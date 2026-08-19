#include "Components/Controllers/StatsController.h"
#include "Components/UI/EndGameController.h"
#include "Components/UI/MenuManager.h"
#include "Constants/AssetPaths.h"
#include <Core/Context/Systems/Coroutines/CoroutineScheduler.h>
#include <Core/Services/Time/Abstractions/ITimeProvider.h>
#include <CustomEvents/GameEndedEvent.h>
#include <Engine/Blueprints/Audio/AudioClipBlueprint.h>
#include <Engine/ECS/Component/UI/TextMesh.h>
#include <Engine/ECS/Entity/Object/Core/GameObject.h>
#include <Engine/ECS/System/Events/EventDispatcher.h>
#include <Engine/ECS/System/Scene/SceneManager.h>
#include <Utilities/Debugging/Guards.h>
#include <Utilities/Helpers/Events/EventHelpers.h>


using namespace DF2D::Core;
using namespace DF2D::Engine;
using namespace DF2D::Utilities;


EndGameController::EndGameController()
{
}

EndGameController::~EndGameController()
{
}

void EndGameController::OnGameEndedHandler(std::shared_ptr<DispatchableEvent> dispatchableEvent)
{
	auto gameEndedEvent = DispatchableEvent::SafeCast<GameEndedEvent>(dispatchableEvent);

	if (gameEndedEvent == nullptr)
		return;

	GetGameObject()->ServiceContext().frameTimer->SetTimeScale(0.0f);

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

	GetGameObject()->CoreContext().coroutineScheduler->StartCoroutine(endGameSoundObj->Destroy(10.0f));
}

void EndGameController::Init()
{
	menuManager = Guard::AgainstNullAssignment(SceneManager::FindObjectOfType<MenuManager>(), NAME_OF(menuManager));
	statsController = Guard::AgainstNullAssignment(SceneManager::FindObjectOfType<StatsController>(), NAME_OF(statsController));

	Guard::AgainstNull(endGameTextMesh, NAME_OF(endGameTextMesh));

	auto* eventDispatcher = Guard::AgainstNullAssignment(GetGameObject()->ServiceContext().eventDispatcher, NAME_OF(eventDispatcher));

	eventDispatcher->RegisterEventHandler<GameEndedEvent>(GetHandle(), EventHelpers::BindFunction(this, &EndGameController::OnGameEndedHandler));
}

void EndGameController::SetEndGameTextMesh(ComponentHandle<TextMesh> endGameTextMesh)
{
	this->endGameTextMesh = endGameTextMesh;
}