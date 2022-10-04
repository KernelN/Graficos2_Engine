#include "Window.h"
#include "glew/include/GL/glew.h"
#include "glfw/include/GLFW/glfw3.h"
#include <iostream>

Window::Window(float height, float width) { 
    this->height = height;
    this->width = width;
    CreateWindow(); 
}

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
    window = glfwCreateWindow(height, width, "Hello World", NULL, NULL);
 
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

float Window::GetHeight()
{
    return height;
}

float Window::GetWidth()
{
    return width;
}
