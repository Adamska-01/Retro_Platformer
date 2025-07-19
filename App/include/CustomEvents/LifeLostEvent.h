#pragma once
#include "EventSystem/DispatchableEvent.h"


class LifeLostEvent : public DispatchableEvent
{
public:
	LifeLostEvent() = default;
};