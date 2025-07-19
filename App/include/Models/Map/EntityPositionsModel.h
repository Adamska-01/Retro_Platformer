#pragma once
#include "Models/Map/PositionModel.h"
#include <nlohmann/json.hpp>
#include <vector>


/** @brief All entity positions for a level. */
struct EntityPositionsModel
{
	PositionModel player;

	std::vector<PositionModel> groundEnemies;

	std::vector<PositionModel> flyEnemies;

	std::vector<PositionModel> coins;

	PositionModel key;


	NLOHMANN_DEFINE_TYPE_INTRUSIVE(EntityPositionsModel, player, groundEnemies, flyEnemies, coins, key)
};