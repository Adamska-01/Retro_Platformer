#pragma once
#include <Engine/EngineEvents/DispatchableEvent.h>


class LifeLostEvent : public DeadFrame2D::Engine::DispatchableEvent
{
public:
	LifeLostEvent() = default;
};