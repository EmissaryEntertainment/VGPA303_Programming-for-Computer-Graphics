#pragma once
#include<iostream>
#include<string>


//call this after glCreateShader(), glCreateProgram()
void checkCreateError(int objectId, const std::string objectName)
{
	if (objectId == 0)
	{
		std::cout << "Error in creating " << objectName << std::endl;
	}
}

//call this function after glCompileShader()
void printShaderInfoLog(GLuint shader)
{
	/*
This code is the original program and has been replaced by the glGetShaderiv() function

int maxLength = 1024;
char infoLog[1024];
int infoLogLength = 0;
if (glIsShader(shader))
{
	glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
}
if (infoLogLength > 0)
{
	std::cout << "Shader: \n" << infoLog << std::endl;
}*/
	GLint success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

//call this function after glLinkProgram()
void printShaderProgramInfoLog(GLuint shaderProgram)
{
	/*
This code is the original program and has been replaced by the glGetShaderiv() function

int maxLength = 1024;
char infoLog[1024];
int infoLogLength = 0;
if (glIsShader(shaderProgram))
{
	glGetShaderInfoLog(shaderProgram, maxLength, &infoLogLength, infoLog);
}
if (infoLogLength > 0)
{
	std::cout << "Shader Program: \n" << infoLog << std::endl;
}*/
	GLint success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}

std::string getErrorString(GLenum error)
{
	std::string msg;
	switch (error)
	{
		case GL_NO_ERROR: msg = "GL_NO_ERROR"; break;
		case GL_INVALID_VALUE: msg = "GL_INVALID_VALUE"; break;
		case GL_INVALID_ENUM: msg = "GL_INVALID_ENUM"; break;
		case GL_STACK_OVERFLOW: msg = "GL_STACK_OVERFLOW"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: msg = "GL_INVALID_FRAMEBUFFER_OPERATION"; break;
		default: msg = "Undefined."; break;
	}
	return msg;
}

// Call at the end of each function
void checkOpenGLError(const std::string functionName)
{
	GLenum error = glGetError();
	std::string msg;
	while (error != GL_NO_ERROR)
	{
		msg = getErrorString(error);
		if (msg.size() > 0)
		{
			std::cout << "Errors in " << functionName << ": " << msg << std::endl;
		}
		error = glGetError();
	}
}