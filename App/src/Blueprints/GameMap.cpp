#include "Blueprints/GameMap.h"
#include "Components/Map/CustomTileMapCollider2D.h"
#include "Components/Map/CustomTileMapRenderer2D.h"
#include <Data/Components/Physics/BodyDefinition2D.h>
#include <Data/Components/Physics/BodyType2D.h>
#include <Engine/ECS/Component/Physics/RigidBody2D.h>


using namespace DF2D::Data;
using namespace DF2D::Engine;


GameMap::GameMap(std::shared_ptr<TileMapModel> tileMapModel)
	: tileMapModel(tileMapModel)
{
}

void GameMap::ConstructGameObject()
{
	auto bodyDef = BodyDefinition2D
	{
		.type = BodyType2D::Static
	};

	auto tileObject = GameObject::Instantiate<GameObject>();

	tileObject->AddComponent<CustomTileMapRenderer2D>(tileMapModel);

	auto physicalMat = PhysicsMaterial
	{
		.friction = 0.0f
	};

	tileObject->AddComponent<CustomTileMapCollider2D>(physicalMat);

	tileObject->AddComponent<RigidBody2D>(bodyDef);

	tileObject->SetParent(thisGameObject);
}