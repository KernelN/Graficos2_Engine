#pragma once

class Window
{
public:
	Window();
	~Window();
	bool WindowExists();
	bool WindowShouldClose();
private:
	void* window;
	void CreateWindow();
};