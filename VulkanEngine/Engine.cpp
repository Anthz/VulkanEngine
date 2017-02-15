#include "Engine.h"
#include <iostream>

Engine::Engine()
{
}


Engine::~Engine()
{
}

void Engine::Run()
{
	InitWindow();
	InitVulkan();
	MainLoop();
}

void Engine::MainLoop()
{
	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
}

void Engine::InitVulkan()
{
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	std::cout << extensionCount << " extensions supported" << std::endl;

}

void Engine::InitWindow()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Vulkan window", nullptr, nullptr);
}
