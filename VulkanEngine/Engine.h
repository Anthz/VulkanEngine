#pragma once

#define GLFW_INCLUDE_VULKAN	//replace vulkan.h and allow glfw to include it
#include <GLFW/glfw3.h>
#include <functional>

class Engine
{
public:
	Engine();
	~Engine();

	void Run();

private:
	void InitVulkan();
	void InitWindow();
	void MainLoop();

	GLFWwindow* window;
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 800;
};

