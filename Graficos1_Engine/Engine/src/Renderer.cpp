#include "Renderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

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
						(unsigned int componentsPerVertex, unsigned int dataSize, void* data, 
								bool dataIsStatic, unsigned int* buffer)
{
	//Ask openGL for X buffers (1 in this case) and links them to a uint pointer
	//https://docs.gl/gl4/glGenBuffers
	glGenBuffers(1, buffer);

	//Select buffer and set it as array buffer (ideal to work with vertexes)
	//https://docs.gl/gl4/glBindBuffer
	glBindBuffer(GL_ARRAY_BUFFER, *buffer);

	//Send data to buffer
	//https://docs.gl/gl4/glBufferData
	GLenum dataUsage = dataIsStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, dataUsage);

	//https://docs.gl/gl4/glEnableVertexAttribArray
	glEnableVertexAttribArray(0);

	//https://docs.gl/gl4/glVertexAttribPointer
	glVertexAttribPointer(0, componentsPerVertex, GL_FLOAT, GL_FALSE, dataSize, 0);
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
	// TEMP CLEAN LATER
	std::string tempVertexShader =
		"#version 330 core\n "
		"\n"
		"layout(location = 0) in vec4 position;\n"
		"\n"
		"void main()\n"
		"{\n"
		"gl_Position = position;\n"
		"}\n";

	unsigned int vs = CompileShader(GL_VERTEX_SHADER, tempVertexShader);

	AttachShaderToProgram(vs);
	shadersCompiling.push(vs);
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

void Renderer::CreateFragmentShader()
{
	// TEMP CLEAN LATER
	std::string tempFragmentShader =
		"#version 330 core\n "
		"\n"
		"layout(location = 0) out vec4 color;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	color = vec4(1.0, 0.0, 0.0, 1.0);\n"
		"}\n";

	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, tempFragmentShader);

	AttachShaderToProgram(fs);
	shadersCompiling.push(fs);
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
	//THIS BREAKS
	float tVertices[6] = { 0.5, 0.0, 0.0, 0.5, 0.0, -0.5 };

	unsigned int buffer;

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), tVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	//THIS BREAKS

	this->CreateProgram();
	this->CreateAllShaders();
	this->UseProgram();
}

void Renderer::DrawFunnyChernoStuff()
{
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::ClearShaders()
{
	while (!shadersCompiling.empty())
	{
		glDeleteShader(shadersCompiling.top());
		shadersCompiling.pop();
	}
}

void Renderer::AttachShaderToProgram(unsigned int shader)
{
	glAttachShader(program, shader);
}