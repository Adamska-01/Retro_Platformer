#include "Application.h"
#include "Scenes/ExampleScene.h"
#include <SubSystems/Window.h>


Application::Application()
{
	Window::SetWindowTitle("Hello World!");

	SceneManager::LoadScene<ExampleScene>();
}