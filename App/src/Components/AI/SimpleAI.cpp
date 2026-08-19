#include "Components/AI/Abstractions/AIBehavior.h"
#include "Components/AI/SimpleAI.h"
#include "Components/Audio/DestroyOnAudioFinished.h"
#include "Components/Controllers/PlayerController.h"
#include <Constants/AssetPaths.h>
#include <CustomEvents/LifeLostEvent.h>
#include <Data/Components/Collision/CollisionInfo.h>
#include <Engine/Blueprints/Audio/AudioClipBlueprint.h>
#include <Engine/ECS/Component/Collisions/CircleCollider2D.h>
#include <Engine/ECS/Component/Physics/RigidBody2D.h>
#include <Engine/ECS/Component/Transform.h>
#include <Engine/ECS/Entity/Object/Core/GameObject.h>
#include <Engine/ECS/System/Events/EventDispatcher.h>
#include <Utilities/Debugging/Guards.h>
#include <Utilities/Helpers/Events/EventHelpers.h>


using namespace DF2D::Core;
using namespace DF2D::Data;
using namespace DF2D::Engine;
using namespace DF2D::Utilities;


SimpleAI::SimpleAI(std::unique_ptr<AIBehavior> behavior)
	: behavior(std::move(behavior)),
	startPos(Vector2F::Zero),
	processingPlayer(true)
{
}

SimpleAI::~SimpleAI()
{
}

void SimpleAI::LifeLostEventHandler(std::shared_ptr<DispatchableEvent> dispatchableEvent)
{
	Reset();
}

void SimpleAI::OnCircleContactEnterHandlers(const CollisionInfo& collisionInfo)
{
	auto playerPtr = collisionInfo.otherGameObject;
	auto enemyPtr = collisionInfo.thisGameObject;

	if (playerPtr == nullptr || enemyPtr == nullptr)
		return;

	auto playerController = playerPtr->GetComponent<PlayerController>();
	auto playerRigidBody = playerPtr->GetComponent<RigidBody2D>();
	auto playerTransform = playerPtr->GetComponent<Transform>();
	auto enemyTransform = enemyPtr->GetComponent<Transform>();

	if (playerController == nullptr 
		|| playerRigidBody == nullptr
		|| playerTransform == nullptr
		|| enemyTransform == nullptr)
		return;
	
	auto fromEnemyToPlayerDir = (playerTransform->GetWorldPosition() - enemyTransform->GetWorldPosition()).Normalize();

	auto dotProduct = Vector2F::Up.Dot(fromEnemyToPlayerDir);

	// Kill enemy
	if (dotProduct <= 1.0f && dotProduct >= 0.9f)
	{
		GetGameObject()->SetActive(false);

		playerRigidBody->SetVelocity(Vector2F::Zero);
		playerRigidBody->AddImpulse(Vector2F::Up * 30.0f);

		// Enemy killed sound (self-destroys once the clip finishes)
		auto soundSourceObj = GameObject::Instantiate<AudioClipBlueprint>(AssetPaths::Files::ENEMY_KILLED);

		soundSourceObj->AddComponent<DestroyOnAudioFinished>();
	}
	// Kill Player
	else
	{
		playerController->LoseLife();

		// Player killed sound (self-destroys once the clip finishes)
		auto soundSourceObj = GameObject::Instantiate<AudioClipBlueprint>(
			AssetPaths::Files::PLAYER_KILLED,
			Vector2F::Zero,
			0.5f);

		soundSourceObj->AddComponent<DestroyOnAudioFinished>();
	}
}

void SimpleAI::Init()
{
	transform = Guard::AgainstNullAssignment(GetGameObject()->GetComponent<Transform>(), NAME_OF(transform));

	auto* eventDispatcher = Guard::AgainstNullAssignment(GetGameObject()->ServiceContext().eventDispatcher, NAME_OF(eventDispatcher));

	eventDispatcher->RegisterEventHandler<LifeLostEvent>(GetHandle(), EventHelpers::BindFunction(this, &SimpleAI::LifeLostEventHandler));

	if (behavior == nullptr)
		return;

	behavior->Init(this);
}

void SimpleAI::Start()
{
	startPos = transform->GetWorldPosition();

	auto circleCollider = GetGameObject()->GetComponent<CircleCollider2D>();

	if (circleCollider == nullptr)
		return;

	circleCollider->RegisterContactEnterHandler(GetHandle(), EventHelpers::BindFunction(this, &SimpleAI::OnCircleContactEnterHandlers));
}

void SimpleAI::Update(float deltaTime)
{
	if (behavior == nullptr)
		return;

	behavior->Update(this, deltaTime);
}

void SimpleAI::Reset()
{
	GetGameObject()->SetActive(true);

	transform->SetWorldPosition(startPos);

	processingPlayer = false;
}

Vector2F SimpleAI::GetStartPos() const
{
	return startPos;
}