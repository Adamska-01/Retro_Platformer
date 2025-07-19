#include "Components/AI/Behaviors/GroundAIBehavior.h"
#include <Components/Physics/RigidBody2D.h>
#include <Components/SpriteAnimator.h>
#include <Components/Transform.h>


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
			? SDL_RendererFlip::SDL_FLIP_NONE
			: SDL_RendererFlip::SDL_FLIP_HORIZONTAL;

		aiSpriteAnimator->SetFlipState(spriteFlipState);
	}

	// Move in current direction
	auto dir = movingLeft ? -1.0f : 1.0f;

	aiRigidBody->SetVelocityX(dir * speed);
}