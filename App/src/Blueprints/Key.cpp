#include "Blueprints/Key.h"
#include "Blueprints/Player.h"
#include "Components/Controllers/PlayerController.h"
#include "Components/Transform.h"
#include "CustomEvents/GameEndedEvent.h"
#include <Components/Collisions/CircleCollider2D.h>
#include <Components/Physics/RigidBody2D.h>
#include <Components/Rendering/Sprite.h>
#include <Components/SpriteAnimator.h>
#include <CustomEvents/PointsScoredEvent.h>
#include <Data/Collision/CollisionInfo.h>
#include <Data/Collision/PhysicsMaterial.h>
#include <Data/Physics/BodyDefinition2D.h>
#include <Tools/Helpers/EventHelpers.h>


Key::Key(Vector2F startPos, std::string_view spriteSource)
	: spriteSource(spriteSource)
{
	transform->SetWorldPosition(startPos);
}

void Key::OnContactEnterHandler(const CollisionInfo& collisionInfo)
{
	const auto& other = collisionInfo.otherGameObject.lock();

	if (other == nullptr)
		return;

	auto playerComponent = other->GetComponent<PlayerController>();

	if (playerComponent == nullptr)
		return;

	EventDispatcher::SendEvent(std::make_shared<PointsScoredEvent>(score));
	EventDispatcher::SendEvent(std::make_shared<GameEndedEvent>(false));

	Destroy();
}

void Key::ConstructGameObject()
{
	AddComponent<Sprite>(spriteSource);
	auto spriteAnimator = AddComponent<SpriteAnimator>();

	auto keyFlipAnimation = SpriteAnimationProperties
	{
		.name = "CoinFlip",
		.spriteSource = spriteSource,
		.columnCount = 9,
		.animSpeed = 5.0f,
		.loop = true
	};

	spriteAnimator->AddAnimation(keyFlipAnimation);
	spriteAnimator->PlayAnimation(keyFlipAnimation.name);
	
	auto physicalMat = PhysicsMaterial
	{
		.isSensor = true
	};
	auto collider = AddComponent<CircleCollider2D>(32.0f, Vector2F::Zero, physicalMat);

	auto bodyDef = BodyDefinition2D
	{
		.type = BodyType2D::Static,
		.gravityScale = 0.0f
	};
	AddComponent<RigidBody2D>(bodyDef);

	collider->RegisterContactEnterHandler(EventHelpers::BindFunction(this, &Key::OnContactEnterHandler), reinterpret_cast<uintptr_t>(this));
}