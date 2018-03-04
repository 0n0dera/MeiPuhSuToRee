#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

class WindowManager
{
public:
	WindowManager(GLuint width = 800, const GLuint height = 600);
	~WindowManager();
	GLFWwindow* GetWindow();

private:
	const GLuint WIDTH;
	const GLuint HEIGHT;

	GLFWwindow* window;

	void init();
};