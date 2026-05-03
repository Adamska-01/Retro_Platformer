#pragma once
#include <Engine/ECS/System/Events/DispatchableEvent.h>


class GameEndedEvent : public DF2D::Engine::DispatchableEvent
{
public:
	bool isGameLost;


	GameEndedEvent(bool isGameLost);
};