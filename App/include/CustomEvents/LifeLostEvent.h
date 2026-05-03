#pragma once
#include <Engine/ECS/System/Events/DispatchableEvent.h>


class LifeLostEvent : public DF2D::Engine::DispatchableEvent
{
public:
	LifeLostEvent() = default;
};