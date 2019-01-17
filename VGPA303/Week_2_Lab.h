#pragma once
#define GLEW_STATIC

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//Create the window
GLFWwindow* window;
//Create a vertex shader
GLuint vs;
//Create a fragment shader
GLuint fs;
//Create program
GLuint program;

GLuint vao;

int PrePrepare()
{
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
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW failed. \n";
		glfwTerminate();
		return -1;
	}
}

void Prepare()
{
	//Compose GLSL source code
	const char* vs_source[] = {
		"#version 420 core                       \n"
		"void main(void)                         \n"
		"{                                       \n"
		"	vec4 vertices[] = vec4[](            \n"
		"                 vec4(1.0,-1.0,0.5,1.0),"
		"                vec4(-1.0,-1.0,0.5,1.0),"
		"                  vec4(0.0,1.0,0.5,1.0)"
		"                           );           \n"
		"	gl_Position = vertices[gl_VertexID];              \n"
		"}                                       \n"
	};
	const char* fs_source[] = {
		"#version 420 core                 \n"
		"out vec4 color;                   \n"
		"void main(void)                   \n"
		"{                                 \n"
		"	color = vec4(0.0,0.8,1.0,1.0); \n"
		"}                                 \n"
	};
	vs = glCreateShader(GL_VERTEX_SHADER);
	//Put source code into the shader
	glShaderSource(vs, 1, vs_source, NULL);
	//Compile
	glCompileShader(vs);

	fs = glCreateShader(GL_FRAGMENT_SHADER);
	//Put source code into the shader
	glShaderSource(fs, 1, fs_source, NULL);
	//Compile
	glCompileShader(fs);

	program = glCreateProgram();
	//Attach shaders to program
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	//Link program
	glLinkProgram(program);


	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

void Render()
{
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Turn window background red
		float red[] = { 1.0,0.0,0.0,1.0 };
		glClearBufferfv(GL_COLOR, 0, red); */

		//glClearColor(0.5, 0.2, 1.0, 1.0); //This does the same as the code directly above it.

		GLfloat color[] =
		{
			(float)sin(glfwGetTime())*0.5 + 0.5,
			(float)cos(glfwGetTime())*0.5 + 0.5,
			0.0,
			1.0
		};
		glClearBufferfv(GL_COLOR, 0, color);

		//Activate the program from above
		glUseProgram(program);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	glfwTerminate();
}