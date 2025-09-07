#pragma once
#include "Engine/EngineEvents/DispatchableEvent.h"


class GameEndedEvent : public DispatchableEvent
{
public:
	bool isGameLost;


	GameEndedEvent(bool isGameLost);
};