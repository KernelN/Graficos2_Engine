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
	void GetNewVertexBuffer
	(
		unsigned int vComponents,
		unsigned int stride,
		bool dataIsStatic,
		unsigned int attribID,
		void* vData,
		unsigned int* indices,
		unsigned int vAmount,
		unsigned int iAmount,
		unsigned int* vBuffer,
		unsigned int* iBuffer
	);
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

static Renderer* globalRenderer;