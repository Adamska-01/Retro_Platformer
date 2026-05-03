#include "Blueprints/Enemy.h"
#include "Components/AI/SimpleAI.h"
#include <Components/AI/Behaviors/FlyingAIBehavior.h>
#include <Components/AI/Behaviors/GroundAIBehavior.h>
#include <Engine/ECS/Component/Animation/SpriteAnimator.h>
#include <Engine/ECS/Component/Collisions/CircleCollider2D.h>
#include <Engine/ECS/Component/Physics/RigidBody2D.h>
#include <Engine/ECS/Component/Rendering/SpriteRenderer.h>
#include <Engine/ECS/Component/Transform.h>


using namespace DF2D::Core;
using namespace DF2D::Engine;


Enemy::Enemy(Vector2F startPos, const EnemyConfig& enemyConfig)
	: enemyConfig(enemyConfig),
	startPos(startPos)
{

}

void Enemy::ConstructGameObject()
{
	auto scale = 0.65f;

	transform->SetWorldPosition(startPos + Vector2F::Up * (enemyConfig.characterSize - enemyConfig.characterSize * scale));

	transform->SetWorldScale(Vector2F(scale, scale));

	AddComponent<SpriteRenderer>(enemyConfig.spriteSource);
	
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