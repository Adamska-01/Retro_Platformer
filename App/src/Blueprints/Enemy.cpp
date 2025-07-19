#include "Blueprints/Enemy.h"
#include "Components/AI/SimpleAI.h"
#include <Components/AI/Behaviors/FlyingAIBehavior.h>
#include <Components/AI/Behaviors/GroundAIBehavior.h>
#include <Components/Collisions/BoxCollider2D.h>
#include <Components/Collisions/CircleCollider2D.h>
#include <Components/Physics/RigidBody2D.h>
#include <Components/Rendering/Sprite.h>
#include <Components/SpriteAnimator.h>
#include <Components/Transform.h>
#include <Data/Collision/PhysicsMaterial.h>
#include <Data/Physics/BodyDefinition2D.h>


Enemy::Enemy(Vector2F startPos, const EnemyConfig& enemyConfig)
	: enemyConfig(enemyConfig)
{
	auto scale = 0.65f;

	transform->SetWorldPosition(startPos + Vector2F::Up * (enemyConfig.characterSize - enemyConfig.characterSize * scale));

	transform->SetWorldScale(Vector2F(scale, scale));
}

void Enemy::ConstructGameObject()
{
	AddComponent<Sprite>(enemyConfig.spriteSource);
	
	auto spriteAnimator = AddComponent<SpriteAnimator>();
	spriteAnimator->AddAnimation(enemyConfig.idleAnimProperty);
	spriteAnimator->PlayAnimation(enemyConfig.idleAnimProperty.name);

	auto scaledColliderSize = enemyConfig.characterSize * transform->GetWorldScale().x;

	std::unique_ptr<AIBehavior> behavior;
	if (enemyConfig.canFly)
	{
		behavior = std::make_unique<FlyingAIBehavior>();
	}
	else
	{
		behavior = std::make_unique<GroundAIBehavior>();
	}

	AddComponent<SimpleAI>(std::move(behavior));
	AddComponent<CircleCollider2D>(scaledColliderSize);
	AddComponent<RigidBody2D>(enemyConfig.bodyDefinition);
}