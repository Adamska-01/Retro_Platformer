#pragma once
#include "Components/UI/Abstractions/MenuBase.h"
#include <Data/UI/MenuID.h>
#include <Engine/Components/GameComponent.h>
#include <Engine/Entity/ComponentHandle.h>
#include <unordered_map>


class MenuManager : public DeadFrame2D::Engine::GameComponent
{
	TYPE_INFO(MenuManager, DeadFrame2D::Engine::GameComponent);


private:
	std::unordered_map<MenuID, DeadFrame2D::Engine::ComponentHandle<MenuBase>> allMenus;

	std::vector<DeadFrame2D::Engine::ComponentHandle<MenuBase>> activeMenus;


public:
	MenuManager();

	~MenuManager() = default;


	virtual void Update(float deltaTime) override;


	void ShowMenu(MenuID menuID);

	void ShowMenu(DeadFrame2D::Engine::ComponentHandle<MenuBase> menu);

	void HideMenu(MenuID menuID);

	void HideMenu(DeadFrame2D::Engine::ComponentHandle<MenuBase> menu);

	void HideAll();

	void RegisterMenu(MenuID menuID, DeadFrame2D::Engine::ComponentHandle<MenuBase> menu);

	DeadFrame2D::Engine::ComponentHandle<MenuBase> GetMenu(MenuID menuID);

	const std::vector<DeadFrame2D::Engine::ComponentHandle<MenuBase>>& GetActiveMenus();
};