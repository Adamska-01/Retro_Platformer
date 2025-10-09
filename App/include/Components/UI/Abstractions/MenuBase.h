#pragma once
#include <Engine/Components/GameComponent.h>
#include <vector>


class MenuManager;

namespace DeadFrame2D::Engine
{
	class IInteractableUI;
}


class MenuBase : public DeadFrame2D::Engine::GameComponent
{
private:
	void Navigate(DeadFrame2D::Engine::IInteractableUI* (*getNext)(DeadFrame2D::Engine::IInteractableUI*));


protected:
	MenuManager* menuManager;

	MenuBase* previousMenu;

	std::vector<DeadFrame2D::Engine::IInteractableUI*> allInteractables;

	DeadFrame2D::Engine::IInteractableUI* selectedInteractable;


public:
	MenuBase();

	virtual ~MenuBase() override = default;


	virtual void Init() override;

	virtual void Start() override;

	virtual void Update(float deltaTime) override;

	virtual void Draw() override;


	virtual void Show();

	virtual void Hide();


	//UI Navigation
	virtual void NavigateLeft();

	virtual void NavigateRight();

	virtual void NavigateUp();

	virtual void NavigateDown();

	virtual void Confirm();

	virtual void GoBack();


	void SetPreviousMenu(MenuBase* previousMenu);
};