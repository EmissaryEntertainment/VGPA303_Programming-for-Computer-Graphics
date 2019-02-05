#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#define GLEW_STATIC
#include<iostream>
#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include "Debug.h"

GLuint PrepareShaderProgram(const char** vs_s, const char** fs_s)
{
	GLuint program = glCreateProgram();
	checkCreateError(program, "Program");
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	checkCreateError(fs, "Fragment Shader");
	glShaderSource(fs, 1, fs_s, NULL);
	glCompileShader(fs);
	printShaderInfoLog(fs);


	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	checkCreateError(vs, "Vertex Shader");
	glShaderSource(vs, 1, vs_s, NULL);
	glCompileShader(vs);
	printShaderInfoLog(vs);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	printShaderProgramInfoLog(program);

	return program;
}

#endif // !FUNCTIONS_H