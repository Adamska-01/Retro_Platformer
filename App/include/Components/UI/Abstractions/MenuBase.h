#pragma once
#include <Engine/Components/GameComponent.h>
#include <Engine/Entity/ComponentHandle.h>
#include <functional>
#include <vector>


class MenuManager;

namespace DeadFrame2D::Engine
{
	class IInteractableUI;
}


class MenuBase : public DeadFrame2D::Engine::GameComponent
{
	TYPE_INFO(MenuBase, DeadFrame2D::Engine::GameComponent);


private:
	void Navigate(std::function<DeadFrame2D::Engine::ComponentHandle<DeadFrame2D::Engine::IInteractableUI>(DeadFrame2D::Engine::ComponentHandle<DeadFrame2D::Engine::IInteractableUI>)> getNext);


protected:
	DeadFrame2D::Engine::ComponentHandle<MenuManager> menuManager;

	DeadFrame2D::Engine::ComponentHandle<MenuBase> previousMenu;

	std::vector<DeadFrame2D::Engine::ComponentHandle<DeadFrame2D::Engine::IInteractableUI>> allInteractables;

	DeadFrame2D::Engine::ComponentHandle<DeadFrame2D::Engine::IInteractableUI> selectedInteractable;


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


	void SetPreviousMenu(DeadFrame2D::Engine::ComponentHandle<MenuBase> previousMenu);
};