#pragma once
#include <Engine/ECS/Entity/Component/Handle/ComponentHandle.h>


class SimpleAI;

namespace DF2D::Engine
{
	class Transform;
	class SpriteAnimator;
	class RigidBody2D;
}


class AIBehavior
{
protected:
	DF2D::Engine::ComponentHandle<DF2D::Engine::Transform> aiTransform;

	DF2D::Engine::ComponentHandle<DF2D::Engine::Transform> playerTransform;

	DF2D::Engine::ComponentHandle<DF2D::Engine::SpriteAnimator> aiSpriteAnimator;

	DF2D::Engine::ComponentHandle<DF2D::Engine::RigidBody2D> aiRigidBody;


public:
	virtual ~AIBehavior() = default;

	
	virtual void Init(SimpleAI* ai);

	virtual void Update(SimpleAI* ai, float deltaTime) = 0;
};