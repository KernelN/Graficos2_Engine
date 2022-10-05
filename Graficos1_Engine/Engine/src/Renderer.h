#pragma once

#include "Window.h"
#include "Data Organizers/Program.h"
#include <string>
#include <stack>
#include <vector> 

class Renderer
{
public:
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
	void BindProgram();
	void Draw(unsigned int indexCount, unsigned int modelID);
	unsigned int GetNewModelID(glm::mat4 model);
	void SetModel(glm::mat4 model, unsigned int modelID);
	glm::mat4 GetModel(unsigned int modelID);

private:
	Window* window;
	Program* program;
	glm::mat4 viewProj;

	std::vector<glm::mat4> models;
};