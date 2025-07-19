#pragma once


class SimpleAI;
class Transform;
class SpriteAnimator;
class RigidBody2D;


class AIBehavior
{
protected:
	Transform* aiTransform;

	Transform* playerTransform;

	SpriteAnimator* aiSpriteAnimator;

	RigidBody2D* aiRigidBody;


public:
	virtual ~AIBehavior() = default;

	
	virtual void Init(SimpleAI* ai);

	virtual void Update(SimpleAI* ai, float deltaTime) = 0;
};