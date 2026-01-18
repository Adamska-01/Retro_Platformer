#include "Blueprints/Player.h"
#include "Components/Controllers/PlayerController.h"
#include <Data/Physics/BodyDefinition2D.h>
#include <Engine/Components/Animation/SpriteAnimator.h>
#include <Engine/Components/Audio/AudioListener.h>
#include <Engine/Components/Collisions/BoxCollider2D.h>
#include <Engine/Components/Collisions/CircleCollider2D.h>
#include <Engine/Components/Physics/RigidBody2D.h>
#include <Engine/Components/Rendering/SpriteRenderer.h>
#include <Engine/Components/Transform.h>


using namespace DeadFrame2D::Core;
using namespace DeadFrame2D::Data;
using namespace DeadFrame2D::Engine;


Player::Player(Vector2F startPos, std::string_view idleSpriteSource, std::string_view runSpriteSource)
	: startPos(startPos),
	idleSpriteSource(idleSpriteSource),
	runSpriteSource(runSpriteSource)
{
	
}

Player::~Player()
{
}

void Player::ConstructGameObject()
{
	transform->SetWorldPosition(startPos);
	transform->SetWorldScale(Vector2F::One * 2.0f);

	AddComponent<SpriteRenderer>(idleSpriteSource);

	AddComponent<SpriteAnimator>();

	auto bodyDef = BodyDefinition2D
	{
		.type = BodyType2D::Dynamic,
		.gravityScale = 15.0f,
		.fixedRotation = true
	};
	AddComponent<RigidBody2D>(bodyDef);

	AddComponent<PlayerController>(idleSpriteSource, runSpriteSource);

	AddComponent<AudioListener>();

	auto physicalMat = PhysicsMaterial
	{
		.friction = 0.0f
	};
	AddComponent<CircleCollider2D>(26.0f, Vector2F::Zero, physicalMat);


	// Ground Collider
	physicalMat.isSensor = true;

	auto groundObject = GameObject::Instantiate<GameObject>();

	groundObject->SetParent(thisGameObject);

	groundObject->GetTransform()->SetLocalPosition(Vector2F::Zero);

	groundObject->AddComponent<BoxCollider2D>(Vector2F(16.0f, 5.0f), Vector2F(0.0f, 32.0f), 0.0f, physicalMat);
}