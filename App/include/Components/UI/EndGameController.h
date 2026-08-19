#pragma once
#include <Engine/ECS/Entity/Component/Core/GameComponent.h>
#include <Engine/ECS/Entity/Component/Handle/ComponentHandle.h>
#include <memory>


class MenuManager;
class StatsController;

namespace DF2D::Engine
{
	class TextMesh;
	class DispatchableEvent;
}



class EndGameController : public DF2D::Engine::GameComponent
{
	TYPE_INFO(EndGameController, DF2D::Engine::GameComponent);


private:
	DF2D::Engine::ComponentHandle<MenuManager> menuManager;

	DF2D::Engine::ComponentHandle<DF2D::Engine::TextMesh> endGameTextMesh;

	DF2D::Engine::ComponentHandle<StatsController> statsController;


	void OnGameEndedHandler(std::shared_ptr<DF2D::Engine::DispatchableEvent> dispatchableEvent);


public:
	EndGameController();

	virtual ~EndGameController() override;


	virtual void Init() override;


	void SetEndGameTextMesh(DF2D::Engine::ComponentHandle<DF2D::Engine::TextMesh> endGameTextMesh);
};