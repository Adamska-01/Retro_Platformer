#pragma once
#include "GameObject.h"
#include "Models/Map/TileMapModel.h"


class GameMap : public GameObject
{
private:
	std::shared_ptr<TileMapModel> tileMapModel;


public:
	GameMap(std::shared_ptr<TileMapModel> tileMapModel);


	virtual void ConstructGameObject() override;
};