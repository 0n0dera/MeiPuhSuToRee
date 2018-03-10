#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

class Shader
{
public:
	Shader(const GLchar* vertex_path, const GLchar* fragment_path);
	void Use();
	GLuint Pid() const;
private:
	const std::string SHADER_BASE = "shaders/";
	GLuint pid_;
};