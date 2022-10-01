#include "Renderer.h"

#include <glew/include/GL/glew.h>
#include <glfw/include/GLFW/glfw3.h>
#include <iostream>
#include <fstream>

Renderer::Renderer(){}

Renderer::Renderer(Window* window) 
{
	SetWindow(window);
}

Renderer::~Renderer(){}

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

void Renderer::CreateAllShaders()
{
	CreateVertexShader();
	CreateFragmentShader();
}

void Renderer::CreateVertexShader()
{
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, ReadShader("libs/MatialeEngine/vertexShader.shader"));

	AttachShaderToProgram(vs);
	shadersCompiling.push(vs);
}

void Renderer::CreateFragmentShader()
{
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, ReadShader("libs/MatialeEngine/fragmentShader.shader"));

	AttachShaderToProgram(fs);
	shadersCompiling.push(fs);
}

unsigned int Renderer::CompileShader(unsigned int type, std::string source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile: " << (type == GL_VERTEX_SHADER ? "vertex " : "fragment") << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

void Renderer::CreateProgram()
{
	program = glCreateProgram();
}

void Renderer::UseProgram()
{
	glLinkProgram(program);
	glValidateProgram(program);
	ClearShaders();
	glUseProgram(program);
}

void Renderer::SetFunnyChernoStuff()
{
	// WITHOUT THIS BREAKS
	float tVertices[] = { 
		-0.5f, -0.5f, // 0
		0.5f, -0.5f, // 1
		0.5f, 0.5f, // 2
		-0.5f, 0.5f // 3	
		//-0.5f, 0.5f // 3
	};
	//float tVertices[] = { 
	//	-1, -1, // 0
	//	1, -1, // 1
	//	1, 1 // 2
	//	-1, 1 // 3	
	//};

	unsigned int indices[] = {
		/*1, 2, 3,		
		0, 1, 3,*/
		0, 1, 2,
		2, 3, 0
	};

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), tVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	
	//THIS BREAKS

	this->CreateProgram();
	this->CreateAllShaders();
	this->UseProgram();
}

void Renderer::DrawFunnyChernoStuff()
{
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Renderer::Draw(unsigned int indexCount)
{
	//glDrawArrays(GL_TRIANGLES, 0, indexCount);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}

void Renderer::ClearShaders()
{
	while (!shadersCompiling.empty())
	{
		glDeleteShader(shadersCompiling.top());
		shadersCompiling.pop();
	}
}

std::string Renderer::ReadShader(std::string fileDir)
{
	std::string shaderLine;
	std::string tempShader = "";
		
	std::ifstream inputStream;
	inputStream.open(fileDir);

	while (getline(inputStream, shaderLine))
	{
		tempShader += shaderLine + '\n';
	}
	
	inputStream.close();

	return tempShader;
}

void Renderer::AttachShaderToProgram(unsigned int shader)
{
	glAttachShader(program, shader);
}