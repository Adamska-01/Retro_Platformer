#include "Blueprints/Key.h"
#include "Components/Controllers/PlayerController.h"
#include "CustomEvents/GameEndedEvent.h"
#include <CustomEvents/PointsScoredEvent.h>
#include <Data/Components/Collision/CollisionInfo.h>
#include <Data/Components/Collision/PhysicsMaterial.h>
#include <Data/Components/Physics/BodyDefinition2D.h>
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
	
	AddComponent<SpriteRenderer>(spriteSource);
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

	collider->RegisterContactEnterHandler(GetObjectHandle(), EventHelpers::BindFunction(this, &Key::OnContactEnterHandler));
}