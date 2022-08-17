#pragma once

class Window
{
public:
	Window();
	~Window();
	void* GetGLFWPointer();
	void ProcessWindowEvents();
	bool WindowExists();
	bool WindowShouldClose();
private:
	void* window;
	void CreateWindow();
};