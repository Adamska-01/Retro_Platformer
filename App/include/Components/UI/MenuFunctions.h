#pragma once
#include <Core/Math/Vector2.h>
#include <Data/Components/UI/Button/ButtonCallback.h>
#include <Engine/Components/GameComponent.h>


class MenuManager;


class MenuFunctions : public DeadFrame2D::Engine::GameComponent
{
	TYPE_INFO(MenuFunctions, DeadFrame2D::Engine::GameComponent);


private:
	void MakeAudioPlayAndDestroyCallback(
		const std::string_view& audioPath,
		const DeadFrame2D::Core::Vector2F& position,
		float volume,
		bool isMusic,
		bool loop,
		float destroyDelaySeconds);


public:
	MenuFunctions() = default;

	~MenuFunctions() = default;


	DeadFrame2D::Data::ButtonCallback LoadMenu();

	DeadFrame2D::Data::ButtonCallback LoadGame();

	DeadFrame2D::Data::ButtonCallback ShowCredits(const DeadFrame2D::Engine::ComponentHandle<MenuManager>& menuManager);

	DeadFrame2D::Data::ButtonCallback ExitGame();

	DeadFrame2D::Data::ButtonCallback SelectUI();
};