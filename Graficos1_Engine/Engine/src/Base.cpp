#include "Base.h"
#include "GLFW/glfw3.h"

void Base::DoFunnyStuff()
{
    //--WINDOW ?
    GLFWwindow* window;

    //--BASE
    /* Initialize the library */
    if (!glfwInit())
        //return -1;
        return;

    //--WINDOW ?
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    //--WINDOW ?
    if (!window)
    {
        //--BASE
        glfwTerminate();
        //return -1;
        return;
    }

    //--WINDOW ?
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    //--WINDOW ?
    //--BASE
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        //--RENDER
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //--RENDER?
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        //--BASE
        /* Poll for and process events */
        glfwPollEvents();
    }

    //--BASE
    glfwTerminate();
    //return 0;
}

Base::Base()
{
}

Base::~Base()
{
}