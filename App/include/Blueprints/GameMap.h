#pragma once
#include "Models/Map/TileMapModel.h"
#include <Engine/Entity/GameObject.h>


class GameMap : public GameObject
{
private:
	std::shared_ptr<TileMapModel> tileMapModel;


public:
	GameMap(std::shared_ptr<TileMapModel> tileMapModel);


	virtual void ConstructGameObject() override;
};