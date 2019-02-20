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

void prepareVao(GLuint& vertexArrayObject)
{
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);
	checkOpenGLError("PrepareVao");
}

void prepareVbo(GLuint& vertexBufferObject, float data[], GLbyte dataSize)
{
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
	checkOpenGLError("PrepareVbo");
}

void prepareEbo(GLuint& elementBufferObject, GLuint data[], GLbyte dataSize)
{
	glGenBuffers(1, &elementBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
	checkOpenGLError("PrepareEbo");
}

void connectBufferToAttrib(GLuint attribLocation, GLint vertexCount, GLint strideSize, GLint startingPos)
{
	glEnableVertexAttribArray(attribLocation);
	//tell OpenGL How to load buffer data
	glVertexAttribPointer(attribLocation, vertexCount, GL_FLOAT, GL_FALSE, strideSize * sizeof(float), (GLvoid*)(startingPos * sizeof(float)));
}

#endif // !FUNCTIONS_H