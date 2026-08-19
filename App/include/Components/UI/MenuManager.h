#pragma once
#include "Components/UI/Abstractions/MenuBase.h"
#include <Data/UI/MenuID.h>
#include <Engine/ECS/Entity/Component/Core/GameComponent.h>
#include <Engine/ECS/Entity/Component/Handle/ComponentHandle.h>
#include <unordered_map>


namespace DF2D::Core
{
	class InputActionView;
}


class MenuManager : public DF2D::Engine::GameComponent
{
	TYPE_INFO(MenuManager, DF2D::Engine::GameComponent);


private:
	std::unordered_map<MenuID, DF2D::Engine::ComponentHandle<MenuBase>> allMenus;

	std::vector<DF2D::Engine::ComponentHandle<MenuBase>> activeMenus;


	void MoveInputHandler(const DF2D::Core::InputActionView& inputAction);

	void ConfirmInputHandler(const DF2D::Core::InputActionView& inputAction);

	void BackInputHandler(const DF2D::Core::InputActionView& inputAction);


public:
	MenuManager();

	~MenuManager() = default;


	void Start() override;


	void ShowMenu(MenuID menuID);

	void ShowMenu(DF2D::Engine::ComponentHandle<MenuBase> menu);

	void HideMenu(MenuID menuID);

	void HideMenu(DF2D::Engine::ComponentHandle<MenuBase> menu);

	void HideAll();

	void RegisterMenu(MenuID menuID, DF2D::Engine::ComponentHandle<MenuBase> menu);

	DF2D::Engine::ComponentHandle<MenuBase> GetMenu(MenuID menuID);

	const std::vector<DF2D::Engine::ComponentHandle<MenuBase>>& GetActiveMenus();
};