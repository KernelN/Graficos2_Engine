#include "Base.h"
#include "Utility/RendererSingleton.h"
#include "Utility/TimeSingleton.h"
#include "InputManager.h"
#include "Window.h"
#include "Renderer.h"
#include <glfw/include/GLFW/glfw3.h>
#include <iostream>

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

    Renderer* tempRenderer = new Renderer(temWindow);
    RendererSingleton::SetRenderer(tempRenderer);
    renderer = tempRenderer;
    
    tempRenderer->SetCamera(new Camera());

    GLFWwindow* tempGLFWwindow = ((GLFWwindow*)temWindow->GetGLFWPointer());

    inputManager = new InputManager(tempGLFWwindow);

    time = new Time();
    TimeSingleton::SetTime(time);

    collisionManager = new CollisionManager();
}

BaseEngine::~BaseEngine()
{
    glfwTerminate();
    delete renderer;
    delete window;
    delete inputManager;
    delete collisionManager;
}

bool BaseEngine::IsRunning()
{
    return isRunning && !((Window*)window)->WindowShouldClose();
}

void BaseEngine::Loop()
{
    Window* temWindow = (Window*)window;
    Renderer* tempRenderer = (Renderer*)renderer;

    tempRenderer->SetView();
    
    time->Update();
 
    OnLoop();

    //tempRenderer->BindProgram();
    //tempRenderer->BindBuffers();

    tempRenderer->ClearScreen();
      
    tempRenderer->BindProgram();

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