#pragma once


class SimpleAI;

namespace DeadFrame2D::Engine
{
	class Transform;
	class SpriteAnimator;
	class RigidBody2D;
}


class AIBehavior
{
protected:
	DeadFrame2D::Engine::Transform* aiTransform;

	DeadFrame2D::Engine::Transform* playerTransform;

	DeadFrame2D::Engine::SpriteAnimator* aiSpriteAnimator;

	DeadFrame2D::Engine::RigidBody2D* aiRigidBody;


public:
	virtual ~AIBehavior() = default;

	
	virtual void Init(SimpleAI* ai);

	virtual void Update(SimpleAI* ai, float deltaTime) = 0;
};