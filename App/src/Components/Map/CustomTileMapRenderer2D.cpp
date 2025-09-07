#include "Components/Map/CustomTileMapRenderer2D.h"
#include <Core/SubSystems/Systems/Renderer.h>
#include <Core/SubSystems/Systems/TextureManager.h>
#include <Engine/Components/Transform.h>
#include <Engine/Entity/GameObject.h>


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
	transform = OwningObject.lock()->GetComponent<Transform>();
}

void CustomTileMapRenderer2D::Start()
{

}

void CustomTileMapRenderer2D::Update(float dt)
{

}

void CustomTileMapRenderer2D::Draw()
{
	const auto& tileLayout = tileMap->layout;

	SDL_Rect srcRect{ 0, 0, tileMap->textureTileSize, tileMap->textureTileSize };
	SDL_Rect destRect{ 0, 0, tileMap->tileRenderSize, tileMap->tileRenderSize };

	auto startPos = transform->GetWorldPosition();
	auto rotation = transform->GetWorldRotation();

	auto mapWidth = tileLayout.size();
	auto mapHeight = tileLayout[0].size();

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

			TextureManager::DrawTextureWorldSpace(tileMap->tileSet.tileSetTexture, &srcRect, &destRect, rotation);
		}
	}
}

Vector2I CustomTileMapRenderer2D::GetMapFullSize()
{
	auto mapHeight = tileMap->layout.size();
	auto mapWidth = tileMap->layout[0].size();

	return Vector2I(mapWidth * tileMap->tileRenderSize, mapHeight * tileMap->tileRenderSize);
}