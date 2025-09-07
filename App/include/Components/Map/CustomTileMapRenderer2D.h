#pragma once
#include <Core/Math/Vector2.h>
#include <Engine/Components/TileMap/TileMapRenderer.h>
#include <Models/Map/TileMapModel.h>


class Transform;


class CustomTileMapRenderer2D : public TileMapRenderer<std::shared_ptr<TileMapModel>>
{
private:
	Transform* transform;


public:
	CustomTileMapRenderer2D(std::shared_ptr<TileMapModel> tileMap, bool extendMapToRenderTarget = false);


	virtual void Init() override;

	virtual void Start() override;

	virtual void Update(float dt) override;

	virtual void Draw() override;


	Vector2I GetMapFullSize();
};