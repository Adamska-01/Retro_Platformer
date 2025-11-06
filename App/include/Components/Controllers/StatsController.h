#pragma once
#include <Engine/Components/GameComponent.h>
#include <Engine/EngineEvents/DispatchableEvent.h>
#include <Engine/Entity/ComponentHandle.h>
#include <memory>


namespace DeadFrame2D::Engine
{
	class TextMesh;
}


class StatsController : public DeadFrame2D::Engine::GameComponent
{
	TYPE_INFO(StatsController, DeadFrame2D::Engine::GameComponent);


private:
	int score;

	int lifes;

	DeadFrame2D::Engine::ComponentHandle<DeadFrame2D::Engine::TextMesh> scoreTextMesh;

	DeadFrame2D::Engine::ComponentHandle<DeadFrame2D::Engine::TextMesh> lifesTextMesh;


	void PointsScoredEventHandler(std::shared_ptr<DeadFrame2D::Engine::DispatchableEvent> dispatchableEvent);

	void LifeLostEventHandler(std::shared_ptr<DeadFrame2D::Engine::DispatchableEvent> dispatchableEvent);


public:
	StatsController();

	virtual ~StatsController() override;


	virtual void Init() override;

	virtual void Start() override;


	void SetScoreTextMesh(DeadFrame2D::Engine::ComponentHandle<DeadFrame2D::Engine::TextMesh> scoreTextMesh);

	void SetLifesTextMesh(DeadFrame2D::Engine::ComponentHandle<DeadFrame2D::Engine::TextMesh> lifesTextMesh);

	int GetScore();

	int GetLifes();
};