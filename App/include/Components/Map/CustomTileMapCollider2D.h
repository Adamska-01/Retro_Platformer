#pragma once
#include "Components/Map/CustomTileMapRenderer2D.h"
#include <Data/Components/Collision/PhysicsMaterial.h>
#include <Engine/ECS/Component/Collisions/Tile/TileCollider2D.h>


class CustomTileMapCollider2D : public DF2D::Engine::TileCollider2D<CustomTileMapRenderer2D>
{
	TYPE_INFO(CustomTileMapCollider2D, DF2D::Engine::TileCollider2D<CustomTileMapRenderer2D>);


private:
	void DeleteFixtures();


protected:
	std::vector<std::vector<char>> layout;

	std::vector<char> collidableTiles;

	std::vector<b2Fixture*> fixtures;

	int tileSize;


	virtual void RebuildFixture() override;


public:
	CustomTileMapCollider2D(const DF2D::Data::PhysicsMaterial& physicsMaterial = DF2D::Data::PhysicsMaterial());

	virtual ~CustomTileMapCollider2D() override;


	virtual void Init() override;
};