#include "Components/Controllers/StatsController.h"
#include "CustomEvents/GameEndedEvent.h"
#include "CustomEvents/LifeLostEvent.h"
#include "CustomEvents/PointsScoredEvent.h"
#include <Engine/ECS/Component/UI/TextMesh.h>
#include <Engine/ECS/System/Events/EventDispatcher.h>
#include <Utilities/Debugging/Guards.h>
#include <Utilities/Helpers/Events/EventHelpers.h>


using namespace DF2D::Engine;
using namespace DF2D::Utilities;


StatsController::StatsController()
	: score(0),
	lifes(3)
{
	EventDispatcher::RegisterEventHandler(std::type_index(typeid(PointsScoredEvent)), this, &StatsController::PointsScoredEventHandler);
	EventDispatcher::RegisterEventHandler(std::type_index(typeid(LifeLostEvent)), this, &StatsController::LifeLostEventHandler);
}

StatsController::~StatsController()
{
	EventDispatcher::DeregisterEventHandler(std::type_index(typeid(PointsScoredEvent)), this);
	EventDispatcher::DeregisterEventHandler(std::type_index(typeid(LifeLostEvent)), this);
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