#include "Components/UI/MenuManager.h"
#include "Components/UI/TextMeshScroller.h"
#include "Constants/AssetPaths.h"
#include "Scenes/MainMenuScene.h"
#include <Constants/ResourcePaths.h>
#include <Core/CoreEvents/EventManager.h>
#include <Core/SubSystems/Systems/Renderer.h>
#include <Engine/Blueprints/UI/ButtonBlueprint.h>
#include <Engine/Components/Audio/AudioListener.h>
#include <Engine/Components/Rendering/Camera.h>
#include <Engine/Components/Transform.h>
#include <Engine/Components/UI/Button.h>
#include <Engine/Components/UI/Canvas.h>
#include <Engine/Components/UI/Layout/VerticalLayoutGroup.h>
#include <Engine/Components/UI/TextMesh.h>
#include <Engine/Entity/GameObject.h>
#include <Engine/SceneSystem/SceneManager.h>
#include <functional>
#include <Scenes/MainGameScene.h>
#include <Utilities/IO/FileSystemUtils.h>


void MainMenuScene::Enter()
{
	auto renderTargetSize = Renderer::GetResolutionTarget();


	// Camera
	auto cameraObject = GameObject::Instantiate<GameObject>();
	cameraObject.lock()->AddComponent<Camera>();


	// UI
	auto canvasObject = GameObject::Instantiate<GameObject>();
	canvasObject.lock()->AddComponent<Canvas>();

	auto layoutPosition = Vector2F(renderTargetSize.x * 0.5f, renderTargetSize.y * 0.65f);

	// Create MenuManager and push the initial menu onto the stack
	auto menuManagerObject = GameObject::Instantiate<GameObject>();
	auto menuManagerComponent = menuManagerObject.lock()->AddComponent<MenuManager>();

	// Main Menu
	auto mainMenuObject = GameObject::Instantiate<GameObject>();
	auto mainMenuBase = mainMenuObject.lock()->AddComponent<MenuBase>();


	auto title = CreateText("Retro Platformer", AssetPaths::Files::GAMEPLAY_FONT);
	title.lock()->GetTransform()->SetWorldPosition(Vector2F(renderTargetSize.x * 0.5f, renderTargetSize.y * 0.2f));

	auto selectCallback = MakeAudioPlayAndDestroyCallback(AssetPaths::Files::CONFIRM_UI, Vector2F::Zero, 0.5f, false, false, 1.0f);
	auto enterCallback = MakeAudioPlayAndDestroyCallback(AssetPaths::Files::SELECT_UI, Vector2F::Zero, 0.5f, false, false, 1.0f);

	auto spButton = CreateButton("Play Game", AssetPaths::Files::GAMEPLAY_FONT, [selectCallback]() { selectCallback(); SceneManager::LoadScene<MainGameScene>(); }, enterCallback);
	auto creditsButton = CreateButton("Credits", AssetPaths::Files::GAMEPLAY_FONT, [selectCallback, menuManagerComponent]() {
		selectCallback(); 
		menuManagerComponent->HideAll(); 
		menuManagerComponent->ShowMenu(MenuID::CREDITS_MENU); 
		}, enterCallback);
	auto exitButton = CreateButton("Exit", AssetPaths::Files::GAMEPLAY_FONT, [selectCallback]() { selectCallback(); EventManager::SendSystemEvent(SDL_EventType::SDL_QUIT); }, enterCallback);

	spButton.lock()->GetComponent<Button>()->SetNavigableUpElement(exitButton.lock()->GetComponent<Button>());
	spButton.lock()->GetComponent<Button>()->SetNavigableDownElement(creditsButton.lock()->GetComponent<Button>());
	creditsButton.lock()->GetComponent<Button>()->SetNavigableUpElement(spButton.lock()->GetComponent<Button>());
	creditsButton.lock()->GetComponent<Button>()->SetNavigableDownElement(exitButton.lock()->GetComponent<Button>());
	exitButton.lock()->GetComponent<Button>()->SetNavigableUpElement(creditsButton.lock()->GetComponent<Button>());
	exitButton.lock()->GetComponent<Button>()->SetNavigableDownElement(spButton.lock()->GetComponent<Button>());

	auto mainMenuLayout = GameObject::Instantiate<GameObject>();

	mainMenuLayout.lock()->AddComponent<VerticalLayoutGroup>(20.0f, LayoutPadding());
	mainMenuLayout.lock()->GetComponent<Transform>()->SetWorldPosition(layoutPosition);
	mainMenuLayout.lock()->AddChildGameObject(spButton);
	mainMenuLayout.lock()->AddChildGameObject(creditsButton);
	mainMenuLayout.lock()->AddChildGameObject(exitButton);
	mainMenuObject.lock()->AddChildGameObject(title);
	mainMenuObject.lock()->AddChildGameObject(mainMenuLayout);

	// Credits Menu
	auto creditsText = Tools::IO::FileSystemUtils::LoadTextFile(AssetPaths::Files::CREDITS);
	
	auto creditsMenuObject = GameObject::Instantiate<GameObject>();
	creditsMenuObject.lock()->GetComponent<Transform>()->SetWorldScale(Vector2F(0.75f, 0.75f));
	auto creditsMenuBase = creditsMenuObject.lock()->AddComponent<MenuBase>();
	
	auto creditTextMeshObj = CreateText(creditsText, Constants::ResourcePaths::Files::CONSOLAS_FONT);
	auto creditTextMeshComponent = creditTextMeshObj.lock()->GetComponent<TextMesh>();
	creditsMenuObject.lock()->AddComponent<TextMeshScroller>(creditTextMeshComponent);

	creditTextMeshObj.lock()->GetComponent<Transform>()->SetWorldPosition(Vector2F(renderTargetSize.x * 0.5f, renderTargetSize.y * 0.5f));

	creditsMenuObject.lock()->AddChildGameObject(creditTextMeshObj);
	
	canvasObject.lock()->AddChildGameObject(mainMenuObject);
	canvasObject.lock()->AddChildGameObject(creditsMenuObject);

	creditsMenuBase->SetPreviousMenu(mainMenuBase);

	// Register menus
	menuManagerComponent->RegisterMenu(MenuID::MAIN_MENU, mainMenuBase);
	menuManagerComponent->RegisterMenu(MenuID::CREDITS_MENU, creditsMenuBase);
	menuManagerComponent->HideAll();
	menuManagerComponent->ShowMenu(MenuID::MAIN_MENU);

	auto soundListenerObj = GameObject::Instantiate<GameObject>();
	soundListenerObj.lock()->AddComponent<AudioListener>();
}