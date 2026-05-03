#include "Components/UI/MenuManager.h"
#include <algorithm>
#include <Core/Context/Systems/Input/Actions/InputActionView.h>
#include <Core/Context/Systems/Input/Actions/RuntimeInputAction.h>
#include <Engine/ECS/Component/Input/PlayerInput.h>
#include <Engine/ECS/System/Scene/SceneManager.h>
#include <Utilities/Debugging/Guards.h>
#include <Utilities/Helpers/Events/EventHelpers.h>


using namespace DF2D::Core;
using namespace DF2D::Engine;
using namespace DF2D::Utilities;


MenuManager::MenuManager()
	: allMenus(),
	activeMenus()
{
}

void MenuManager::MoveInputHandler(const InputActionView& inputAction)
{
	if (!inputAction.IsStarted())
		return;

	auto dir = inputAction.ReadValue<Vector2F>();

	for (const auto& currentMenu : activeMenus)
	{
		if (dir.y > 0.0f)
		{
			currentMenu->NavigateUp();
		}
		if (dir.y < 0.0f)
		{
			currentMenu->NavigateDown();
		}
		if (dir.x < 0.0f)
		{
			currentMenu->NavigateLeft();
		}
		if (dir.x > 0.0f)
		{
			currentMenu->NavigateRight();
		}
	}
}

void MenuManager::ConfirmInputHandler(const InputActionView& inputAction)
{
	if (!inputAction.IsCancelled())
		return;

	for (const auto& currentMenu : activeMenus)
	{
		currentMenu->Confirm();
	}
}

void MenuManager::BackInputHandler(const InputActionView& inputAction)
{
	if (!inputAction.IsCancelled())
		return;

	for (const auto& currentMenu : activeMenus)
	{
		currentMenu->GoBack();
	}
}

void MenuManager::Start()
{
	// Input Registration
	auto playerInput = Guard::AgainstNullAssignment(SceneManager::FindObjectOfType<PlayerInput>(), NAME_OF(playerInput));

	playerInput->RegisterAction("Default", "Move", GetHandle(), EventHelpers::BindFunction(this, &MenuManager::MoveInputHandler));
	playerInput->RegisterAction("Default", "Confirm", GetHandle(), EventHelpers::BindFunction(this, &MenuManager::ConfirmInputHandler));
	playerInput->RegisterAction("Default", "Back", GetHandle(), EventHelpers::BindFunction(this, &MenuManager::BackInputHandler));
}

void MenuManager::ShowMenu(MenuID menuID)
{
	auto it = allMenus.find(menuID);

	if (it == allMenus.end())
		return;

	auto& menu = it->second;

	menu->Show();
	activeMenus.push_back(menu);
}

void MenuManager::ShowMenu(ComponentHandle<MenuBase> menu)
{
	if (menu == nullptr)
		return;

	// Avoid showing a menu that's already active
	auto it = std::find(activeMenus.begin(), activeMenus.end(), menu);

	if (it != activeMenus.end())
		return;

	menu->Show();
	activeMenus.push_back(menu);
}

void MenuManager::HideMenu(MenuID menuID)
{
	auto it = allMenus.find(menuID);

	if (it == allMenus.end())
		return;

	auto menu = it->second;

	menu->Hide();

	activeMenus.erase(
		std::remove(
			activeMenus.begin(),
			activeMenus.end(),
			menu),
		activeMenus.end());
}

void MenuManager::HideMenu(ComponentHandle<MenuBase> menu)
{
	if (menu == nullptr)
		return;

	menu->Hide();

	activeMenus.erase(
		std::remove(
			activeMenus.begin(),
			activeMenus.end(),
			menu),
		activeMenus.end());
}

void MenuManager::HideAll()
{
	for (auto& menu : allMenus)
	{
		menu.second->Hide();
	}

	activeMenus.clear();
}

void MenuManager::RegisterMenu(MenuID menuID, ComponentHandle<MenuBase> menu)
{
	allMenus[menuID] = menu;
}

ComponentHandle<MenuBase> MenuManager::GetMenu(MenuID menuID)
{
	auto it = allMenus.find(menuID);

	return it != allMenus.end() ? it->second : ComponentHandle<MenuBase>();
}

const std::vector<ComponentHandle<MenuBase>>& MenuManager::GetActiveMenus()
{
	return activeMenus;
}