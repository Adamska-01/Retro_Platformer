#include "Components/AI/Abstractions/AIBehavior.h"
#include "Components/AI/SimpleAI.h"
#include "Components/Controllers/PlayerController.h"
#include <Constants/AssetPaths.h>
#include <Core/SubSystems/Systems/CoroutineScheduler.h>
#include <CustomEvents/LifeLostEvent.h>
#include <Data/Collision/CollisionInfo.h>
#include <Engine/Blueprints/Audio/AudioClipBlueprint.h>
#include <Engine/Components/Collisions/CircleCollider2D.h>
#include <Engine/Components/Physics/RigidBody2D.h>
#include <Engine/Components/Transform.h>
#include <Engine/EngineEvents/EventDispatcher.h>
#include <Engine/Entity/GameObject.h>
#include <Utilities/Debugging/Guards.h>
#include <Utilities/Helpers/Events/EventHelpers.h>


SimpleAI::SimpleAI(std::unique_ptr<AIBehavior> behavior)
	: behavior(std::move(behavior)),
	transform(nullptr),
	startPos(Vector2F::Zero),
	processingPlayer(true)
{
	EventDispatcher::RegisterEventHandler(std::type_index(typeid(LifeLostEvent)), EventHelpers::BindFunction(this, &SimpleAI::LifeLostEventHandler), reinterpret_cast<std::uintptr_t>(this));
}

SimpleAI::~SimpleAI()
{
	EventDispatcher::DeregisterEventHandler(std::type_index(typeid(LifeLostEvent)), reinterpret_cast<std::uintptr_t>(this));
}

void SimpleAI::LifeLostEventHandler(std::shared_ptr<DispatchableEvent> dispatchableEvent)
{
	Reset();
}

void SimpleAI::OnCircleContactEnterHandlers(const CollisionInfo& collisionInfo)
{
	auto playerPtr = collisionInfo.otherGameObject.lock();
	auto enemyPtr = collisionInfo.thisGameObject.lock();

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
		OwningObject.lock()->SetActive(false);

		playerRigidBody->SetVelocity(Vector2F::Zero);
		playerRigidBody->AddImpulse(Vector2F::Up * 30.0f);

		// Jump Sound
		auto soundSourceObj = GameObject::Instantiate<AudioClipBlueprint>(AssetPaths::Files::ENEMY_KILLED);

		CoroutineScheduler::StartCoroutine(soundSourceObj.lock()->Destroy(1.0f));
	}
	// Kill Player
	else
	{
		playerController->LoseLife();

		// Jump Sound
		auto soundSourceObj = GameObject::Instantiate<AudioClipBlueprint>(
			AssetPaths::Files::PLAYER_KILLED, 
			Vector2F::Zero, 
			0.5f);

		CoroutineScheduler::StartCoroutine(soundSourceObj.lock()->Destroy(1.0f));
	}
}

void SimpleAI::Init()
{
	transform = OwningObject.lock()->GetComponent<Transform>();

	Tools::Helpers::GuardAgainstNull(transform, "Failed to get Transform from OwningObject");

	if (behavior == nullptr)
		return;

	behavior->Init(this);
}

void SimpleAI::Start()
{
	startPos = transform->GetWorldPosition();

	auto circleCollider = OwningObject.lock()->GetComponent<CircleCollider2D>();

	if (circleCollider == nullptr)
		return;

	circleCollider->RegisterContactEnterHandler(EventHelpers::BindFunction(this, &SimpleAI::OnCircleContactEnterHandlers), reinterpret_cast<uintptr_t>(this));
}

void SimpleAI::Update(float deltaTime)
{
	if (behavior == nullptr)
		return;

	behavior->Update(this, deltaTime);
}

void SimpleAI::Draw()
{

}

void SimpleAI::Reset()
{
	OwningObject.lock()->SetActive(true);

	transform->SetWorldPosition(startPos);

	processingPlayer = false;
}

Vector2F SimpleAI::GetStartPos() const
{
	return startPos;
}
