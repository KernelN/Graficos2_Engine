#include "Base.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "Entity/Entity2D/Shape/Shapes/Triangle.h"
#include "Entity/Entity2D/Shape/Shapes/Square.h"

Triangle* triangle;
Square* square;

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

    float tVertices[8] = 
    { 
        -0.5, -0.5,
        0.5, -0.5,
        0.5, 0.5,
        -0.5, 0.5
    };
    triangle = new Triangle(tVertices, true, renderer);
    square = new Square(tVertices, true, renderer);

    renderer->CreateProgram();
    renderer->CreateAllShaders();
    renderer->UseProgram();
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
    square->Draw();
    //renderer->DrawFunnyChernoStuff();
}