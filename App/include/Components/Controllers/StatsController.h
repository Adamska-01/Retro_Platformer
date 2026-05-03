#pragma once
#include <Engine/ECS/Entity/Component/Core/GameComponent.h>
#include <Engine/ECS/Entity/Component/Handle/ComponentHandle.h>
#include <Engine/ECS/System/Events/DispatchableEvent.h>
#include <memory>


namespace DF2D::Engine
{
	class TextMesh;
}


class StatsController : public DF2D::Engine::GameComponent
{
	TYPE_INFO(StatsController, DF2D::Engine::GameComponent);


private:
	int score;

	int lifes;

	DF2D::Engine::ComponentHandle<DF2D::Engine::TextMesh> scoreTextMesh;

	DF2D::Engine::ComponentHandle<DF2D::Engine::TextMesh> lifesTextMesh;


	void PointsScoredEventHandler(std::shared_ptr<DF2D::Engine::DispatchableEvent> dispatchableEvent);

	void LifeLostEventHandler(std::shared_ptr<DF2D::Engine::DispatchableEvent> dispatchableEvent);


public:
	StatsController();

	virtual ~StatsController() override;


	virtual void Init() override;

	virtual void Start() override;


	void SetScoreTextMesh(DF2D::Engine::ComponentHandle<DF2D::Engine::TextMesh> scoreTextMesh);

	void SetLifesTextMesh(DF2D::Engine::ComponentHandle<DF2D::Engine::TextMesh> lifesTextMesh);

	int GetScore();

	int GetLifes();
};