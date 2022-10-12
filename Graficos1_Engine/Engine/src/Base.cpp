#include "Base.h"
#include "Utility/Singleton.h"
#include "InputManager.h"
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

    window = new Window(640, 480);
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


    Singleton::SetRenderer(new Renderer(temWindow));
    renderer = Singleton::GetRenderer();

    inputManager = new InputManager(temWindow->GetGLFWPointer());

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
    delete inputManager;
}

bool BaseEngine::IsRunning()
{
    return isRunning && !((Window*)window)->WindowShouldClose();
}

void BaseEngine::Loop()
{
    Window* temWindow = (Window*)window;
    Renderer* tempRenderer = (Renderer*)renderer;
 
    OnLoop();

    tempRenderer->BindProgram();

    tempRenderer->ClearScreen();
        
    Draw();

    tempRenderer->SwapWindowBuffers();

    temWindow->ProcessWindowEvents();
   
}

void BaseEngine::OnLoop()
{

}

void BaseEngine::Draw()
{
    //triangle->Draw();
    //square->Draw();
    //renderer->DrawFunnyChernoStuff();
}

bool BaseEngine::IsKeyPressed(unsigned short KeyCode)
{
    return ((InputManager*)inputManager)->IsKeyPressed(KeyCode);
}

