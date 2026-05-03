#pragma once
#include <Core/Math/Vector2.h>
#include <Engine/ECS/Entity/Object/Core/GameObject.h>
#include <memory>
#include <SDL.h>


class FollowCameraObject : public DF2D::Engine::GameObject
{
private:
	DF2D::Engine::ObjectHandle<DF2D::Engine::GameObject> target;

	SDL_FRect bounds;

	DF2D::Core::Vector2F offset;

	float followSpeed;


public:
	FollowCameraObject(DF2D::Engine::ObjectHandle<DF2D::Engine::GameObject> target, SDL_FRect bounds, DF2D::Core::Vector2F offset = DF2D::Core::Vector2F::Zero, float followSpeed = 10.0f);


	virtual void ConstructGameObject() override;
};