#pragma once
#include "Models/Map/TileMapModel.h"
#include <Engine/ECS/Entity/Object/Core/GameObject.h>


class GameMap : public DF2D::Engine::GameObject
{
private:
	std::shared_ptr<TileMapModel> tileMapModel;


public:
	GameMap(std::shared_ptr<TileMapModel> tileMapModel);


	virtual void ConstructGameObject() override;
};