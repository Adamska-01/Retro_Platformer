#pragma once
#include "Components/UI/Abstractions/MenuBase.h"
#include <Components/GameComponent.h>
#include <Data/UI/MenuID.h>
#include <unordered_map>


class MenuManager : public GameComponent
{
private:
	std::unordered_map<MenuID, MenuBase*> allMenus;

	std::vector<MenuBase*> activeMenus;


public:
	MenuManager();

	~MenuManager() = default;


	virtual void Init() override;

	virtual void Start() override;

	virtual void Update(float deltaTime) override;

	virtual void Draw() override;


	void ShowMenu(MenuID menuID);

	void ShowMenu(MenuBase* menu);

	void HideMenu(MenuID menuID);

	void HideMenu(MenuBase* menu);

	void HideAll();

	void RegisterMenu(MenuID menuID, MenuBase* menu);

	MenuBase* GetMenu(MenuID menuID);

	const std::vector<MenuBase*>& GetActiveMenus();
};