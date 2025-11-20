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


using namespace DeadFrame2D::Core;
using namespace DeadFrame2D::Engine;
using namespace DeadFrame2D::Utilities;


EndGameController::EndGameController()
{
	EventDispatcher::RegisterEventHandler(std::type_index(typeid(GameEndedEvent)), this, &EndGameController::OnGameEndedHandler);
}

EndGameController::~EndGameController()
{
	EventDispatcher::DeregisterEventHandler(std::type_index(typeid(GameEndedEvent)), this);
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

	CoroutineScheduler::StartCoroutine(endGameSoundObj->Destroy(10.0f));
}

void EndGameController::Init()
{
	menuManager = Guard::AgainstNullAssignment(SceneManager::FindObjectOfType<MenuManager>(), NAME_OF(menuManager));
	statsController = Guard::AgainstNullAssignment(SceneManager::FindObjectOfType<StatsController>(), NAME_OF(statsController));

	Guard::AgainstNull(endGameTextMesh, NAME_OF(endGameTextMesh));
}

void EndGameController::SetEndGameTextMesh(ComponentHandle<TextMesh> endGameTextMesh)
{
	this->endGameTextMesh = endGameTextMesh;
}