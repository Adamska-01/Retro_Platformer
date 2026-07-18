#include "Blueprints/Coin.h"
#include "Components/Controllers/PlayerController.h"
#include "Constants/AssetPaths.h"
#include "CustomEvents/PointsScoredEvent.h"
#include <Core/Context/Systems/Coroutines/CoroutineScheduler.h>
#include <Data/Components/Collision/CollisionInfo.h>
#include <Engine/Blueprints/Audio/AudioClipBlueprint.h>
#include <Engine/ECS/Component/Animation/SpriteAnimator.h>
#include <Engine/ECS/Component/Collisions/CircleCollider2D.h>
#include <Engine/ECS/Component/Physics/RigidBody2D.h>
#include <Engine/ECS/Component/Rendering/SpriteRenderer.h>
#include <Engine/ECS/Component/Transform.h>
#include <Engine/ECS/System/Events/EventDispatcher.h>
#include <Utilities/Helpers/Events/EventHelpers.h>


using namespace DF2D::Core;
using namespace DF2D::Data;
using namespace DF2D::Engine;
using namespace DF2D::Utilities;


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

	CoreContext().coroutineScheduler->StartCoroutine(soundSourceObj->Destroy(1.0f));

	Destroy();
}

void Coin::ConstructGameObject()
{
	transform->SetWorldPosition(startPos);
	transform->SetWorldScale(Vector2F::One * 2.0f);

	AddComponent<SpriteRenderer>(spriteSource);
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

	collider->RegisterContactEnterHandler(GetObjectHandle(), EventHelpers::BindFunction(this, &Coin::OnContactEnterHandler));
}