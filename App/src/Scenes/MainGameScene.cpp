#include "Blueprints/Coin.h"
#include "Blueprints/Enemy.h"
#include "Blueprints/GameMap.h"
#include "Blueprints/Key.h"
#include "Components/Controllers/StatsController.h"
#include "Components/Map/CustomTileMapRenderer2D.h"
#include "Components/UI/Abstractions/MenuBase.h"
#include "Components/UI/EndGameController.h"
#include "Components/UI/MenuManager.h"
#include "Constants/AssetPaths.h"
#include "Data/Entities/EnemyConfig.h"
#include "Models/Map/TileMapModel.h"
#include "Scenes/MainGameScene.h"
#include <Blueprints/FollowCameraObject.h>
#include <Blueprints/Player.h>
#include <Core/CoreEvents/EventManager.h>
#include <Core/SubSystems/Systems/Renderer.h>
#include <Data/Components/UI/TextMeshComponentModel.h>
#include <Data/UI/MenuID.h>
#include <Engine/Blueprints/UI/ButtonBlueprint.h>
#include <Engine/Components/Transform.h>
#include <Engine/Components/UI/Button.h>
#include <Engine/Components/UI/Canvas.h>
#include <Engine/Components/UI/Image.h>
#include <Engine/Components/UI/Layout/VerticalLayoutGroup.h>
#include <Engine/Components/UI/TextMesh.h>
#include <Engine/Entity/GameObject.h>
#include <Engine/SceneSystem/SceneManager.h>
#include <Scenes/MainMenuScene.h>
#include <Tools/Serialization/JsonSerializer.h>


using namespace DeadFrame2D::Core;
using namespace DeadFrame2D::Data;
using namespace DeadFrame2D::Engine;
using namespace Shared::Tools;


ObjectHandle<GameObject> MainGameScene::CreateText(const std::string& text)
{
	auto textMeshObject = GameObject::Instantiate<GameObject>();

	textMeshObject->AddComponent<TextMesh>(TextMeshComponentModel
		{
			.fontSource = AssetPaths::Files::GAMEPLAY_FONT,
			.text = text,
			.textColor = SDL_Color(255, 132, 31),
			.fontSize = 100,
			.textObjectInitialScale = Vector2F(0.25f, 0.25f),
			.isCentered = true
		});

	return textMeshObject;
}

ComponentHandle<MenuBase> MainGameScene::CreateEndScreen(std::string menuTitle, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	auto renderTargetSize = Renderer::GetResolutionTarget();

	auto endScreenMenuObject = GameObject::Instantiate<GameObject>();
	auto endScreenMenuBase = endScreenMenuObject->AddComponent<MenuBase>();
	auto endGameController = endScreenMenuObject->AddComponent<EndGameController>();

	auto background = GameObject::Instantiate<GameObject>();
	auto imageBackground = background->AddComponent<Image>();
	imageBackground->SetWidgetSize(Vector2F(renderTargetSize.x, renderTargetSize.y));
	imageBackground->SetAnchor(UIAnchor::TOP_LEFT);
	imageBackground->SetColor(r, g, b, a);

	auto enterCallback = MakeAudioPlayAndDestroyCallback(AssetPaths::Files::CONFIRM_UI, Vector2F::Zero, 0.5f, false, false, 1.0f);
	auto title = CreateText(menuTitle);
	auto spButton = CreateButton("Back To Menu", AssetPaths::Files::GAMEPLAY_FONT, []() { SceneManager::LoadScene<MainMenuScene>(); }, enterCallback);
	auto exitButton = CreateButton("Exit", AssetPaths::Files::GAMEPLAY_FONT, []() { EventManager::SendSystemEvent(SDL_EventType::SDL_QUIT); }, enterCallback);

	spButton->GetComponent<Button>()->SetNavigableUpElement(exitButton->GetComponent<Button>());
	spButton->GetComponent<Button>()->SetNavigableDownElement(exitButton->GetComponent<Button>());
	exitButton->GetComponent<Button>()->SetNavigableUpElement(spButton->GetComponent<Button>());
	exitButton->GetComponent<Button>()->SetNavigableDownElement(spButton->GetComponent<Button>());

	auto menuLayout = GameObject::Instantiate<GameObject>();
	menuLayout->AddComponent<VerticalLayoutGroup>(20.0f, LayoutPadding());
	menuLayout->GetComponent<Transform>()->SetWorldPosition(Vector2F(renderTargetSize.x * 0.5f, renderTargetSize.y * 0.5f));
	menuLayout->AddChildGameObject(title);
	menuLayout->AddChildGameObject(spButton);
	menuLayout->AddChildGameObject(exitButton);

	endScreenMenuObject->AddChildGameObject(background);
	endScreenMenuObject->AddChildGameObject(menuLayout);

	endGameController->SetEndGameTextMesh(title->GetComponent<TextMesh>());

	endScreenMenuBase->Hide();

	return endScreenMenuBase;
}

ComponentHandle<MenuBase> MainGameScene::CreateHUD()
{
	auto renderTargetSize = Renderer::GetResolutionTarget();

	auto hudMenuObject = GameObject::Instantiate<GameObject>();
	auto hudMenuBase = hudMenuObject->AddComponent<MenuBase>();

	auto scoreLayout = GameObject::Instantiate<GameObject>();
	scoreLayout->GetTransform()->SetWorldPosition(Vector2F(20, 40));
	auto statsComponent = scoreLayout->AddComponent<StatsController>();
	scoreLayout->AddComponent<VerticalLayoutGroup>(20.0f, LayoutPadding());

	auto scoreTextObj = CreateText("Score: xx");
	scoreTextObj->GetComponent<TextMesh>()->SetAnchor(UIAnchor::TOP_LEFT);

	auto lifesTextObj = CreateText("Lifes: xx");
	lifesTextObj->GetComponent<TextMesh>()->SetAnchor(UIAnchor::TOP_LEFT);

	scoreLayout->AddChildGameObject(scoreTextObj);
	scoreLayout->AddChildGameObject(lifesTextObj);

	statsComponent->SetScoreTextMesh(scoreTextObj->GetComponent<TextMesh>());
	statsComponent->SetLifesTextMesh(lifesTextObj->GetComponent<TextMesh>());

	hudMenuObject->AddChildGameObject(scoreLayout);

	return hudMenuBase;
}

void MainGameScene::Enter()
{
	auto resolutionTarget = Renderer::GetResolutionTarget();

	// UI
	auto canvasObject = GameObject::Instantiate<GameObject>();
	canvasObject->AddComponent<Canvas>();


	auto hud = CreateHUD();
	auto endGameMenuBase = CreateEndScreen("GameOver!", 0, 0, 0, 120);

	canvasObject->AddChildGameObject(hud->GetGameObject());
	canvasObject->AddChildGameObject(endGameMenuBase->GetGameObject());

	auto menuManagerObject = GameObject::Instantiate<GameObject>();
	auto menuManagerComponent = menuManagerObject->AddComponent<MenuManager>();
	menuManagerComponent->RegisterMenu(MenuID::HUD, hud->GetHandleAs<MenuBase>());
	menuManagerComponent->RegisterMenu(MenuID::END_GAME_MENU, endGameMenuBase->GetHandleAs<MenuBase>());
	menuManagerComponent->HideAll();
	menuManagerComponent->ShowMenu(MenuID::HUD);


	// GameObjects
	auto tileMapModel = std::make_shared<TileMapModel>(DeserializeFromFile<TileMapModel>(AssetPaths::Files::MAP_LV_1));
	auto tileRenderSize = tileMapModel->tileRenderSize;

	auto gameMap = GameObject::Instantiate<GameMap>(tileMapModel);

	// Enemies
	auto enemyConfig = EnemyConfig
	{
		.characterSize = static_cast<float>(tileMapModel->tileRenderSize),
		.idleAnimProperty = SpriteAnimationProperties
		{
			.name = "Idle",
			.columnCount = 2,
			.animSpeed = 5.0f,
			.loop = true
		},
		.bodyDefinition = BodyDefinition2D
		{
			.type = BodyType2D::Dynamic,
			.fixedRotation = true
		}
	};

	enemyConfig.spriteSource = AssetPaths::Files::GROUND_ENEMY_SPRITE;
	enemyConfig.canFly = false;
	enemyConfig.idleAnimProperty.spriteSource = AssetPaths::Files::GROUND_ENEMY_SPRITE;
	enemyConfig.bodyDefinition.gravityScale = 1.0f;

	for (const auto& enemyPos : tileMapModel->entityPositions.groundEnemies)
	{
		GameObject::Instantiate<Enemy>(enemyPos.ToVector2F(tileRenderSize), enemyConfig);
	}

	enemyConfig.spriteSource = AssetPaths::Files::FLY_ENEMY_SPRITE;
	enemyConfig.canFly = true;
	enemyConfig.idleAnimProperty.spriteSource = AssetPaths::Files::FLY_ENEMY_SPRITE;
	enemyConfig.bodyDefinition.gravityScale = 0.0f;

	for (const auto& enemyPos : tileMapModel->entityPositions.flyEnemies)
	{
		GameObject::Instantiate<Enemy>(enemyPos.ToVector2F(tileRenderSize), enemyConfig);
	}

	// Coins
	for (const auto& coinPos : tileMapModel->entityPositions.coins)
	{
		GameObject::Instantiate<Coin>(coinPos.ToVector2F(tileRenderSize), AssetPaths::Files::COIN_SPRITE);
	}

	// Keys
	GameObject::Instantiate<Key>(tileMapModel->entityPositions.key.ToVector2F(tileRenderSize), AssetPaths::Files::KEY_SPRITE);

	// Player
	auto playerObj = GameObject::Instantiate<Player>(
		tileMapModel->entityPositions.player.ToVector2F(tileRenderSize),
		AssetPaths::Files::PLAYER_IDLE_SPRITE, 
		AssetPaths::Files::PLAYER_RUN_SPRITE);

	auto mapFullSize = gameMap->GetComponentInChildren<CustomTileMapRenderer2D>()->GetMapFullSize();
	auto gameMapPosition = gameMap->GetTransform()->GetWorldPosition();
	auto mapBounds = SDL_FRect
	{
		gameMapPosition.x,
		gameMapPosition.y,
		static_cast<float>(mapFullSize.x),
		static_cast<float>(mapFullSize.y)
	};

	GameObject::Instantiate<FollowCameraObject>(playerObj, mapBounds);
}