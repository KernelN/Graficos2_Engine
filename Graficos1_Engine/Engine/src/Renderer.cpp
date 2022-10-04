#include "Renderer.h"

#include <glew/include/GL/glew.h>
#include <glfw/include/GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <iostream>
#include <fstream>
#include <glm/ext/matrix_transform.hpp>


Renderer::Renderer(Window* window) 
{
	SetWindow(window);

	ShaderData shaders[] =
	{
		{"libs/MatialeEngine/vertexShader.shader", GL_VERTEX_SHADER},
		{"libs/MatialeEngine/fragmentShader.shader", GL_FRAGMENT_SHADER}
	};

	program = new Program(shaders, 2);

	//glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
	glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0,0,0));
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

	glm::mat4 mvp = proj * view * model;

	program->Bind();
	program->SetUniformMat4f("mvp", mvp);
	
	

}

Renderer::~Renderer()
{
	delete program;
}

void Renderer::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::SwapWindowBuffers()
{
	//Check for windows existance
	if (!window)
	{
		std::cout << "RENDERER ERROR: Window Unexistant" << std::endl;
		return;
	}
	else if (!window->WindowExists())
	{
		std::cout << "RENDERER ERROR: GLFW Window Unexistant" << std::endl;
		return;
	}

	/* Swap front and back buffers */
	glfwSwapBuffers((GLFWwindow*)window->GetGLFWPointer());
}

void Renderer::SetWindow(Window* window)
{
	this->window = window;
}

void Renderer::GetNewVertexBuffer
(
#pragma region vars
	unsigned int vComponents,
	unsigned int stride,
	bool dataIsStatic,
	unsigned int attribID,
	//could change to BufferData struct
	void* vData,
	unsigned int* indices,
	unsigned int vAmount,
	unsigned int iAmount,
	unsigned int* vBuffer,
	unsigned int* iBuffer
	//could change to BufferData struct
#pragma endregion
)
{
#pragma region SET VERTEX BUFFER
	//Ask openGL for X buffers (1 in this case) and links them to a uint pointer
	//https://docs.gl/gl4/glGenBuffers
	glGenBuffers(1, vBuffer);

	//Select buffer and set it as array buffer (ideal to work with vertexes)
	//https://docs.gl/gl4/glBindBuffer
	unsigned int vBufferData = *vBuffer;
	glBindBuffer(GL_ARRAY_BUFFER, vBufferData); //maybe problems?

	//Send data to buffer
	//https://docs.gl/gl4/glBufferData
	GLenum dataUsage = dataIsStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;
	unsigned int vDataSize = vAmount * stride;
	glBufferData(GL_ARRAY_BUFFER, vDataSize, vData, dataUsage); //may be a problem
#pragma endregion

#pragma region SET VERTEX ATTRIB POINTER
	//https://docs.gl/gl4/glEnableVertexAttribArray
	glEnableVertexAttribArray(attribID);

	//https://docs.gl/gl4/glVertexAttribPointer
	glVertexAttribPointer(attribID, vComponents, GL_FLOAT, GL_FALSE, stride, 0);
#pragma endregion

#pragma region SET INDEX BUFFER
	//Ask openGL for X buffers (1 in this case) and links them to a uint pointer
	//https://docs.gl/gl4/glGenBuffers
	glGenBuffers(1, iBuffer);

	//Select buffer and set it as element array buffer (ideal to work with indices)
	//https://docs.gl/gl4/glBindBuffer
	unsigned int iBufferData = *iBuffer;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBufferData);

	//Send data to buffer
	//https://docs.gl/gl4/glBufferData
	// index will always be an unsigned int
	//because it's just an index, it doesn't have components
	unsigned int iDataSize = iAmount * sizeof(unsigned int);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, iDataSize, indices, dataUsage);
#pragma endregion
}

void Renderer::DeleteBuffer(unsigned int* buffer)
{
	//Get buffer using index and delete it
	glDeleteBuffers(1, buffer);
}

void Renderer::BindProgram()
{
	program->Bind();
}

void Renderer::Draw(unsigned int indexCount)
{
	//glDrawArrays(GL_TRIANGLES, 0, indexCount);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}