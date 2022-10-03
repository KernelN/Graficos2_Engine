#include "Base.h"
#include <glfw/include/GLFW/glfw3.h>
#include <iostream>
#include "Entity/Entity2D/Shape/Shapes/Triangle.h"
#include "Entity/Entity2D/Shape/Shapes/Square.h"

Triangle* triangle;
Square* square;

BaseEngine::BaseEngine()
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


    this->renderer = new Renderer(window);
    globalRenderer = this->renderer;


    /*float tVertices[8] = 
    { 
        -0.5, -0.5,
        0.5, -0.5,
        0.5, 0.5,
        -0.5, 0.5
    };*/
    /*triangle = new Triangle(tVertices, true);
    square = new Square(tVertices, true);*/
}

BaseEngine::~BaseEngine()
{
    glfwTerminate();
    delete renderer;
    delete window;
}

bool BaseEngine::IsRunning()
{
    return isRunning;
}

void BaseEngine::Loop()
{
    /* Loop until the user closes the window */
    while (!window->WindowShouldClose())
    {
        renderer->BindProgram();

        renderer->ClearScreen();
        
        Draw();

        renderer->SwapWindowBuffers();

        window->ProcessWindowEvents();
    }

    //Close glfw
    glfwTerminate();

    isRunning = false;
}

void BaseEngine::Draw()
{
    //triangle->Draw();
    //square->Draw();
    //renderer->DrawFunnyChernoStuff();
}