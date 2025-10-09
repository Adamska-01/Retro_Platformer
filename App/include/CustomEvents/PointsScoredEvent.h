#pragma once
#include "Engine/EngineEvents/DispatchableEvent.h"


class PointsScoredEvent : public DeadFrame2D::Engine::DispatchableEvent
{
public:
	unsigned int pointsScored;


	PointsScoredEvent(unsigned int pointsScored);
};