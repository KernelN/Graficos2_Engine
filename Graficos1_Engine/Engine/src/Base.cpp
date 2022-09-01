#include "Base.h"
#include <GLFW/glfw3.h>
#include <iostream>

Base::Base()
{
    //Initialize glfw
    if (!glfwInit())
    {
        std::cout << "ENGINE ERROR: GLFW Init failed" << std::endl;
        isRunning = false;
        return;
    }

    window = new Window();

    /*if (glewInit() != GLEW_OK)
        std::cout << "ENGINE ERROR: GLEW Init failed" << std::endl;*/

    if (!window->WindowExists())
    {
        std::cout << "ENGINE ERROR: Window Init failed" << std::endl;
        isRunning = false;
        glfwTerminate();
        return;
    }

    renderer = new Renderer(window);
}

Base::~Base()
{
    glfwTerminate();
    delete renderer;
    delete window;
}

bool Base::IsRunning()
{
    return isRunning;
}

void Base::Loop()
{
    /* Loop until the user closes the window */
    while (!window->WindowShouldClose())
    {
        Draw();
        renderer->ClearScreen();

        renderer->SwapWindowBuffers();

        window->ProcessWindowEvents();
    }

    //Close glfw
    glfwTerminate();

    isRunning = false;
}