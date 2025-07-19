#include "Application.h"
#include <Scenes/MainMenuScene.h>
#include <SubSystems/Window.h>


Application::Application()
{
	Window::SetWindowTitle("Retro Platformer");

	SceneManager::LoadScene<MainMenuScene>();
}