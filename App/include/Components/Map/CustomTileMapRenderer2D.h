#pragma once
#include <Core/Math/Vector2.h>
#include <Engine/ECS/Component/Rendering/TileMap/Abstractions/TileMapRenderer.h>
#include <Engine/ECS/Entity/Component/Handle/ComponentHandle.h>
#include <Models/Map/TileMapModel.h>


namespace DF2D::Engine
{
	class Transform;
}


class CustomTileMapRenderer2D : public DF2D::Engine::TileMapRenderer<std::shared_ptr<TileMapModel>>
{
	TYPE_INFO(CustomTileMapRenderer2D, DF2D::Engine::TileMapRenderer<std::shared_ptr<TileMapModel>>);


private:
	DF2D::Engine::ComponentHandle<DF2D::Engine::Transform> transform;


public:
	CustomTileMapRenderer2D(std::shared_ptr<TileMapModel> tileMap, bool extendMapToRenderTarget = false);


	virtual void Init() override;

	virtual void Draw() override;


	DF2D::Core::Vector2I GetMapFullSize();
};