#include "Application.h"
#include <Core/Context/Systems/Window/Window.h>
#include <Engine/ECS/System/Scene/SceneManager.h>
#include <Scenes/MainMenuScene.h>


using namespace DF2D::Core;
using namespace DF2D::Engine;


Application::Application()
{
	auto coreCtx = SceneManager::GetCoreContext();
	coreCtx.window->SetWindowTitle("Retro Platformer");

	SceneManager::LoadScene<MainMenuScene>();
}