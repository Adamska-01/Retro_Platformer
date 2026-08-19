#pragma once
#include <Core/Math/Rect.h>
#include <Core/Math/Vector2.h>
#include <Engine/ECS/Entity/Object/Core/GameObject.h>
#include <memory>


class FollowCameraObject : public DF2D::Engine::GameObject
{
private:
	DF2D::Engine::ObjectHandle<DF2D::Engine::GameObject> target;

	DF2D::Core::RectF bounds;

	DF2D::Core::Vector2F offset;

	float followSpeed;


public:
	FollowCameraObject(DF2D::Engine::ObjectHandle<DF2D::Engine::GameObject> target, DF2D::Core::RectF bounds, DF2D::Core::Vector2F offset = DF2D::Core::Vector2F::Zero, float followSpeed = 10.0f);
};