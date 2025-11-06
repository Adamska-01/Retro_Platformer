#pragma once
#include <Core/Math/Vector2.h>
#include <Engine/Components/GameComponent.h>
#include <Engine/Entity/ComponentHandle.h>
#include <memory>


class AIBehavior;

namespace DeadFrame2D::Engine
{
	class Transform;
	class DispatchableEvent;
}

namespace DeadFrame2D::Data
{
	struct CollisionInfo;
}


class SimpleAI : public DeadFrame2D::Engine::GameComponent
{
	TYPE_INFO(SimpleAI, DeadFrame2D::Engine::GameComponent);


private:
	std::unique_ptr<AIBehavior> behavior;

	DeadFrame2D::Engine::ComponentHandle<DeadFrame2D::Engine::Transform> transform;

	DeadFrame2D::Core::Vector2F startPos;

	bool processingPlayer;


	void LifeLostEventHandler(std::shared_ptr<DeadFrame2D::Engine::DispatchableEvent> dispatchableEvent);

	void OnCircleContactEnterHandlers(const DeadFrame2D::Data::CollisionInfo& collisionInfo);


public:
	SimpleAI(std::unique_ptr<AIBehavior> behavior);

	virtual ~SimpleAI() override;


	virtual void Init() override;

	virtual void Start() override;

	virtual void Update(float deltaTime) override;


	void Reset();

	DeadFrame2D::Core::Vector2F GetStartPos() const;
};