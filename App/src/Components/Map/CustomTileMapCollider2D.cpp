#include "Components/Map/CustomTileMapCollider2D.h"
#include <Core/Math/Vector2.h>
#include <Engine/ECS/Component/Physics/RigidBody2D.h>
#include <Engine/ECS/Component/Transform.h>
#include <Engine/ECS/Entity/Object/Core/GameObject.h>
#include <Utilities/Debugging/Guards.h>


using namespace DF2D::Constants;
using namespace DF2D::Core;
using namespace DF2D::Data;
using namespace DF2D::Utilities;


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

	for (auto fixture : fixtures)
	{
		if (fixture <= 0)
			continue;

		rigidBody->DestroyFixture(fixture);
	}
}

void CustomTileMapCollider2D::Init()
{
	TileCollider2D::Init();

	tileMapRenderer = Guard::AgainstNullAssignment(GetGameObject()->GetComponent<CustomTileMapRenderer2D>(), NAME_OF(tileMapRenderer));

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

	auto angle = transform->GetWorldRotation() * (MathConstants::PI_f / 180.0f);

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

			physicsMaterial.shape = BoxShapeDefinition2D
			{
				.halfExtents = Vector2F(tileSize * 0.5f, tileSize * 0.5f),
				.center = Vector2F((column * tileSize + tileSize * 0.5f), (row * tileSize + tileSize * 0.5f)),
				.angle = angle
			};

			fixtures.push_back(rigidBody->CreateFixture(physicsMaterial, GetHandleAs<DF2D::Engine::ContactEventProvider>()));
		}
	}

	isDirty = false;
}