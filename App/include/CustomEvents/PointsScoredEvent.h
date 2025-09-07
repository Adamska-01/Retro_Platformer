#pragma once
#include "Engine/EngineEvents/DispatchableEvent.h"


class PointsScoredEvent : public DispatchableEvent
{
public:
	unsigned int pointsScored;


	PointsScoredEvent(unsigned int pointsScored);
};