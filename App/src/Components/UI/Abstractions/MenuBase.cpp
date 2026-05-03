#include "Components/UI/Abstractions/MenuBase.h"
#include "Components/UI/MenuManager.h"
#include <Engine/ECS/Entity/Component/Core/UI/Abstractions/IInteractableUI.h>
#include <Engine/ECS/Entity/Object/Core/GameObject.h>
#include <Engine/ECS/System/Scene/SceneManager.h>
#include <Utilities/Debugging/Guards.h>


using namespace DF2D::Engine;
using namespace DF2D::Utilities;


void MenuBase::Navigate(std::function<ComponentHandle<IInteractableUI>(ComponentHandle<IInteractableUI>)> getNext)
{
	if (selectedInteractable == nullptr)
	{
		if (!allInteractables.empty())
		{
			selectedInteractable = allInteractables.front();

			selectedInteractable->OnPointerEnter();
		}

		return;
	}

	auto next = getNext(selectedInteractable);

	if (next == nullptr)
		return;

	selectedInteractable->OnPointerExit();
	next->OnPointerEnter();

	selectedInteractable = next;
}

MenuBase::MenuBase()
{
	allInteractables.clear();

	menuManager = nullptr;
	previousMenu = nullptr;
	selectedInteractable = nullptr;
}

void MenuBase::Init()
{
	menuManager = Guard::AgainstNullAssignment(SceneManager::FindObjectOfType<MenuManager>(), NAME_OF(menuManager));
	
	allInteractables = GetGameObject()->GetComponentsInChildren<IInteractableUI>(true);
}

void MenuBase::Show()
{
	GetGameObject()->SetActive(true);
}

void MenuBase::Hide()
{
	GetGameObject()->SetActive(false);
}

void MenuBase::NavigateLeft()
{
	Navigate([](ComponentHandle<IInteractableUI> current)
		{
			return current->GetLeftInteractable();
		});
}

void MenuBase::NavigateRight()
{
	Navigate([](ComponentHandle<IInteractableUI> current)
		{
			return current->GetRightInteractable();
		});
}

void MenuBase::NavigateUp()
{
	Navigate([](ComponentHandle<IInteractableUI> current)
		{
			return current->GetUpInteractable();
		});
}

void MenuBase::NavigateDown()
{
	Navigate([](ComponentHandle<IInteractableUI> current)
		{
			return current->GetDownInteractable();
		});
}

void MenuBase::Confirm()
{
	if (selectedInteractable == nullptr)
	{
		if (!allInteractables.empty())
		{
			selectedInteractable = allInteractables.front();

			selectedInteractable->OnPointerEnter();
		}

		return;
	}

	selectedInteractable->OnPointerUp();
}

void MenuBase::GoBack()
{
	if (previousMenu == nullptr)
		return;

	menuManager->HideMenu(GetHandleAs<MenuBase>());
	menuManager->ShowMenu(previousMenu);
}

void MenuBase::SetPreviousMenu(ComponentHandle<MenuBase> previousMenu)
{
	this->previousMenu = previousMenu;
}