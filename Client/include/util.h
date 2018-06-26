#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

namespace util {

const std::string SHADER_BASE = "shaders/";

GLuint genShader(const GLchar* vertex_path, const GLchar* fragment_path) {
	std::string vertex_code;
	std::string fragment_code;
	std::ifstream v_shader_file;
	std::ifstream f_shader_file;
	v_shader_file.exceptions(std::ifstream::badbit);
	f_shader_file.exceptions(std::ifstream::badbit);
	try
	{
		// Open files
		v_shader_file.open(SHADER_BASE + vertex_path);
		f_shader_file.open(SHADER_BASE + fragment_path);
		std::stringstream v_shader_stream, f_shader_stream;
		// Read file's buffer contents into streams
		v_shader_stream << v_shader_file.rdbuf();
		f_shader_stream << f_shader_file.rdbuf();
		// Close file handlers
		v_shader_file.close();
		f_shader_file.close();
		// Convert streams into GLchar array
		vertex_code = v_shader_stream.str();
		fragment_code = f_shader_stream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR:SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const GLchar* v_shader_code = vertex_code.c_str();
	const GLchar* f_shader_code = fragment_code.c_str();

	// Compile and link
	GLuint vertex_shader, fragment_shader;
	GLint success;
	GLchar infoLog[512];

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &v_shader_code, NULL);
	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
		std::cout << vertex_path << std::endl << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &f_shader_code, NULL);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
		std::cout << fragment_path << std::endl << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Create and link program
	GLuint pid = glCreateProgram();
	glAttachShader(pid, vertex_shader);
	glAttachShader(pid, fragment_shader);
	glLinkProgram(pid);
	glGetProgramiv(pid, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(pid, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// Don't need shader objects after shader program is linked
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return pid;
}

GLfloat getAngleDotProduct(const glm::vec3& v1, const glm::vec3& v2) {
	return glm::acos(glm::dot(v1, v2) / glm::length(v1) / glm::length(v2));
}

}