#include "Components/Map/CustomTileMapRenderer2D.h"
#include <Core/Context/Systems/Graphics/TextureManager.h>
#include <Core/Context/Systems/Rendering/Renderer.h>
#include <Core/Context/Systems/Rendering/RenderSystem.h>
#include <Engine/ECS/Component/Transform.h>
#include <Engine/ECS/Entity/Object/Core/GameObject.h>
#include <Utilities/Debugging/Guards.h>


using namespace DF2D::Core;
using namespace DF2D::Data;
using namespace DF2D::Engine;
using namespace DF2D::Utilities;


CustomTileMapRenderer2D::CustomTileMapRenderer2D(std::shared_ptr<TileMapModel> tileMap, bool extendMapToRenderTarget)
{
	this->tileMap = tileMap;
	this->extendMapToRenderTarget = extendMapToRenderTarget;
}

void CustomTileMapRenderer2D::Init()
{
	transform = Guard::AgainstNullAssignment(GetGameObject()->GetComponent<Transform>(), NAME_OF(transform));
	textureManager = GetGameObject()->CoreContext().textureManager;

	if (extendMapToRenderTarget)
	{
		auto renderer = GetGameObject()->CoreContext().renderer;

		if (renderer != nullptr)
		{
			auto width = static_cast<int>(tileMap->layout[0].size());
			auto height = static_cast<int>(tileMap->layout.size());

			renderer->SetResolutionTarget({ width * tileMap->tileRenderSize, height * tileMap->tileRenderSize });
		}
	}

	tileMap->tileSet.LoadTexture(textureManager);
}

void CustomTileMapRenderer2D::Draw()
{
	const auto& tileLayout = tileMap->layout;
	const auto tileSize = tileMap->textureTileSize;
	const auto tileRenderSize = tileMap->tileRenderSize;

	auto srcRect = RectI
	{
		0,
		0,
		tileSize,
		tileSize
	};

	auto destRect = RectF
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
				.texture = tileMap->tileSet.tileSetTexture,
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