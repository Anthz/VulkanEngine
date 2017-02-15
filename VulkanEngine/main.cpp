#define GLFW_INCLUDE_VULKAN
#include <iostream>
#include "Engine.h"

int main()
{
	Engine engine;
	
	try
	{
		engine.Run();
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;	//1
	}

	return EXIT_SUCCESS;	//0
}