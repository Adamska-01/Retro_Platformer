#include "Components/AI/Behaviors/FlyingAIBehavior.h"
#include "Components/AI/SimpleAI.h"
#include <Core/Math/Vector2.h>
#include <Data/Systems/Rendering/RenderFlip.h>
#include <Engine/ECS/Component/Animation/SpriteAnimator.h>
#include <Engine/ECS/Component/Physics/RigidBody2D.h>
#include <Engine/ECS/Component/Transform.h>


using namespace DF2D::Core;
using namespace DF2D::Data;


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

	auto flipState = (playerPos.x < currentPos.x) ? RenderFlip::NONE : RenderFlip::HORIZONTAL;

	aiSpriteAnimator->SetFlipState(flipState);
}