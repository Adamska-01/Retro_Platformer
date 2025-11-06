#include "Components/Controllers/StatsController.h"
#include "CustomEvents/GameEndedEvent.h"
#include "CustomEvents/LifeLostEvent.h"
#include "CustomEvents/PointsScoredEvent.h"
#include <Engine/Components/UI/TextMesh.h>
#include <Engine/EngineEvents/EventDispatcher.h>
#include <Utilities/Debugging/Guards.h>
#include <Utilities/Helpers/Events/EventHelpers.h>


using namespace DeadFrame2D::Engine;
using namespace DeadFrame2D::Utilities;


StatsController::StatsController()
	: score(0),
	lifes(3)
{
	auto identifier = reinterpret_cast<std::uintptr_t>(this);
	
	EventDispatcher::RegisterEventHandler(std::type_index(typeid(PointsScoredEvent)), EventHelpers::BindFunction(this, &StatsController::PointsScoredEventHandler), identifier);
	EventDispatcher::RegisterEventHandler(std::type_index(typeid(LifeLostEvent)), EventHelpers::BindFunction(this, &StatsController::LifeLostEventHandler), identifier);
}

StatsController::~StatsController()
{
	auto identifier = reinterpret_cast<std::uintptr_t>(this);

	EventDispatcher::DeregisterEventHandler(std::type_index(typeid(PointsScoredEvent)), identifier);
	EventDispatcher::DeregisterEventHandler(std::type_index(typeid(LifeLostEvent)), identifier);
}

void StatsController::PointsScoredEventHandler(std::shared_ptr<DispatchableEvent> dispatchableEvent)
{
	auto pointsScoredEvent = DispatchableEvent::SafeCast<PointsScoredEvent>(dispatchableEvent);

	if (pointsScoredEvent == nullptr)
		return;

	score += pointsScoredEvent->pointsScored;

	scoreTextMesh->SetText("Score: " + std::to_string(score));
}

void StatsController::LifeLostEventHandler(std::shared_ptr<DispatchableEvent> dispatchableEvent)
{
	--lifes;

	lifesTextMesh->SetText("Lifes: " + std::to_string(lifes));

	if (lifes <= 0)
	{
		EventDispatcher::SendEvent(std::make_shared<GameEndedEvent>(true));
	}
}

void StatsController::Init()
{
	Guard::AgainstNull(scoreTextMesh, NAME_OF(scoreTextMesh));
	Guard::AgainstNull(lifesTextMesh, NAME_OF(lifesTextMesh));
}

void StatsController::Start()
{
	scoreTextMesh->SetText("Score: " + std::to_string(score));
	lifesTextMesh->SetText("Lifes: " + std::to_string(lifes));
}

void StatsController::SetScoreTextMesh(ComponentHandle<TextMesh> scoreTextMesh)
{
	this->scoreTextMesh = scoreTextMesh;
}

void StatsController::SetLifesTextMesh(ComponentHandle<TextMesh> lifesTextMesh)
{
	this->lifesTextMesh = lifesTextMesh;
}

int StatsController::GetScore()
{
	return score;
}

int StatsController::GetLifes()
{
	return lifes;
}