#pragma once
#include <Core/DeadFrameRuntime.h>


class Application : public DeadFrame2D::Core::DeadFrameRuntime
{
public:
	Application();

	virtual ~Application() = default;
};