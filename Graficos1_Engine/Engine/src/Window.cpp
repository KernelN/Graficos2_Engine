#include "Window.h"
#include "glew/include/GL/glew.h"
#include "glfw/include/GLFW/glfw3.h"
#include <iostream>

Window::Window() { CreateWindow(); }

Window::~Window(){}

void* Window::GetGLFWPointer()
{
    return window;
}

void Window::ProcessWindowEvents()
{
    //Asks the glfw window for events and processes them
    /* Poll for and process events */
    glfwPollEvents();
}

void Window::CreateWindow()
{
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
 
    if (!WindowExists()) return;

    glfwMakeContextCurrent((GLFWwindow*)window);

    if (glewInit() != GLEW_OK)
        std::cout << "ENGINE ERROR: GLEW Init failed" << std::endl;
}

bool Window::WindowExists()
{
    return window;
}

bool Window::WindowShouldClose()
{
    return glfwWindowShouldClose((GLFWwindow*)window);
}
