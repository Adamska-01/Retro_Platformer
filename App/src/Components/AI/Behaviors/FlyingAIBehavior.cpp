#include "Components/AI/Behaviors/FlyingAIBehavior.h"
#include "Components/AI/SimpleAI.h"
#include <Core/Math/Vector2.h>
#include <Engine/Components/Animation/SpriteAnimator.h>
#include <Engine/Components/Physics/RigidBody2D.h>
#include <Engine/Components/Transform.h>


FlyingAIBehavior::FlyingAIBehavior()
	: minDistance(300),
	speed(2.0f)
{
}

void FlyingAIBehavior::Update(SimpleAI* ai, float deltaTime)
{
	auto currentPos = aiTransform->GetWorldPosition();
	auto playerPos = playerTransform->GetWorldPosition();
	auto startPos = ai->GetStartPos();

	auto toPlayerDir = playerPos - currentPos;
	auto toStartDir = startPos - currentPos;
	auto playerToStart = startPos - playerPos;

	auto distFromStartToCurrentPos = toStartDir.Magnitude();
	auto distFromStartToPlayer = playerToStart.Magnitude();

	auto movementDir = Vector2F::Zero;

	const auto epsilon = 1.0f;

	bool isPlayerFar = distFromStartToPlayer >= minDistance;
	bool isNotAtStart = distFromStartToCurrentPos > epsilon;

	if (isPlayerFar && isNotAtStart)
	{
		movementDir = toStartDir.Normalize();
	}
	else if (!isPlayerFar)
	{
		movementDir = toPlayerDir.Normalize();
	}

	aiRigidBody->SetVelocity(movementDir * speed);

	auto flipState = (playerPos.x < currentPos.x) ? SDL_RendererFlip::SDL_FLIP_NONE : SDL_RendererFlip::SDL_FLIP_HORIZONTAL;

	aiSpriteAnimator->SetFlipState(flipState);
}