#pragma once
#include "Models/Map/EntityPositionsModel.h"
#include "Models/Map/TileDrawCoordinateModel.h"
#include "Models/Map/TileSetModel.h"
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <vector>


/**
 * @brief Represents the full tilemap including layout and tile rendering data.
 */
class TileMapModel
{
public:
	TileSetModel tileSet;

	/** @brief The size in pixels used to render the single tile. */
	int tileRenderSize = 32;

	/** @brief The size of the tile portion in the texture. */
	int textureTileSize = 32;

	/** @brief The grid layout where each character represents a tile type. */
	std::vector<std::vector<char>> layout;

	/** @brief List of tile characters that are considered collidable. */
	std::vector<char> collidableTiles;

	/** @brief Mapping from tile character to draw information. */
	std::unordered_map<char, TileDrawCoordinateModel> tileDrawCoordinates;

	/** @brief List of all the entity positions. */
	EntityPositionsModel entityPositions;
};


// Custom to_json
inline void to_json(nlohmann::json& j, const TileMapModel& t) 
{
	// Convert layout to vector of vector of strings
	std::vector<std::vector<std::string>> layoutStr;

	for (const auto& row : t.layout) 
	{
		std::vector<std::string> rowStr;

		for (char c : row) 
		{
			rowStr.push_back(std::string(1, c));
		}

		layoutStr.push_back(rowStr);
	}

	// Convert collidableTiles to vector of strings
	std::vector<std::string> collidablesStr;
	for (char c : t.collidableTiles) 
	{
		collidablesStr.push_back(std::string(1, c));
	}

	// Convert tileDrawCoordinates keys to strings
	std::unordered_map<std::string, TileDrawCoordinateModel> tileDrawCoordsStr;
	for (const auto& [key, value] : t.tileDrawCoordinates) 
	{
		tileDrawCoordsStr[std::string(1, key)] = value;
	}

	j = nlohmann::json
	{
		{"tileSet", t.tileSet},
		{"tileRenderSize", t.tileRenderSize},
		{"textureTileSize", t.textureTileSize},
		{"layout", layoutStr},
		{"collidableTiles", collidablesStr},
		{"tileDrawCoordinates", tileDrawCoordsStr},
		{"entityPositions", t.entityPositions}
	};
}

// Custom from_json
inline void from_json(const nlohmann::json& j, TileMapModel& t) 
{
	j.at("tileSet").get_to(t.tileSet);
	j.at("tileRenderSize").get_to(t.tileRenderSize);
	j.at("textureTileSize").get_to(t.textureTileSize);
	j.at("entityPositions").get_to(t.entityPositions);

	// Parse layout
	t.layout.clear();
	for (const auto& row : j.at("layout")) 
	{
		std::vector<char> rowChars;
		for (const auto& s : row) 
		{
			std::string str = s.get<std::string>();
		
			if (str.size() != 1)
			{
				throw std::runtime_error("Expected single-character string in layout.");
			}

			rowChars.push_back(str[0]);
		}

		t.layout.push_back(rowChars);
	}

	// Parse collidableTiles
	t.collidableTiles.clear();
	for (const auto& s : j.at("collidableTiles")) 
	{
		std::string str = s.get<std::string>();

		if (str.size() != 1)
		{
			throw std::runtime_error("Expected single-character string in collidableTiles.");
		}

		t.collidableTiles.push_back(str[0]);
	}

	// Parse tileDrawCoordinates
	t.tileDrawCoordinates.clear();
	for (auto it = j.at("tileDrawCoordinates").begin(); it != j.at("tileDrawCoordinates").end(); ++it) 
	{
		const std::string& key = it.key();

		if (key.size() != 1)
		{
			throw std::runtime_error("Expected single-character key in tileDrawCoordinates.");
		}

		t.tileDrawCoordinates[key[0]] = it.value().get<TileDrawCoordinateModel>();
	}
}