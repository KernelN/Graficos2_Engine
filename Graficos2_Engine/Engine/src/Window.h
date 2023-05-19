#pragma once

class Window
{
public:
	Window(float height, float width);
	~Window();
	void* GetGLFWPointer();
	void ProcessWindowEvents();
	bool WindowExists();
	bool WindowShouldClose();
	float GetHeight();
	float GetWidth();
private:
	void* window;
	float height;
	float width;
	void CreateWindow();
};