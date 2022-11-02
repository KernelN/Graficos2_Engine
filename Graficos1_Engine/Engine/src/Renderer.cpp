#include "Renderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include <Utility/stb_image.h>
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
		{"shaders/vertexShader_sprite.shader", GL_VERTEX_SHADER},
		{"shaders/fragmentShader_sprite.shader", GL_FRAGMENT_SHADER}
		//{"shaders/vertexShader.shader", GL_VERTEX_SHADER},
		//{"shaders/fragmentShader.shader", GL_FRAGMENT_SHADER}
	};

	program = new Program(shaders, 2);

	//glm::mat4 proj = glm::ortho(0.0f, window->GetHeight(), 0.0f, window->GetWidth(), -1.0f, 1.0f);
	glm::mat4 proj = glm::ortho(-window->GetHeight()/2, window->GetHeight() / 2, -window->GetWidth() / 2, window->GetWidth()/2, -1.0f, 1.0f);
	
	//"Camera" - vec sets position (if "Camera" should move to the right, mvp matrix will move everything to the left)
	//glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0,0,0));
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	viewProj = proj * view;

	models = std::vector<glm::mat4>();

	SetUniversalSpriteSettings();
}

Renderer::~Renderer()
{
	//Delete Program
	delete program;

	//Delete Buffers
	for (unsigned short i = 0; i < vertexBuffers.size(); i++)
	{
		delete vertexBuffers[i];
	}
	for (unsigned short i = 0; i < indexBuffers.size(); i++)
	{
		delete indexBuffers[i];
	}
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

void Renderer::Draw(unsigned int indexCount, unsigned int modelID)
{
	BindProgram();
	BindBuffers();

	program->SetUniformMat4f("mvp", viewProj * models[modelID]);
	//program->SetUniform4f("_color", viewProj * models[modelID]);

	//https://docs.gl/gl4/glDrawElements
	//glDrawArrays(GL_TRIANGLES, 0, indexCount);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}

#pragma region Buffers & Program

//void Renderer::GetNewVertexBuffer
//(
//#pragma region vars
//	unsigned int vComponents,
//	unsigned int stride,
//	bool dataIsStatic,
//	unsigned int attribID,
//	//could change to BufferData struct
//	void* vData,
//	unsigned int* indices,
//	unsigned int vAmount,
//	unsigned int iAmount,
//	unsigned int* vBuffer,
//	unsigned int* iBuffer
//	//could change to BufferData struct
//#pragma endregion
//)
//{
//#pragma region SET VERTEX BUFFER
//	//Ask openGL for X buffers (1 in this case) and links them to a uint pointer
//	//https://docs.gl/gl4/glGenBuffers
//	glGenBuffers(1, vBuffer);
//
//	//Select buffer and set it as array buffer (ideal to work with vertexes)
//	//https://docs.gl/gl4/glBindBuffer
//	unsigned int vBufferData = *vBuffer;
//	glBindBuffer(GL_ARRAY_BUFFER, vBufferData); //maybe problems?
//
//	//Send data to buffer
//	//https://docs.gl/gl4/glBufferData
//	GLenum dataUsage = dataIsStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;
//	unsigned int vDataSize = vAmount * stride;
//	glBufferData(GL_ARRAY_BUFFER, vDataSize, vData, dataUsage); //may be a problem
//#pragma endregion
//
//#pragma region SET VERTEX ATTRIB POINTER
//	////https://docs.gl/gl4/glVertexAttribPointer
//	//glVertexAttribPointer(attribID, vComponents, GL_FLOAT, GL_FALSE, stride, 0);
//
//	////https://docs.gl/gl4/glEnableVertexAttribArray
//	//glEnableVertexAttribArray(attribID);
//
//	//SET POS
//	//https://docs.gl/gl4/glVertexAttribPointer
//	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (void*)0);
//
//	//https://docs.gl/gl4/glEnableVertexAttribArray
//	glEnableVertexAttribArray(0);
//
//	//SET COLOR
//	//https://docs.gl/gl4/glVertexAttribPointer
//	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (void*)(2*sizeof(float)));
//
//	//https://docs.gl/gl4/glEnableVertexAttribArray
//	glEnableVertexAttribArray(1);
//#pragma endregion
//
//#pragma region SET INDEX BUFFER
//	//Ask openGL for X buffers (1 in this case) and links them to a uint pointer
//	//https://docs.gl/gl4/glGenBuffers
//	glGenBuffers(1, iBuffer);
//
//	//Select buffer and set it as element array buffer (ideal to work with indices)
//	//https://docs.gl/gl4/glBindBuffer
//	unsigned int iBufferData = *iBuffer;
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBufferData);
//
//	//Send data to buffer
//	//https://docs.gl/gl4/glBufferData
//	// index will always be an unsigned int
//	//because it's just an index, it doesn't have components
//	unsigned int iDataSize = iAmount * sizeof(unsigned int);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, iDataSize, indices, dataUsage);
//#pragma endregion
//}

void Renderer::GetNewVertexBuffer(const void* data, unsigned int dataSize)
{
	//VertexBuffer vb(data, 4 * 2 * sizeof(float), true);

	VertexBuffer* vb = new VertexBuffer(data, dataSize, true);
	vertexBuffers.push_back(vb);

	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(*vb, layout);
}

void Renderer::GetNewIndexBuffer(unsigned int* indices, unsigned int indexAmmount)
{
	IndexBuffer* ib = new IndexBuffer(indices, indexAmmount);
	indexBuffers.push_back(ib);
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

void Renderer::BindBuffers()
{
	va.Bind();

	for (unsigned short i = 0; i < indexBuffers.size(); i++)
	{
		indexBuffers[i]->Bind();
	}
}
#pragma endregion

#pragma region Model

unsigned int Renderer::GetNewModelID(glm::mat4 model)
{
	unsigned int newModelID = models.size();
	models.push_back(model);
	return newModelID;
}

void Renderer::SetModel(glm::mat4 model, unsigned int modelID)
{
	models[modelID] = model;
}

glm::mat4 Renderer::GetModel(unsigned int modelID)
{
	return models[modelID];
}

#pragma endregion

#pragma region Sprite

void Renderer::GetSprite(std::string imgPath, int* width, int* height, int* bpp, unsigned int* spriteID)
{
	unsigned char* localBuffer = nullptr;

	stbi_set_flip_vertically_on_load(1);

	//bpp = Bits per Pixel
	localBuffer = stbi_load(imgPath.c_str(), width, height, bpp, 4);

	//https://docs.gl/gl4/glGenTextures
	glGenTextures(1, spriteID);

	//https://docs.gl/gl4/glBindTexture
	glBindTexture(GL_TEXTURE_2D, *spriteID);

	//If image didn't load exit
	if (!localBuffer) return;

	//https://docs.gl/gl4/glTexImage2D
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, *width, *height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	//Free buffer/image from stbi
	stbi_image_free(localBuffer);
}

void Renderer::SetSprite(unsigned int value)
{
	program->SetUniform1i("u_Sprite", 0);
}

void Renderer::DeleteSprite(unsigned int* spriteID)
{
	glDeleteTextures(1, spriteID);
}

void Renderer::BindSprite(unsigned int slot, unsigned int spriteID)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, spriteID);
}

void Renderer::UnbindSprite()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::SetUniversalSpriteSettings()
{
	//https://docs.gl/gl4/glTexParameteri
	///SET MIPMAPPING VARS
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	///SET WRAPPING VARS
	//Repeat: repeats image in empty space
	//Mirror Repeat: repeats image, but mirroring it
	//Clamp Border: stretches image to edge of screen
	//Clamp Edge: fills empty space left by image with color
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	//Enable blending, so images with transparency can be draw
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

#pragma endregion