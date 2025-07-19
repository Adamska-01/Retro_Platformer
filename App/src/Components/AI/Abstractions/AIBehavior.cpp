#include "Components/AI/Abstractions/AIBehavior.h"
#include "Components/AI/SimpleAI.h"
#include "Components/Controllers/PlayerController.h"
#include <Components/Physics/RigidBody2D.h>
#include <Components/SpriteAnimator.h>
#include <Components/Transform.h>
#include <GameObject.h>
#include <Management/SceneManager.h>
#include <Tools/Helpers/Guards.h>


void AIBehavior::Init(SimpleAI* ai)
{
	auto go = ai->GetGameObject().lock();

	Tools::Helpers::GuardAgainstNull(go, "Failed to get GameObject from SimpleAI");

	aiTransform = go->GetComponent<Transform>();
	playerTransform = SceneManager::FindObjectOfType<PlayerController>()->GetGameObject().lock()->GetTransform();
	aiSpriteAnimator = go->GetComponent<SpriteAnimator>();
	aiRigidBody = go->GetComponent<RigidBody2D>();

	Tools::Helpers::GuardAgainstNull(aiTransform, "Failed to get AI Transform from SimpleAI");
	Tools::Helpers::GuardAgainstNull(playerTransform, "Failed to get player Transform from SimpleAI");
	Tools::Helpers::GuardAgainstNull(aiSpriteAnimator, "Failed to get AI SpriteAnimator from SimpleAI");
	Tools::Helpers::GuardAgainstNull(aiRigidBody, "Failed to get AI RigidBody2D from SimpleAI");
}