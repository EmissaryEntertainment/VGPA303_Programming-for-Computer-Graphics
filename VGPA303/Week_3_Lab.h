#pragma once
// OpenGL Host Program Skeleton
#define GLEW_STATIC
#include<iostream>
#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include "Debug.h"
// variables
GLuint vao;
GLuint program;
GLuint offsetLocation;

//functions
void Prepare();
void Render();

int Run()
{
	GLFWwindow* window;
	/* Initialize the library */
	if (!glfwInit())
		return -1;
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	//Load GLEW
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW Failed. \n";
		glfwTerminate();
		return -1;
	}
	Prepare();
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		Render();
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	glfwTerminate();
	system("pause");
	return 0;
}

void Prepare()
{
	// Declare source code for vertex shader.
	const char * vs_source[] =
	{
		"#version 420 core                                                 \n"
		"layout(location = 0) in vec4 offset;                              \n"
		"layout(location = 1) in vec4 color;                               \n"
		"out vec4 vs_color;                                                \n"
		"void main(void)                                                   \n"
		"{                                                                 \n"
		"    const vec4 vertices[] = vec4[](vec4( 0.25, -0.25, 0.5, 1.0),  \n"
		"                                   vec4(-0.25, -0.25, 0.5, 1.0),  \n"
		"                                   vec4( 0.25,  0.25, 0.5, 1.0)); \n"
		"                                                                  \n"
		"    gl_Position = vertices[gl_VertexID] + offset;                 \n"
		"    vs_color = color;                                             \n"
		"}                                                                 \n"
	};

	// Declare source code for fragment shader.
	const char * fs_source[] =
	{
		"#version 420 core                             \n"
		"in vec4 vs_color;                             \n"
		"out vec4 color;                               \n"
		"void main()                                   \n"
		"{                                             \n"
		"    color = vs_color;                         \n"
		"}                                             \n"
	};

	program = glCreateProgram();
	checkCreateError(program, "Program");
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	checkCreateError(fs, "Fragment Shader");
	glShaderSource(fs, 1, fs_source, NULL);
	glCompileShader(fs);
	printShaderInfoLog(fs);
	

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	checkCreateError(vs, "Vertex Shader");
	glShaderSource(vs, 1, vs_source, NULL);
	glCompileShader(vs);
	printShaderInfoLog(vs);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	printShaderProgramInfoLog(program);

	//glUseProgram(program);
	//offsetLocation = glGetAttribLocation(program,"offset");

	//create Vertex array object
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}


void Render()
{
	// Block below controls background color
	double currentTime = glfwGetTime();
	const GLfloat color[] = { -(float)sin(currentTime) *0.5f + 0.5, -(float)cos(currentTime) *0.5f + 0.5 , 0.7f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, color);

	// Prepare the offset values
	GLfloat attrib[] = { (float)sin(currentTime)*0.5f, (float)cos(currentTime)*0.5f, 0.0f, 0.0f };
	GLfloat vs_color[] = { (float)sin(currentTime) *0.5f + 0.5, (float)cos(currentTime) *0.5f +0.5 , 0.7f, 1.0f };
	
	// Assign the values to "offset"
	glVertexAttrib4fv(0, attrib);
	glVertexAttrib4fv(1, vs_color);
	glUseProgram(program);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}