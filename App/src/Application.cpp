#include "Application.h"
#include <Core/SubSystems/Systems/Window.h>
#include <Scenes/MainMenuScene.h>


Application::Application()
{
	Window::SetWindowTitle("Retro Platformer");

	SceneManager::LoadScene<MainMenuScene>();
}