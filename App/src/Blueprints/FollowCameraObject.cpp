#include <Blueprints/FollowCameraObject.h>
#include <Engine/ECS/Component/Rendering/Camera/Camera.h>
#include <Engine/ECS/Component/Rendering/Camera/CameraFollow.h>


using namespace DF2D::Core;
using namespace DF2D::Engine;


FollowCameraObject::FollowCameraObject(ObjectHandle<GameObject> target, RectF bounds, Vector2F offset, float followSpeed)
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