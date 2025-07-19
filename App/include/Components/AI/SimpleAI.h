#pragma once
#include <Components/GameComponent.h>
#include <Math/Vector2.h>
#include <memory>


class AIBehavior;
class Transform;
class DispatchableEvent;
struct CollisionInfo;


class SimpleAI : public GameComponent
{
private:
	std::unique_ptr<AIBehavior> behavior;

	Transform* transform;

	Vector2F startPos;

	bool processingPlayer;


	void LifeLostEventHandler(std::shared_ptr<DispatchableEvent> dispatchableEvent);

	void OnCircleContactEnterHandlers(const CollisionInfo& collisionInfo);


public:
	SimpleAI(std::unique_ptr<AIBehavior> behavior);

	virtual ~SimpleAI() override;


	virtual void Init() override;

	virtual void Start() override;

	virtual void Update(float deltaTime) override;

	virtual void Draw() override;


	void Reset();

	Vector2F GetStartPos() const;
};