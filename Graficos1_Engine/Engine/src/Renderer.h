#pragma once

#include "Window.h"
#include "Data Organizers/Program.h"
#include "Data Organizers/Buffer/Arrays/VertexArray.h"
#include "Data Organizers/Buffer/IndexBuffer.h"
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
	void Draw(unsigned int vertexBuffer, unsigned int indexBuffer, unsigned int modelID);

#pragma region Buffers & Program
	//void GetNewVertexBuffer
	//(
	//	unsigned int vComponents,
	//	unsigned int stride,
	//	bool dataIsStatic,
	//	unsigned int attribID,
	//	void* vData,
	//	unsigned int* indices,
	//	unsigned int vAmount,
	//	unsigned int iAmount,
	//	unsigned int* vBuffer,
	//	unsigned int* iBuffer
	//);
	void DeleteBuffer(unsigned int* buffer);
	void BindProgram();
	void BindBuffers();
	unsigned int GetNewVertexBuffer(const void* data, unsigned int dataSize);
	void SetVertexBuffer(unsigned int bufferID, const void* data, unsigned int dataSize);
	unsigned int GetNewIndexBuffer(unsigned int* indices, unsigned int indexAmmount);
#pragma endregion

#pragma region Model
	unsigned int GetNewModelID(glm::mat4 model);
	void SetModel(glm::mat4 model, unsigned int modelID);
	glm::mat4 GetModel(unsigned int modelID);
#pragma endregion

#pragma region Sprite
	void GetNewSprite(std::string imgPath, int* width, int* height, int* bpp, unsigned int* imageID);
	void GetNewSprite(int* width, int* height, int* bpp, unsigned int* imageID);
	void SetSprite(unsigned int value);
	void DeleteSprite(unsigned int* spriteID);
	void BindSprite(unsigned int slot, unsigned int spriteID);
	void UnbindSprite();
#pragma endregion

private:
	Window* window;
	Program* program;
	glm::mat4 viewProj;

	std::vector<glm::mat4> models;
	std::vector<VertexBuffer*> vertexBuffers;
	std::vector<IndexBuffer*> indexBuffers;
	std::vector<VertexArray*> vertexArrays;

	void SetUniversalSpriteSettings();
};