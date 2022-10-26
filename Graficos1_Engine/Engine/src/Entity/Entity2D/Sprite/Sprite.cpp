//#include "Sprite.h"
//
//#include "Utility/stb_image.h"
//#include <glew/include/GL/glew.h>
//#include "glfw/include/GLFW/glfw3.h"
//
//Sprite::Sprite(const std::string& path)
//{
//	rendererID = 0;
//	filePath = path;
//	localBuffer = nullptr;
//	width = 0;
//	height = 0;
//	bitsPerPixel = 0;
//
//	stbi_set_flip_vertically_on_load(1);
//	localBuffer = stbi_load(path.c_str(), &width, &height, &bitsPerPixel, 4);
//
//	glGenTextures(1, &rendererID);
//	glBindTexture(GL_TEXTURE_2D, rendererID);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
//
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_INT, localBuffer);
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//	if (localBuffer)
//		stbi_image_free(localBuffer);
//
//}
//
//Sprite::~Sprite()
//{
//	glDeleteTextures(1, &rendererID);
//}
//
//void Sprite::Bind(unsigned int slot)
//{
//	glActiveTexture(GL_TEXTURE0 + slot);
//	glBindTexture(GL_TEXTURE_2D, rendererID);
//}
//
//void Sprite::UnBind() const
//{
//	glBindTexture(GL_TEXTURE_2D, 0);
//}
