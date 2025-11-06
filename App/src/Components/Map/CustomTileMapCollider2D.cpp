#include "Components/Map/CustomTileMapCollider2D.h"
#include <Core/Math/Vector2.h>
#include <Engine/Components/Physics/RigidBody2D.h>
#include <Engine/Components/Transform.h>
#include <Engine/Entity/GameObject.h>
#include <Utilities/Debugging/Guards.h>


using namespace DeadFrame2D::Constants;
using namespace DeadFrame2D::Core;
using namespace DeadFrame2D::Data;
using namespace DeadFrame2D::Utilities;


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

			// TODO: The code below is not accessible anymore. Refactor TileCollider2D<T> so that the client doesn't have to interact with the Box2D backend
			/*
			this->physicsMaterial.shape = Physics::ToB2BoxShape(
				tileSize * 0.5f,
				tileSize * 0.5f,
				Vector2F((column * tileSize + tileSize * 0.5f), (row * tileSize + tileSize * 0.5f)),
				angle);

			auto def = Physics::ToB2FixtureDef(physicsMaterial, reinterpret_cast<uintptr_t>(this));
			*/

			auto shape = new b2PolygonShape();

			const auto METER_PER_PIXEL = DeadFrame2D::Core::PhysicsEngine2D::GetPhysicsConfig().meterPerPixel;

			shape->SetAsBox(
				tileSize * 0.5f * METER_PER_PIXEL,
				tileSize * 0.5f * METER_PER_PIXEL,
				b2Vec2(
					(column * tileSize + tileSize * 0.5f) * METER_PER_PIXEL,
					(row * tileSize + tileSize * 0.5f) * METER_PER_PIXEL),
				angle);

			this->physicsMaterial.shape = shape;

			b2FixtureDef b2FDef;

			b2FDef.shape = physicsMaterial.shape;
			b2FDef.friction = physicsMaterial.friction;
			b2FDef.restitution = physicsMaterial.restitution;
			b2FDef.restitutionThreshold = physicsMaterial.restitutionThreshold;
			b2FDef.density = physicsMaterial.density;
			b2FDef.isSensor = physicsMaterial.isSensor;
			b2FDef.filter.categoryBits = physicsMaterial.filter.categoryBits;
			b2FDef.filter.groupIndex = physicsMaterial.filter.groupIndex;
			b2FDef.filter.maskBits = physicsMaterial.filter.maskBits;
			b2FDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

			assert(b2FDef.shape != nullptr && "Shape must not be null");

			fixtures.push_back(rigidBody->CreateFixture(&b2FDef));

			// Clean up before creating another shape
			delete this->physicsMaterial.shape;
			this->physicsMaterial.shape = nullptr;
		}
	}

	isDirty = false;
}