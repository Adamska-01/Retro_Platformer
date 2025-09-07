#include "Components/Controllers/StatsController.h"
#include "Components/UI/EndGameController.h"
#include "Components/UI/MenuManager.h"
#include "Constants/AssetPaths.h"
#include <Core/Framerate/FrameTimer.h>
#include <Core/SubSystems/Systems/CoroutineScheduler.h>
#include <CustomEvents/GameEndedEvent.h>
#include <Engine/Blueprints/Audio/AudioClipBlueprint.h>
#include <Engine/Components/UI/TextMesh.h>
#include <Engine/EngineEvents/EventDispatcher.h>
#include <Engine/Entity/GameObject.h>
#include <Engine/SceneSystem/SceneManager.h>
#include <Utilities/Debugging/Guards.h>
#include <Utilities/Helpers/Events/EventHelpers.h>


EndGameController::EndGameController()
	: menuManager(nullptr)
{
	EventDispatcher::RegisterEventHandler(std::type_index(typeid(GameEndedEvent)), EventHelpers::BindFunction(this, &EndGameController::OnGameEndedHandler), reinterpret_cast<std::uintptr_t>(this));
}

EndGameController::~EndGameController()
{
	EventDispatcher::DeregisterEventHandler(std::type_index(typeid(GameEndedEvent)), reinterpret_cast<std::uintptr_t>(this));
}

void EndGameController::OnGameEndedHandler(std::shared_ptr<DispatchableEvent> dispatchableEvent)
{
	auto gameEndedEvent = DispatchableEvent::SafeCast<GameEndedEvent>(dispatchableEvent);

	if (gameEndedEvent == nullptr)
		return;

	FrameTimer::SetTimeScale(0.0f);

	auto endGameSound = gameEndedEvent->isGameLost ? AssetPaths::Files::GAME_OVER : AssetPaths::Files::VICTORY;
	auto title = gameEndedEvent->isGameLost
		? "GameOver\n\nScore: " + std::to_string(statsController->GetScore()) + "\n\n"
		: "Congratulations\n\nScore: " + std::to_string(statsController->GetScore()) + "\n\n";

	endGameTextMesh->SetText(title);

	menuManager->HideAll();
	menuManager->ShowMenu(MenuID::END_GAME_MENU);

	auto endGameSoundObj = GameObject::Instantiate<AudioClipBlueprint>(
		endGameSound,
		Vector2F::Zero,
		0.7f,
		true);

	CoroutineScheduler::StartCoroutine(endGameSoundObj.lock()->Destroy(10.0f));
}

void EndGameController::Init()
{
	menuManager = SceneManager::FindObjectOfType<MenuManager>();
	statsController = SceneManager::FindObjectOfType<StatsController>();

	Tools::Helpers::GuardAgainstNull(menuManager, "Failed to get MenuManager from the scene");
	Tools::Helpers::GuardAgainstNull(menuManager, "Failed to get StatsManager from the scene");
	Tools::Helpers::GuardAgainstNull(endGameTextMesh, "EndGameController::Init: The endGame TextMesh is required!");
}

void EndGameController::Start()
{

}

void EndGameController::Update(float deltaTime)
{

}

void EndGameController::Draw()
{

}

void EndGameController::SetEndGameTextMesh(TextMesh* endGameTextMesh)
{
	this->endGameTextMesh = endGameTextMesh;
}