#pragma once
#include <Core/Math/Vector2.h>
#include <Engine/Components/TileMap/TileMapRenderer.h>
#include <Engine/Entity/ComponentHandle.h>
#include <Models/Map/TileMapModel.h>


namespace DeadFrame2D::Engine
{
	class Transform;
}


class CustomTileMapRenderer2D : public DeadFrame2D::Engine::TileMapRenderer<std::shared_ptr<TileMapModel>>
{
	TYPE_INFO(CustomTileMapRenderer2D, DeadFrame2D::Engine::TileMapRenderer<std::shared_ptr<TileMapModel>>);


private:
	DeadFrame2D::Engine::ComponentHandle<DeadFrame2D::Engine::Transform> transform;


public:
	CustomTileMapRenderer2D(std::shared_ptr<TileMapModel> tileMap, bool extendMapToRenderTarget = false);


	virtual void Init() override;

	virtual void Draw() override;


	DeadFrame2D::Core::Vector2I GetMapFullSize();
};