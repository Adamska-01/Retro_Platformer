#pragma once
#include <Core/DeadFrameRuntime.h>


class Application : public DF2D::Core::DeadFrameRuntime
{
public:
	Application();

	virtual ~Application() = default;
};