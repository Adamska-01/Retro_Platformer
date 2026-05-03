#pragma once
#include <Engine/ECS/System/Events/DispatchableEvent.h>


class PointsScoredEvent : public DF2D::Engine::DispatchableEvent
{
public:
	unsigned int pointsScored;


	PointsScoredEvent(unsigned int pointsScored);
};