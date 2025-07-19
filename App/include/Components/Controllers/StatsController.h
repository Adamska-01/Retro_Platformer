#pragma once
#include <Components/GameComponent.h>
#include <EventSystem/DispatchableEvent.h>
#include <memory>


class TextMesh;


class StatsController : public GameComponent
{
private:
	int score;

	int lifes;

	TextMesh* scoreTextMesh;

	TextMesh* lifesTextMesh;


	void PointsScoredEventHandler(std::shared_ptr<DispatchableEvent> dispatchableEvent);

	void LifeLostEventHandler(std::shared_ptr<DispatchableEvent> dispatchableEvent);


public:
	StatsController();

	virtual ~StatsController() override;


	virtual void Init() override;

	virtual void Start() override;

	virtual void Update(float deltaTime) override;

	virtual void Draw() override;


	void SetScoreTextMesh(TextMesh* scoreTextMesh);

	void SetLifesTextMesh(TextMesh* lifesTextMesh);

	int GetScore();

	int GetLifes();
};