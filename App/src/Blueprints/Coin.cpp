#include "Blueprints/Coin.h"
#include "Components/Controllers/PlayerController.h"
#include "Constants/AssetPaths.h"
#include "CustomEvents/PointsScoredEvent.h"
#include <Core/SubSystems/Systems/CoroutineScheduler.h>
#include <Data/Collision/CollisionInfo.h>
#include <Engine/Blueprints/Audio/AudioClipBlueprint.h>
#include <Engine/Components/Animation/SpriteAnimator.h>
#include <Engine/Components/Collisions/CircleCollider2D.h>
#include <Engine/Components/Physics/RigidBody2D.h>
#include <Engine/Components/Rendering/Sprite.h>
#include <Engine/Components/Transform.h>
#include <Engine/EngineEvents/EventDispatcher.h>
#include <Utilities/Helpers/Events/EventHelpers.h>


using namespace DeadFrame2D::Core;
using namespace DeadFrame2D::Data;
using namespace DeadFrame2D::Engine;
using namespace DeadFrame2D::Utilities;


Coin::Coin(Vector2F startPos, std::string_view spriteSource)
	: startPos(startPos),
	score(100),
	spriteSource(spriteSource)
{
	
}

void Coin::OnContactEnterHandler(const CollisionInfo& collisionInfo)
{
	const auto& other = collisionInfo.otherGameObject;
	
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

	CoroutineScheduler::StartCoroutine(soundSourceObj->Destroy(1.0f));

	Destroy();
}

void Coin::ConstructGameObject()
{
	transform->SetWorldPosition(startPos);
	transform->SetWorldScale(Vector2F::One * 2.0f);

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