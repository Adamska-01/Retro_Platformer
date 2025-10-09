#include "Application.h"
#include <Core/SubSystems/Systems/Window.h>
#include <Engine/SceneSystem/SceneManager.h>
#include <Scenes/MainMenuScene.h>


using namespace DeadFrame2D::Core;
using namespace DeadFrame2D::Engine;


Application::Application()
{
	Window::SetWindowTitle("Retro Platformer");

	SceneManager::LoadScene<MainMenuScene>();
}