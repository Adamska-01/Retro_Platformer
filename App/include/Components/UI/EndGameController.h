#pragma once
#include <Engine/Components/GameComponent.h>
#include <Engine/Entity/ComponentHandle.h>
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
	TYPE_INFO(EndGameController, DeadFrame2D::Engine::GameComponent);


private:
	DeadFrame2D::Engine::ComponentHandle<MenuManager> menuManager;

	DeadFrame2D::Engine::ComponentHandle<DeadFrame2D::Engine::TextMesh> endGameTextMesh;

	DeadFrame2D::Engine::ComponentHandle<StatsController> statsController;


	void OnGameEndedHandler(std::shared_ptr<DeadFrame2D::Engine::DispatchableEvent> dispatchableEvent);


public:
	EndGameController();

	virtual ~EndGameController() override;


	virtual void Init() override;


	void SetEndGameTextMesh(DeadFrame2D::Engine::ComponentHandle<DeadFrame2D::Engine::TextMesh> endGameTextMesh);
};