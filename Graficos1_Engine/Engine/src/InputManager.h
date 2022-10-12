#pragma once
#include "glfw/include/GLFW/glfw3.h"

class InputManager
{
public:
	InputManager(GLFWwindow* _window);
	~InputManager();
	bool IsKeyPressed(unsigned int keyCode);
private:
	GLFWwindow* window;
	
};