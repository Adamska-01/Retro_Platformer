#include "Application.h"
#include <memory>
#include <Tools/FileSystem/PathMountResolver.h>


int main(int argc, char** argv)
{
	// Do NOT remove this, unless you found a better solution
	PathMountResolver::SetMountPrefix("Core");

	auto App = std::make_unique<Application>();

	App->Run();
	
	return 0;
}