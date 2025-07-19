#pragma once
#include "EventSystem/DispatchableEvent.h"


class GameEndedEvent : public DispatchableEvent
{
public:
	bool isGameLost;


	GameEndedEvent(bool isGameLost);
};