#include "Blueprints/ExampleBlueprint.h"
#include "Components/ExampleComponent.h"
#include <Components/Rendering/Sprite.h>
#include <Components/Transform.h>
#include <Constants/ResourcePaths.h>


ExampleBlueprint::ExampleBlueprint(Vector2F startPos)
	: startPos(startPos)
{
}

void ExampleBlueprint::ConstructGameObject()
{
	transform->SetWorldPosition(startPos);

	AddComponent<Sprite>(Constants::ResourcePaths::Files::WINDOW_ICON);
	AddComponent<ExampleComponent>(100.0f, 2.0f, 90.0f);
}