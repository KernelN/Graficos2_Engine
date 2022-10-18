#pragma once

#include <string>
#include "glfw/include/GLFW/glfw3.h"

class Sprite
{
private:
	unsigned int rendererID;
	std::string filePath;
	unsigned char* localBuffer;
	int width, height, bitsPerPixel;

public:
	Sprite(const std::string& path);
	~Sprite();

	void Bind(unsigned int slot = 0);
	void UnBind() const;

	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }

};
