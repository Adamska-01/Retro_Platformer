#pragma once
#include <Core/Context/Systems/Graphics/TextureManager.h>
#include <Data/Systems/Graphics/TextureID.h>
#include <nlohmann/json.hpp>
#include <string>


class TileSetModel
{
public:
	/** @brief The source path or identifier of the tile map data (e.g., a file name or asset key). */
	std::string tileSetSource = "";

	DF2D::Data::TextureID tileSetTexture = 0;


	void LoadTexture(DF2D::Core::TextureManager* tm)
	{
		if (tileSetSource.empty() || !tm)
			return;

		tileSetTexture = tm->LoadTexture(tileSetSource);
	}


	friend void from_json(const nlohmann::json& j, TileSetModel& model)
	{
		j.at("tileSetSource").get_to(model.tileSetSource);
	}

	friend void to_json(nlohmann::json& j, const TileSetModel& model)
	{
		j = nlohmann::json
		{
			{ "tileSetSource", model.tileSetSource }
		};
	}
};