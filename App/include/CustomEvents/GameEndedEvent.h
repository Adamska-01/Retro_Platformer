#pragma once
#include "Engine/EngineEvents/DispatchableEvent.h"


class GameEndedEvent : public DeadFrame2D::Engine::DispatchableEvent
{
public:
	bool isGameLost;


	GameEndedEvent(bool isGameLost);
};