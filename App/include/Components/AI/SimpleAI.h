#pragma once
#include <Core/Math/Vector2.h>
#include <Engine/ECS/Entity/Component/Core/GameComponent.h>
#include <Engine/ECS/Entity/Component/Handle/ComponentHandle.h>
#include <memory>


class AIBehavior;

namespace DF2D::Engine
{
	class Transform;
	class DispatchableEvent;
}

namespace DF2D::Data
{
	struct CollisionInfo;
}


class SimpleAI : public DF2D::Engine::GameComponent
{
	TYPE_INFO(SimpleAI, DF2D::Engine::GameComponent);


private:
	std::unique_ptr<AIBehavior> behavior;

	DF2D::Engine::ComponentHandle<DF2D::Engine::Transform> transform;

	DF2D::Core::Vector2F startPos;

	bool processingPlayer;


	void LifeLostEventHandler(std::shared_ptr<DF2D::Engine::DispatchableEvent> dispatchableEvent);

	void OnCircleContactEnterHandlers(const DF2D::Data::CollisionInfo& collisionInfo);


public:
	SimpleAI(std::unique_ptr<AIBehavior> behavior);

	virtual ~SimpleAI() override;


	virtual void Init() override;

	virtual void Start() override;

	virtual void Update(float deltaTime) override;


	void Reset();

	DF2D::Core::Vector2F GetStartPos() const;
};