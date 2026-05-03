#pragma once
#include <Core/Math/Vector2.h>
#include <Data/Components/UI/Button/ButtonCallback.h>
#include <Engine/ECS/Entity/Component/Core/GameComponent.h>


class MenuManager;


class MenuFunctions : public DF2D::Engine::GameComponent
{
	TYPE_INFO(MenuFunctions, DF2D::Engine::GameComponent);


private:
	void MakeAudioPlayAndDestroyCallback(
		const std::string_view& audioPath,
		const DF2D::Core::Vector2F& position,
		float volume,
		bool isMusic,
		bool loop,
		float destroyDelaySeconds);


public:
	MenuFunctions() = default;

	~MenuFunctions() = default;


	DF2D::Data::ButtonCallback LoadMenu();

	DF2D::Data::ButtonCallback LoadGame();

	DF2D::Data::ButtonCallback ShowCredits(const DF2D::Engine::ComponentHandle<MenuManager>& menuManager);

	DF2D::Data::ButtonCallback ExitGame();

	DF2D::Data::ButtonCallback SelectUI();
};