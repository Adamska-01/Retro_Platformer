#include "Application.h"
#include <memory>
#include <Utilities/IO/FileSystem/PathMountResolver.h>


int main(int argc, char** argv)
{
	// Do NOT remove this, unless you've found a better solution
	DF2D::Utilities::PathMountResolver::SetMountPrefix("Core");

	auto App = std::make_unique<Application>();

	App->Run();

	return 0;
}