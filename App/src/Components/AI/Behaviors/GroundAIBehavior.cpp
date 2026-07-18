#include "Components/AI/Behaviors/GroundAIBehavior.h"
#include <Data/Systems/Rendering/RenderFlip.h>
#include <Engine/ECS/Component/Animation/SpriteAnimator.h>
#include <Engine/ECS/Component/Physics/RigidBody2D.h>
#include <Engine/ECS/Component/Transform.h>


using namespace DF2D::Core;
using namespace DF2D::Data;


GroundAIBehavior::GroundAIBehavior()
	: movingLeft(true),
	speed(2.0f)
{
}

void GroundAIBehavior::Update(SimpleAI* ai, float deltaTime)
{
	auto velocity = aiRigidBody->GetVelocity();

	// Check if we've hit a wall (velocity dropped due to collision)
	if (std::abs(velocity.x) < 0.1f)
	{
		// Reverse direction
		movingLeft = !movingLeft;

		auto spriteFlipState = movingLeft
			? RenderFlip::NONE
			: RenderFlip::HORIZONTAL;

		aiSpriteAnimator->SetFlipState(spriteFlipState);
	}

	// Move in current direction
	auto dir = movingLeft ? -1.0f : 1.0f;

	aiRigidBody->SetVelocityX(dir * speed);
}