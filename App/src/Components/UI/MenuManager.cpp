#include "Components/UI/MenuManager.h"
#include <algorithm>
#include <Core/SubSystems/Systems/Input/Input.h>


MenuManager::MenuManager()
	: allMenus(),
	activeMenus()
{
}

void MenuManager::Init()
{
}

void MenuManager::Start()
{

}

void MenuManager::Update(float deltaTime)
{
	for (auto currentMenu : activeMenus)
	{
		if (Input::IsButtonPressed(PlayerInputSlot::PLAYER_1, "Up")
			|| Input::IsButtonPressed(PlayerInputSlot::PLAYER_1, "Up2"))
		{
			currentMenu->NavigateUp();
		}
		if (Input::IsButtonPressed(PlayerInputSlot::PLAYER_1, "Down")
			|| Input::IsButtonPressed(PlayerInputSlot::PLAYER_1, "Down2"))
		{
			currentMenu->NavigateDown();
		}
		if (Input::IsButtonPressed(PlayerInputSlot::PLAYER_1, "Left")
			|| Input::IsButtonPressed(PlayerInputSlot::PLAYER_1, "Left2"))
		{
			currentMenu->NavigateLeft();
		}
		if (Input::IsButtonPressed(PlayerInputSlot::PLAYER_1, "Right")
			|| Input::IsButtonPressed(PlayerInputSlot::PLAYER_1, "Right2"))
		{
			currentMenu->NavigateRight();
		}
		if (Input::IsButtonPressed(PlayerInputSlot::PLAYER_1, "Jump")
			|| Input::IsButtonPressed(PlayerInputSlot::PLAYER_1, "Confirm"))
		{
			currentMenu->Confirm();
		}
		if (Input::IsButtonPressed(PlayerInputSlot::PLAYER_1, "Back"))
		{
			currentMenu->GoBack();
		}
	}
}

void MenuManager::Draw()
{

}

void MenuManager::ShowMenu(MenuID menuID)
{
	auto it = allMenus.find(menuID);

	if (it == allMenus.end())
		return;

	auto menu = it->second;

	menu->Show();
	activeMenus.push_back(menu);
}

void MenuManager::ShowMenu(MenuBase* menu)
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

void MenuManager::HideMenu(MenuBase* menu)
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
	for (auto* menu : activeMenus)
	{
		menu->Hide();
	}
	for (auto menu : allMenus)
	{
		menu.second->Hide();
	}

	activeMenus.clear();
}

void MenuManager::RegisterMenu(MenuID menuID, MenuBase* menu)
{
	allMenus[menuID] = menu;
}

MenuBase* MenuManager::GetMenu(MenuID menuID)
{
	auto it = allMenus.find(menuID);

	return it != allMenus.end() ? it->second : nullptr;
}

const std::vector<MenuBase*>& MenuManager::GetActiveMenus()
{
	return activeMenus;
}