#include "Components/AI/Abstractions/AIBehavior.h"
#include "Components/AI/SimpleAI.h"
#include "Components/Controllers/PlayerController.h"
#include <Engine/ECS/Component/Animation/SpriteAnimator.h>
#include <Engine/ECS/Component/Physics/RigidBody2D.h>
#include <Engine/ECS/Component/Transform.h>
#include <Engine/ECS/Entity/Object/Core/GameObject.h>
#include <Engine/ECS/System/Scene/SceneManager.h>
#include <Utilities/Debugging/Guards.h>


using namespace DF2D::Engine;
using namespace DF2D::Utilities;


void AIBehavior::Init(SimpleAI* ai)
{
	auto go = Guard::AgainstNullAssignment(ai->GetGameObject(), NAME_OF(go));

	aiTransform = Guard::AgainstNullAssignment(go->GetComponent<Transform>(), NAME_OF(aiTransform));
	playerTransform = Guard::AgainstNullAssignment(SceneManager::FindObjectOfType<PlayerController>()->GetGameObject()->GetTransform(), NAME_OF(playerTransform));
	aiSpriteAnimator = Guard::AgainstNullAssignment(go->GetComponent<SpriteAnimator>(), NAME_OF(aiSpriteAnimator));
	aiRigidBody = Guard::AgainstNullAssignment(go->GetComponent<RigidBody2D>(), NAME_OF(aiRigidBody));
}