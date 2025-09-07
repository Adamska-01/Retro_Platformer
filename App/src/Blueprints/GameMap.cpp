#include "Blueprints/GameMap.h"
#include "Components/Map/CustomTileMapCollider2D.h"
#include "Components/Map/CustomTileMapRenderer2D.h"
#include <Data/Physics/BodyDefinition2D.h>
#include <Data/Physics/BodyType2D.h>
#include <Engine/Components/Physics/RigidBody2D.h>
#include <Utilities/Serialization/JsonSerializer.h>


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

	tileObject.lock()->AddComponent<CustomTileMapRenderer2D>(tileMapModel);

	auto physicalMat = PhysicsMaterial
	{
		.friction = 0.0f
	};

	tileObject.lock()->AddComponent<CustomTileMapCollider2D>(physicalMat);
	
	tileObject.lock()->AddComponent<RigidBody2D>(bodyDef);

	AddChildGameObject(tileObject);
}