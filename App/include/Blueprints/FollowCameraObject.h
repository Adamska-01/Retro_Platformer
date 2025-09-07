#pragma once
#include <Core/Math/Vector2.h>
#include <Engine/Entity/GameObject.h>
#include <memory>
#include <SDL.h>


class FollowCameraObject : public GameObject
{
private:
	std::weak_ptr<GameObject> target;

	SDL_FRect bounds;

	Vector2F offset;

	float followSpeed;


public:
	FollowCameraObject(std::weak_ptr<GameObject> target, SDL_FRect bounds, Vector2F offset = Vector2F::Zero, float followSpeed = 10.0f);


	virtual void ConstructGameObject() override;
};