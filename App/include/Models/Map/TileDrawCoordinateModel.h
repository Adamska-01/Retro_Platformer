#pragma once
#include <nlohmann/json.hpp>


/**
 * @brief Contains the draw coordinates to draw a tile.
 */
class TileDrawCoordinateModel
{
public:
	/** @brief The x coordinate of the tile portion in the Texture. */
	int x = 0;

	/** @brief The y coordinate of the tile portion in the Texture. */
	int y = 0;


	NLOHMANN_DEFINE_TYPE_INTRUSIVE(TileDrawCoordinateModel, x, y)
};