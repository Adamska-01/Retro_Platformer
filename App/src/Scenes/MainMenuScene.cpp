#include "Components/UI/MenuManager.h"
#include "Components/UI/TextMeshScroller.h"
#include "Constants/AssetPaths.h"
#include "Scenes/MainMenuScene.h"
#include <Components/UI/MenuFunctions.h>
#include <Constants/Paths/ResourcePaths.h>
#include <Core/Context/Systems/Rendering/Renderer.h>
#include <Engine/Blueprints/UI/ButtonBlueprint.h>
#include <Engine/ECS/Component/Audio/AudioListener.h>
#include <Engine/ECS/Component/Input/PlayerInput.h>
#include <Engine/ECS/Component/Rendering/Camera/Camera.h>
#include <Engine/ECS/Component/Transform.h>
#include <Engine/ECS/Component/UI/Button.h>
#include <Engine/ECS/Component/UI/Canvas.h>
#include <Engine/ECS/Component/UI/Layout/VerticalLayoutGroup.h>
#include <Engine/ECS/Component/UI/TextMesh.h>
#include <Engine/ECS/Entity/Object/Core/GameObject.h>
#include <Utilities/IO/IO_Helpers.h>


using namespace DF2D::Constants;
using namespace DF2D::Core;
using namespace DF2D::Data;
using namespace DF2D::Engine;
using namespace DF2D::Utilities;


void MainMenuScene::Enter()
{
	auto renderTargetSize = Renderer::GetResolutionTarget();


	// Camera
	auto cameraObject = GameObject::Instantiate<GameObject>();
	cameraObject->AddComponent<Camera>();


	// UI
	auto canvasObject = GameObject::Instantiate<GameObject>();
	canvasObject->AddComponent<Canvas>();

	auto layoutPosition = Vector2F(renderTargetSize.x * 0.5f, renderTargetSize.y * 0.65f);

	// Create MenuManager and push the initial menu onto the stack
	auto menuManagerObject = GameObject::Instantiate<GameObject>();
	auto menuManagerComponent = menuManagerObject->AddComponent<MenuManager>();

	// Main Menu
	auto mainMenuObject = GameObject::Instantiate<GameObject>();
	auto mainMenuBase = mainMenuObject->AddComponent<MenuBase>();


	auto title = CreateText("Retro Platformer", AssetPaths::Files::GAMEPLAY_FONT);
	title->GetTransform()->SetWorldPosition(Vector2F(renderTargetSize.x * 0.5f, renderTargetSize.y * 0.2f));

	auto menuFunctions = GameObject::Instantiate<GameObject>()->AddComponent<MenuFunctions>();

	auto spButton = CreateButton("Play Game", AssetPaths::Files::GAMEPLAY_FONT, menuFunctions->LoadGame(), menuFunctions->SelectUI());
	auto creditsButton = CreateButton("Credits", AssetPaths::Files::GAMEPLAY_FONT, menuFunctions->ShowCredits(menuManagerComponent), menuFunctions->SelectUI());
	auto exitButton = CreateButton("Exit", AssetPaths::Files::GAMEPLAY_FONT, menuFunctions->ExitGame(), menuFunctions->SelectUI());

	spButton->GetComponent<Button>()->SetNavigableUpElement(exitButton->GetComponent<Button>());
	spButton->GetComponent<Button>()->SetNavigableDownElement(creditsButton->GetComponent<Button>());
	creditsButton->GetComponent<Button>()->SetNavigableUpElement(spButton->GetComponent<Button>());
	creditsButton->GetComponent<Button>()->SetNavigableDownElement(exitButton->GetComponent<Button>());
	exitButton->GetComponent<Button>()->SetNavigableUpElement(creditsButton->GetComponent<Button>());
	exitButton->GetComponent<Button>()->SetNavigableDownElement(spButton->GetComponent<Button>());

	auto mainMenuLayout = GameObject::Instantiate<GameObject>();

	mainMenuLayout->AddComponent<VerticalLayoutGroup>(20.0f, LayoutPadding());
	mainMenuLayout->GetComponent<Transform>()->SetWorldPosition(layoutPosition);
	spButton->SetParent(mainMenuLayout);
	creditsButton->SetParent(mainMenuLayout);
	exitButton->SetParent(mainMenuLayout);
	title->SetParent(mainMenuObject);
	mainMenuLayout->SetParent(mainMenuObject);

	// Credits Menu
	auto creditsText = IO_Helpers::LoadTextFile(AssetPaths::Files::CREDITS);

	auto creditsMenuObject = GameObject::Instantiate<GameObject>();
	creditsMenuObject->GetComponent<Transform>()->SetWorldScale(Vector2F(0.75f, 0.75f));
	auto creditsMenuBase = creditsMenuObject->AddComponent<MenuBase>();

	auto creditTextMeshObj = CreateText(creditsText, Paths::Files::CONSOLAS_FONT);
	auto creditTextMeshComponent = creditTextMeshObj->GetComponent<TextMesh>();
	creditsMenuObject->AddComponent<TextMeshScroller>(creditTextMeshComponent);

	creditTextMeshObj->GetComponent<Transform>()->SetWorldPosition(Vector2F(renderTargetSize.x * 0.5f, renderTargetSize.y * 0.5f));

	creditTextMeshObj->SetParent(creditsMenuObject);

	mainMenuObject->SetParent(canvasObject);
	creditsMenuObject->SetParent(canvasObject);

	creditsMenuBase->SetPreviousMenu(mainMenuBase);

	// Register menus
	menuManagerComponent->RegisterMenu(MenuID::MAIN_MENU, mainMenuBase);
	menuManagerComponent->RegisterMenu(MenuID::CREDITS_MENU, creditsMenuBase);
	menuManagerComponent->HideAll();
	menuManagerComponent->ShowMenu(MenuID::MAIN_MENU);

	auto soundListenerObj = GameObject::Instantiate<GameObject>();
	soundListenerObj->AddComponent<AudioListener>();

	// Input
	auto playerInputObject = GameObject::Instantiate<GameObject>();
	auto playerInputComponent = playerInputObject->AddComponent<PlayerInput>("Player1");
	playerInputComponent->EnableActionMap("Default");
}