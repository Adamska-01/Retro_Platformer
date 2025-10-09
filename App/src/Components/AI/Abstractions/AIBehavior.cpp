#include "Components/AI/Abstractions/AIBehavior.h"
#include "Components/AI/SimpleAI.h"
#include "Components/Controllers/PlayerController.h"
#include <Engine/Components/Animation/SpriteAnimator.h>
#include <Engine/Components/Physics/RigidBody2D.h>
#include <Engine/Components/Transform.h>
#include <Engine/Entity/GameObject.h>
#include <Engine/SceneSystem/SceneManager.h>
#include <Utilities/Debugging/Guards.h>


using namespace DeadFrame2D::Engine;
using namespace DeadFrame2D::Utilities;


void AIBehavior::Init(SimpleAI* ai)
{
	auto go = ai->GetGameObject().lock();

	Guard::AgainstNull(go, NAME_OF(go));

	aiTransform = go->GetComponent<Transform>();
	playerTransform = SceneManager::FindObjectOfType<PlayerController>()->GetGameObject().lock()->GetTransform();
	aiSpriteAnimator = go->GetComponent<SpriteAnimator>();
	aiRigidBody = go->GetComponent<RigidBody2D>();

	Guard::AgainstNull(aiTransform, NAME_OF(aiTransform));
	Guard::AgainstNull(playerTransform, NAME_OF(playerTransform));
	Guard::AgainstNull(aiSpriteAnimator, NAME_OF(aiSpriteAnimator));
	Guard::AgainstNull(aiRigidBody, NAME_OF(aiRigidBody));
}