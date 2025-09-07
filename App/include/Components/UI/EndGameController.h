#pragma once
#include <Engine/Components/GameComponent.h>
#include <memory>


class MenuManager;
class DispatchableEvent;
class TextMesh;
class StatsController;


class EndGameController : public GameComponent
{
private:
	MenuManager* menuManager;

	TextMesh* endGameTextMesh;

	StatsController* statsController;


	void OnGameEndedHandler(std::shared_ptr<DispatchableEvent> dispatchableEvent);


public:
	EndGameController();

	virtual ~EndGameController() override;


	virtual void Init() override;

	virtual void Start() override;

	virtual void Update(float deltaTime) override;

	virtual void Draw() override;


	void SetEndGameTextMesh(TextMesh* endGameTextMesh);
};