#pragma once
#include <Core/Math/Vector2.h>
#include <Engine/Entity/GameObject.h>
#include <memory>
#include <SDL.h>


class FollowCameraObject : public DeadFrame2D::Engine::GameObject
{
private:
	DeadFrame2D::Engine::ObjectHandle<DeadFrame2D::Engine::GameObject> target;

	SDL_FRect bounds;

	DeadFrame2D::Core::Vector2F offset;

	float followSpeed;


public:
	FollowCameraObject(DeadFrame2D::Engine::ObjectHandle<DeadFrame2D::Engine::GameObject> target, SDL_FRect bounds, DeadFrame2D::Core::Vector2F offset = DeadFrame2D::Core::Vector2F::Zero, float followSpeed = 10.0f);


	virtual void ConstructGameObject() override;
};