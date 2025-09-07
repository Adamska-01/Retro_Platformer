#pragma once
#include <Engine/EngineEvents/DispatchableEvent.h>


class LifeLostEvent : public DispatchableEvent
{
public:
	LifeLostEvent() = default;
};