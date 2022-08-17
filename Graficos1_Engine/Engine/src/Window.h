#pragma once

class Window
{
public:
	Window();
	~Window();
	void PollEvents();
	bool WindowExists();
	bool WindowShouldClose();
private:
	void* window;
	void CreateWindow();
};