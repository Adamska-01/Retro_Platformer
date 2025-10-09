#pragma once
#include "Tools/FileSystem/ResolvedPath.h"
#include "Tools/FileSystem/ResourceMount.h"
#include <string_view>


namespace AssetPaths
{
	namespace Folders
	{
		// Keys
		inline constexpr std::string_view APP_FONTS_ALIAS = "app_fonts";

		inline constexpr std::string_view APP_ENTITY_SPRITES_ALIAS = "app_entity_sprites";

		inline constexpr std::string_view APP_MAPS_SPRITES_ALIAS = "app_maps_sprites";

		inline constexpr std::string_view APP_MAP_LEVELS_ALIAS = "app_map_levels";

		inline constexpr std::string_view APP_AUDIO_ALIAS = "app_audio";

		inline constexpr std::string_view APP_ASSETS_ALIAS = "app";


		inline static const Shared::Tools::ResourceMount APP_FONTS = { std::string(APP_FONTS_ALIAS), "App/Assets/Fonts/" };

		inline static const Shared::Tools::ResourceMount APP_ENTITY_SPRITES = { std::string(APP_ENTITY_SPRITES_ALIAS), "App/Assets/Sprites/Entities/" };

		inline static const Shared::Tools::ResourceMount APP_MAP_SPRITES = { std::string(APP_MAPS_SPRITES_ALIAS), "App/Assets/Sprites/Maps/" };

		inline static const Shared::Tools::ResourceMount APP_MAP_LEVELS = { std::string(APP_MAP_LEVELS_ALIAS), "App/Assets/Levels/" };

		inline static const Shared::Tools::ResourceMount APP_AUDIO = { std::string(APP_AUDIO_ALIAS), "App/Assets/Audio/" };

		inline static const Shared::Tools::ResourceMount APP_ASSETS = { std::string(APP_ASSETS_ALIAS), "App/Assets/" };
	}


	namespace Files
	{
		// Fonts
		inline const Shared::Tools::ResolvedPath GAMEPLAY_FONT = { std::string(Folders::APP_FONTS_ALIAS), "Gameplay.ttf" };


		// Sprites
		inline const Shared::Tools::ResolvedPath PLAYER_IDLE_SPRITE = { std::string(Folders::APP_ENTITY_SPRITES_ALIAS), "Player_Idle.png" };

		inline const Shared::Tools::ResolvedPath PLAYER_RUN_SPRITE = { std::string(Folders::APP_ENTITY_SPRITES_ALIAS), "Player_Run.png" };

		inline const Shared::Tools::ResolvedPath GROUND_ENEMY_SPRITE = { std::string(Folders::APP_ENTITY_SPRITES_ALIAS), "Ground_Enemy.png" };

		inline const Shared::Tools::ResolvedPath FLY_ENEMY_SPRITE = { std::string(Folders::APP_ENTITY_SPRITES_ALIAS), "Fly_Enemy.png" };

		inline const Shared::Tools::ResolvedPath COIN_SPRITE = { std::string(Folders::APP_ENTITY_SPRITES_ALIAS), "Coin.png" };

		inline const Shared::Tools::ResolvedPath KEY_SPRITE = { std::string(Folders::APP_ENTITY_SPRITES_ALIAS), "Key.png" };

		inline const Shared::Tools::ResolvedPath TILES_SPRITE = { std::string(Folders::APP_MAPS_SPRITES_ALIAS), "Tiles.png" };


		// Maps
		inline const Shared::Tools::ResolvedPath MAP_LV_1 = { std::string(Folders::APP_MAP_LEVELS_ALIAS), "Lv1.json" };


		// Audio
		inline const Shared::Tools::ResolvedPath SELECT_UI = { std::string(Folders::APP_AUDIO_ALIAS), "snd_system_menu_select_move.ogg" };

		inline const Shared::Tools::ResolvedPath CONFIRM_UI = { std::string(Folders::APP_AUDIO_ALIAS), "snd_system_menu_select_confirm.ogg" };

		inline const Shared::Tools::ResolvedPath COIN_TAKEN = { std::string(Folders::APP_AUDIO_ALIAS), "snd_opening_press.ogg" };

		inline const Shared::Tools::ResolvedPath PLAYER_JUMP = { std::string(Folders::APP_AUDIO_ALIAS), "snd_chick_jump.ogg" };

		inline const Shared::Tools::ResolvedPath ENEMY_KILLED = { std::string(Folders::APP_AUDIO_ALIAS), "snd_boss_damaged.ogg" };

		inline const Shared::Tools::ResolvedPath PLAYER_KILLED = { std::string(Folders::APP_AUDIO_ALIAS), "snd_boss_fall_t1.ogg" };

		inline const Shared::Tools::ResolvedPath GAME_OVER = { std::string(Folders::APP_AUDIO_ALIAS), "GameOver.ogg" };

		inline const Shared::Tools::ResolvedPath VICTORY = { std::string(Folders::APP_AUDIO_ALIAS), "Victory.mp3" };


		// Other
		inline const Shared::Tools::ResolvedPath CREDITS = { std::string(Folders::APP_ASSETS_ALIAS), "credits.txt" };
	}
}