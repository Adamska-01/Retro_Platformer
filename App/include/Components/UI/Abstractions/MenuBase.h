#pragma once
#include <Engine/ECS/Entity/Component/Core/GameComponent.h>
#include <Engine/ECS/Entity/Component/Handle/ComponentHandle.h>
#include <functional>
#include <vector>


class MenuManager;

namespace DF2D::Engine
{
	class IInteractableUI;
}


class MenuBase : public DF2D::Engine::GameComponent
{
	TYPE_INFO(MenuBase, DF2D::Engine::GameComponent);


private:
	void Navigate(std::function<DF2D::Engine::ComponentHandle<DF2D::Engine::IInteractableUI>(DF2D::Engine::ComponentHandle<DF2D::Engine::IInteractableUI>)> getNext);


protected:
	DF2D::Engine::ComponentHandle<MenuManager> menuManager;

	DF2D::Engine::ComponentHandle<MenuBase> previousMenu;

	std::vector<DF2D::Engine::ComponentHandle<DF2D::Engine::IInteractableUI>> allInteractables;

	DF2D::Engine::ComponentHandle<DF2D::Engine::IInteractableUI> selectedInteractable;


public:
	MenuBase();

	virtual ~MenuBase() override = default;


	virtual void Init() override;


	virtual void Show();

	virtual void Hide();


	//UI Navigation
	virtual void NavigateLeft();

	virtual void NavigateRight();

	virtual void NavigateUp();

	virtual void NavigateDown();

	virtual void Confirm();

	virtual void GoBack();


	void SetPreviousMenu(DF2D::Engine::ComponentHandle<MenuBase> previousMenu);
};