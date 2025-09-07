#pragma once
#include "Components/Map/CustomTileMapRenderer2D.h"
#include <Engine/Components/Collisions/Tile/TileCollider2D.h>


class b2Fixture;


class CustomTileMapCollider2D : public TileCollider2D<CustomTileMapRenderer2D>
{
private:
	void DeleteFixtures();


protected:
	std::vector<std::vector<char>> layout;

	std::vector<char> collidableTiles;

	std::vector<b2Fixture*> fixtures;

	int tileSize;


	virtual void RebuildFixture() override;


public:
	CustomTileMapCollider2D(const PhysicsMaterial& physicsMaterial = PhysicsMaterial());

	virtual ~CustomTileMapCollider2D() override;


	virtual void Init() override;
};