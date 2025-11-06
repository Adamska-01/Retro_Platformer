#include "Blueprints/Key.h"
#include "Components/Controllers/PlayerController.h"
#include "CustomEvents/GameEndedEvent.h"
#include <CustomEvents/PointsScoredEvent.h>
#include <Data/Collision/CollisionInfo.h>
#include <Data/Collision/PhysicsMaterial.h>
#include <Data/Physics/BodyDefinition2D.h>
#include <Engine/Components/Animation/SpriteAnimator.h>
#include <Engine/Components/Collisions/CircleCollider2D.h>
#include <Engine/Components/Physics/RigidBody2D.h>
#include <Engine/Components/Rendering/Sprite.h>
#include <Engine/Components/Transform.h>
#include <Utilities/Helpers/Events/EventHelpers.h>


using namespace DeadFrame2D::Core;
using namespace DeadFrame2D::Data;
using namespace DeadFrame2D::Engine;
using namespace DeadFrame2D::Utilities;


Key::Key(Vector2F startPos, std::string_view spriteSource)
	: startPos(startPos),
	spriteSource(spriteSource)
{
}

void Key::OnContactEnterHandler(const CollisionInfo& collisionInfo)
{
	const auto& other = collisionInfo.otherGameObject;

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
	transform->SetWorldPosition(startPos);
	
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