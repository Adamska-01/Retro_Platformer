#include "Blueprints/Coin.h"
#include "Components/Controllers/PlayerController.h"
#include "Constants/AssetPaths.h"
#include "CustomEvents/PointsScoredEvent.h"
#include "EventSystem/EventDispatcher.h"
#include <Blueprints/Audio/AudioClipBlueprint.h>
#include <Components/Collisions/CircleCollider2D.h>
#include <Components/Physics/RigidBody2D.h>
#include <Components/Rendering/Sprite.h>
#include <Components/SpriteAnimator.h>
#include <Components/Transform.h>
#include <Coroutines/CoroutineScheduler.h>
#include <Data/Collision/CollisionInfo.h>
#include <Tools/Helpers/EventHelpers.h>


Coin::Coin(Vector2F startPos, std::string_view spriteSource)
	: score(100),
	spriteSource(spriteSource)
{
	transform->SetWorldPosition(startPos);
	transform->SetWorldScale(Vector2F::One * 2.0f);
}

void Coin::OnContactEnterHandler(const CollisionInfo& collisionInfo)
{
	const auto& other = collisionInfo.otherGameObject.lock();
	
	if (other == nullptr)
		return;

	auto playerComponent = other->GetComponent<PlayerController>();

	if (playerComponent == nullptr)
		return;

	EventDispatcher::SendEvent(std::make_shared<PointsScoredEvent>(score));

	auto soundSourceObj = GameObject::Instantiate<AudioClipBlueprint>(
		AssetPaths::Files::COIN_TAKEN,
		Vector2F::Zero,
		0.5f);

	CoroutineScheduler::StartCoroutine(soundSourceObj.lock()->Destroy(1.0f));

	Destroy();
}

void Coin::ConstructGameObject()
{
	AddComponent<Sprite>(spriteSource);
	auto spriteAnimator = AddComponent<SpriteAnimator>();

	auto coinFlipAnimation = SpriteAnimationProperties
	{
		.name = "CoinFlip",
		.spriteSource = spriteSource,
		.columnCount = 8,
		.animSpeed = 5.0f,
		.loop = true
	};

	spriteAnimator->AddAnimation(coinFlipAnimation);
	spriteAnimator->PlayAnimation(coinFlipAnimation.name);

	auto physicalMat = PhysicsMaterial
	{
		.isSensor = true
	};
	auto collider = AddComponent<CircleCollider2D>(16.0f, Vector2F::Zero, physicalMat);

	auto bodyDef = BodyDefinition2D
	{
		.type = BodyType2D::Static,
		.gravityScale = 0.0f
	};
	AddComponent<RigidBody2D>(bodyDef);

	collider->RegisterContactEnterHandler(EventHelpers::BindFunction(this, &Coin::OnContactEnterHandler), reinterpret_cast<uintptr_t>(this));
}