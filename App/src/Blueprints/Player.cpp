#include "Blueprints/Player.h"
#include "Components/Controllers/PlayerController.h"
#include "Components/Transform.h"
#include <Components/Audio/AudioListener.h>
#include <Components/Collisions/BoxCollider2D.h>
#include <Components/Collisions/CircleCollider2D.h>
#include <Components/Physics/RigidBody2D.h>
#include <Components/Rendering/Sprite.h>
#include <Components/SpriteAnimator.h>
#include <Data/Physics/BodyDefinition2D.h>


Player::Player(Vector2F startPos, std::string_view idleSpriteSource, std::string_view runSpriteSource)
	: idleSpriteSource(idleSpriteSource),
	runSpriteSource(runSpriteSource)
{
	transform->SetWorldPosition(startPos);
	transform->SetWorldScale(Vector2F::One * 2.0f);
}

Player::~Player()
{
}

void Player::ConstructGameObject()
{
	AddComponent<Sprite>(idleSpriteSource);
	AddComponent<SpriteAnimator>();

	auto physicalMat = PhysicsMaterial
	{
		.friction = 0.0f
	};
	AddComponent<CircleCollider2D>(26.0f, Vector2F::Zero, physicalMat);

	physicalMat.isSensor = true;
	auto groundCollider = AddComponent<BoxCollider2D>(Vector2F(16.0f, 5.0f), Vector2F(0.0f, 32.0f), 0.0f, physicalMat);

	auto bodyDef = BodyDefinition2D
	{
		.type = BodyType2D::Dynamic,
		.gravityScale = 15.0f,
		.fixedRotation = true
	};
	AddComponent<RigidBody2D>(bodyDef);

	AddComponent<PlayerController>(idleSpriteSource, runSpriteSource);

	AddComponent<AudioListener>();
}