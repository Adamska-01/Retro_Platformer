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
	auto go = Guard::AgainstNullAssignment(ai->GetGameObject(), NAME_OF(go));

	aiTransform = Guard::AgainstNullAssignment(go->GetComponent<Transform>(), NAME_OF(aiTransform));
	playerTransform = Guard::AgainstNullAssignment(SceneManager::FindObjectOfType<PlayerController>()->GetGameObject()->GetTransform(), NAME_OF(playerTransform));
	aiSpriteAnimator = Guard::AgainstNullAssignment(go->GetComponent<SpriteAnimator>(), NAME_OF(aiSpriteAnimator));
	aiRigidBody = Guard::AgainstNullAssignment(go->GetComponent<RigidBody2D>(), NAME_OF(aiRigidBody));
}