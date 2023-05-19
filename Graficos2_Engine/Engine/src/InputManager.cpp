#include "InputManager.h"


InputManager::InputManager(GLFWwindow* _window)
{
	window = _window;
}

InputManager::~InputManager()
{
}

bool InputManager::IsKeyPressed(unsigned int keyCode)
{
	int state = glfwGetKey(window, keyCode);
	bool isPressed = state == GLFW_PRESS;

	return isPressed;
}
