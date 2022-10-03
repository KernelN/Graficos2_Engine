#include "Base.h"
#include "Window.h"
#include "Renderer.h"
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
    Window* temWindow = (Window*)window;

    /*if (glewInit() != GLEW_OK)
        std::cout << "ENGINE ERROR: GLEW Init failed" << std::endl;*/

    if (!temWindow->WindowExists())
    {
        std::cout << "ENGINE ERROR: Window Init failed" << std::endl;
        isRunning = false;
        glfwTerminate();
        return;
    }


    this->renderer = new Renderer(temWindow);
    Renderer* tempRenderer = (Renderer*)renderer;
    globalRenderer = tempRenderer;


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
    Window* temWindow = (Window*)window;
    Renderer* tempRenderer = (Renderer*)renderer;

    /* Loop until the user closes the window */
    while (!temWindow->WindowShouldClose())
    {
        tempRenderer->BindProgram();

        tempRenderer->ClearScreen();
        
        Draw();

        tempRenderer->SwapWindowBuffers();

        temWindow->ProcessWindowEvents();
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