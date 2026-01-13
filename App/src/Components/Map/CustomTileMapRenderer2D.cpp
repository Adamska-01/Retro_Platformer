#include "Components/Map/CustomTileMapRenderer2D.h"
#include <Core/SubSystems/Systems/Rendering/Renderer.h>
#include <Core/SubSystems/Systems/Rendering/RenderSystem.h>
#include <Engine/Components/Transform.h>
#include <Engine/Entity/GameObject.h>
#include <Utilities/Debugging/Guards.h>


using namespace DeadFrame2D::Core;
using namespace DeadFrame2D::Data;
using namespace DeadFrame2D::Engine;
using namespace DeadFrame2D::Utilities;


CustomTileMapRenderer2D::CustomTileMapRenderer2D(std::shared_ptr<TileMapModel> tileMap, bool extendMapToRenderTarget)
{
	this->tileMap = tileMap;

	if (!extendMapToRenderTarget)
		return;

	auto width = static_cast<int>(tileMap->layout[0].size());
	auto height = static_cast<int>(tileMap->layout.size());

	Renderer::SetResolutionTarget({ width * tileMap->tileRenderSize, height * tileMap->tileRenderSize });
}

void CustomTileMapRenderer2D::Init()
{
	transform = Guard::AgainstNullAssignment(GetGameObject()->GetComponent<Transform>(), NAME_OF(transform));
}

void CustomTileMapRenderer2D::Draw()
{
	const auto& tileLayout = tileMap->layout;
	const auto tileSize = tileMap->textureTileSize;
	const auto tileRenderSize = tileMap->tileRenderSize;

	auto srcRect = SDL_Rect
	{ 
		0, 
		0, 
		tileSize,
		tileSize
	};

	auto destRect = SDL_FRect
	{ 
		0.0f, 
		0.0f, 
		static_cast<float>(tileRenderSize),
		static_cast<float>(tileRenderSize)
	};

	auto startPos = transform->GetWorldPosition();
	auto rotation = transform->GetWorldRotation();

	auto mapWidth = tileLayout.size();
	auto mapHeight = tileLayout[0].size();

	auto batchData = SpriteBatchRenderData();
	batchData.spriteBatch.reserve(mapWidth * mapHeight);

	// TODO: optimize and draw only what's visible in the camera
	for (auto row = 0; row < mapWidth; row++)
	{
		for (auto column = 0; column < mapHeight; column++)
		{
			const auto& drawCoordinates = tileMap->tileDrawCoordinates[tileMap->layout[row][column]];

			srcRect.x = drawCoordinates.x * srcRect.w + drawCoordinates.x;
			srcRect.y = drawCoordinates.y * srcRect.h + drawCoordinates.y;

			destRect.x = startPos.x + column * destRect.w;
			destRect.y = startPos.y + row * destRect.h;

			auto renderData = SpriteRenderData
			{
				.texture = tileMap->tileSet.tileSetTexture.get(),
				.srcRect = srcRect,
				.destRect = destRect,
				.rotation = rotation
			};

			batchData.spriteBatch.push_back(renderData);
		}
	}

	renderTask.renderData = std::move(batchData);

	RenderSystem::Submit(renderTask);
}

Vector2I CustomTileMapRenderer2D::GetMapFullSize()
{
	auto mapHeight = tileMap->layout.size();
	auto mapWidth = tileMap->layout[0].size();

	return Vector2I(mapWidth * tileMap->tileRenderSize, mapHeight * tileMap->tileRenderSize);
}