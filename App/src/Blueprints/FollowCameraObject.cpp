#include "Components/Rendering/Camera.h"
#include <Blueprints/FollowCameraObject.h>
#include <Components/Rendering/Camera/CameraFollow.h>


FollowCameraObject::FollowCameraObject(std::weak_ptr<GameObject> target, SDL_FRect bounds, Vector2F offset, float followSpeed)
	: target(target),
	bounds(bounds),
	offset(offset),
	followSpeed(followSpeed)
{
}

void FollowCameraObject::ConstructGameObject()
{
	auto cameraComonent = AddComponent<Camera>();

	auto cameraFollowComponent = AddComponent<CameraFollow>(cameraComonent, target);

	cameraFollowComponent->SetBounds(bounds);
}
