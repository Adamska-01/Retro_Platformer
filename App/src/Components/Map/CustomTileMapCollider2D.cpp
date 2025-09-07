#include "Components/Map/CustomTileMapCollider2D.h"
#include <Core/Math/Vector2.h>
#include <Engine/Components/Physics/RigidBody2D.h>
#include <Engine/Components/Transform.h>
#include <Engine/Entity/GameObject.h>
#include <Utilities/Debugging/Guards.h>
#include <Utilities/Helpers/Physics/PhysicsConversion.h>
#include <Utilities/Helpers/Physics/PhysicsShapeCreators.h>


CustomTileMapCollider2D::CustomTileMapCollider2D(const PhysicsMaterial& physicsMaterial)
{
	fixtures.clear();
	layout.clear();

	tileSize = 0;
}

CustomTileMapCollider2D::~CustomTileMapCollider2D()
{
	DeleteFixtures();
}

void CustomTileMapCollider2D::DeleteFixtures()
{
	if (fixtures.size() <= 0 || rigidBody == nullptr)
		return;

	for (auto fix : fixtures)
	{
		if (fix == nullptr)
			continue;

		rigidBody->DestroyFixture(fix);
	}
}

void CustomTileMapCollider2D::Init()
{
	TileCollider2D::Init();

	tileMapRenderer = OwningObject.lock()->GetComponent<CustomTileMapRenderer2D>();

	Tools::Helpers::GuardAgainstNull(tileMapRenderer, "Failed to get CustomTileMapRenderer2D from OwningObject");

	const auto& tileMap = tileMapRenderer->GetTileMap();

	layout = tileMap->layout;
	
	collidableTiles = tileMap->collidableTiles;

	tileSize = tileMap->tileRenderSize;

	MarkDirty();
}

void CustomTileMapCollider2D::RebuildFixture()
{
	DeleteFixtures();

	SearchRigidBody();

	if (rigidBody == nullptr)
		return;

	fixtures.clear();

	auto startPos = transform->GetWorldPosition();
	auto angle = transform->GetWorldRotation() * (MathConstants::PI / 180.0f);

	auto mapWidth = layout.size();
	auto mapHeight = layout[0].size();

	for (auto row = 0; row < mapWidth; row++)
	{
		for (auto column = 0; column < mapHeight; column++)
		{
			auto tile = layout[row][column];

			auto isCollidable = std::find(collidableTiles.begin(), collidableTiles.end(), tile) != collidableTiles.end();

			if (!isCollidable)
				continue;

			this->physicsMaterial.shape = PhysicsShapeCreators::CreateBoxShape(
				tileSize * 0.5f,
				tileSize * 0.5f,
				Vector2F((column * tileSize + tileSize * 0.5f), (row * tileSize + tileSize * 0.5f)),
				angle);

			auto def = PhysicsConversion::ToB2FixtureDef(physicsMaterial, reinterpret_cast<uintptr_t>(this));

			fixtures.push_back(rigidBody->CreateFixture(&def));

			// Clean up before creating another shape
			delete this->physicsMaterial.shape;
			this->physicsMaterial.shape = nullptr;
		}
	}

	isDirty = false;
}