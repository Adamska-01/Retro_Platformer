#include "Application.h"
#include <Core/Context/Systems/Window/Window.h>
#include <Engine/ECS/System/Scene/SceneManager.h>
#include <Scenes/MainMenuScene.h>


using namespace DF2D::Core;
using namespace DF2D::Engine;


Application::Application()
{
	Window::SetWindowTitle("Retro Platformer");

	SceneManager::LoadScene<MainMenuScene>();
}