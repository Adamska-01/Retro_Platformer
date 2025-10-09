#pragma once
#include <Engine/Components/GameComponent.h>
#include <memory>


class MenuManager;
class StatsController;

namespace DeadFrame2D::Engine
{
	class TextMesh;
	class DispatchableEvent;
}



class EndGameController : public DeadFrame2D::Engine::GameComponent
{
private:
	MenuManager* menuManager;

	DeadFrame2D::Engine::TextMesh* endGameTextMesh;

	StatsController* statsController;


	void OnGameEndedHandler(std::shared_ptr<DeadFrame2D::Engine::DispatchableEvent> dispatchableEvent);


public:
	EndGameController();

	virtual ~EndGameController() override;


	virtual void Init() override;

	virtual void Start() override;

	virtual void Update(float deltaTime) override;

	virtual void Draw() override;


	void SetEndGameTextMesh(DeadFrame2D::Engine::TextMesh* endGameTextMesh);
};