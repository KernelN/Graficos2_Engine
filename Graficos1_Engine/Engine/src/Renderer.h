#pragma once

#include "Window.h"
#include <string>
#include <stack>

class Renderer
{
public:
	Renderer();
	Renderer(Window* window);
	~Renderer();
	void ClearScreen();
	void SwapWindowBuffers();
	void SetWindow(Window* window);
	void GetNewVertexBuffer(unsigned int componentsPerVertex, unsigned int vertexAmount, unsigned int stride, void* data, bool dataIsStatic, unsigned int* buffer, unsigned int attribID);
	void DeleteBuffer(unsigned int* buffer);
	void CreateAllShaders();
	void CreateProgram();
	void UseProgram();
	void SetFunnyChernoStuff();
	void DrawFunnyChernoStuff();
	void Draw(unsigned int indexCount);
	void AttachShaderToProgram(unsigned int shader);
	unsigned int program;
private:
	Window* window;
	std::stack<unsigned int> shadersCompiling;

	void CreateVertexShader();
	void CreateFragmentShader();
	unsigned int CompileShader(unsigned int type, std::string source);
	void ClearShaders();
};