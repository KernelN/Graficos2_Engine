#include "Window.h"
#include "GLFW/glfw3.h"

Window::Window() { CreateWindow(); }

Window::~Window()
{
    delete window;
}

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
}

bool Window::WindowExists()
{
    return window;
}

bool Window::WindowShouldClose()
{
    return glfwWindowShouldClose((GLFWwindow*)window);
}
