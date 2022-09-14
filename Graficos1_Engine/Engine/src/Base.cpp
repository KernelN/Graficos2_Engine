#include "Base.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "Entity/Entity2D/Shape/Shapes/Triangle.h"

Triangle* triangle;

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

    //float tVertices[6] = { 0.5, 0.0, 0.0, 0.5, 0.0, -0.5 };
    //triangle = new Triangle(tVertices, true, renderer);

    /*renderer->CreateProgram();
    renderer->CreateAllShaders();
    renderer->UseProgram();*/

    renderer->SetFunnyChernoStuff();
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
        renderer->ClearScreen();
        
        Draw();

        renderer->SwapWindowBuffers();

        window->ProcessWindowEvents();
    }

    //Close glfw
    glfwTerminate();

    isRunning = false;
}

void Base::Draw()
{
    //triangle->Draw();
    renderer->DrawFunnyChernoStuff();
}