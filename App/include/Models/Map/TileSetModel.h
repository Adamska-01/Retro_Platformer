#pragma once
#include <Core/SubSystems/Systems/TextureManager.h>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>


class TileSetModel
{
private:
	void LoadTexture()
	{
		if (tileSetSource.empty())
			return;

		tileSetTexture = TextureManager::LoadTexture(tileSetSource);
	}


public:
	/** @brief The source path or identifier of the tile map data (e.g., a file name or asset key). */
	std::string tileSetSource = "";

	std::shared_ptr<SDL_Texture> tileSetTexture;


	friend void from_json(const nlohmann::json& j, TileSetModel& model)
	{
		j.at("tileSetSource").get_to(model.tileSetSource);
		
		model.LoadTexture();
	}

	friend void to_json(nlohmann::json& j, const TileSetModel& model)
	{
		j = nlohmann::json
		{
			{ "tileSetSource", model.tileSetSource }
		};
	}
};