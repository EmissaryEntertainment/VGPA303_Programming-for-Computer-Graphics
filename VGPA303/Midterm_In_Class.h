#pragma once
// Garrett McSpadden Midterm for VGPA303

#define GLEW_STATIC
#include<iostream>
#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include "Debug.h"

//Shader source
const char * vs_source[] =
{
	"#version 450 core                     \n"
	"layout (location = 1) in vec4 aPos;   \n"
	"layout (location = 2) in vec4 aColor; \n"
	"out vec4 ourColor;                    \n"
	"void main()                           \n"
	"{                                     \n"
	"   gl_Position = aPos;                \n"
	"   ourColor = aColor;                 \n"
	"}                                     \n"
};

const char * fs_source[] =
{
	"#version 450 core                             \n"
	"in vec4 ourColor;                             \n"
	"out vec4 color;                               \n"
	"void main()                                   \n"
	"{                                             \n"
	"    color = ourColor;                         \n"
	"}                                             \n"
};

//DATA
float vertices[] = {
	//first triangle
	// positions           // colors
	 0.0,  1.0, 0.5, 1.0,  1.0f, 0.0f, 0.0f, 1.0,  // top	  Red
	 1.0,  0.0, 0.5, 1.0,  0.0f, 1.0f, 0.0f, 1.0,  // right   Green
	-1.0,  0.0, 0.5, 1.0,  1.0f, 1.0f, 1.0f, 1.0,  // left    White
	//second triangle
	 1.0,  0.0, 0.5, 1.0,  0.0f, 1.0f, 0.0f, 1.0,  // right   Green
	 0.0, -1.0, 0.5, 1.0,  0.0f, 0.0f, 1.0f, 1.0,  // Bottom  Blue
	-1.0,  0.0, 0.5, 1.0,  1.0f, 1.0f, 1.0f, 1.0  // left    White
};

//variables
GLuint program, vao;
GLuint buffer;

//functions
void prepare(); //everything that we need to prepare before rendering
void render(); //called in loop to draw graphics

int Run()
{
	GLFWwindow* window;
	/* Initialize the library */
	if (!glfwInit())
		return -1;
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Midterm Diamond", NULL, NULL);
	if (!window)
	{
		glfwTerminate(); return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	//GLEW loads extenstion entry points
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW Failed\n";
		glfwTerminate();
		system("pause");
		return -1;
	}
	// Prepare everything you need with this function call
	prepare();
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		render();

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

void prepare()
{
	//prepare VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//prepare VBO
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	/*TODO //put DATA into the buffer object */
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//prepare Shader Program
	program = glCreateProgram();
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	checkCreateError(fs, "Fragment Shader");
	glShaderSource(fs, 1, fs_source, NULL);
	glCompileShader(fs);
	glAttachShader(program, fs);
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	/*TODO  // put source into vertex shader */
	glShaderSource(vs, 1, vs_source, NULL);
	/*TODO  // compile vertex shader */
	glCompileShader(vs);
	/*TODO  // attach vertex shader to the shader program */
	glAttachShader(program, vs);
	//link the shader program
	glLinkProgram(program);
}

void render()
{
	//Clear background to Black
	float c[] = { 0,0,0,1 };
	glClearBufferfv(GL_COLOR, 0, c);
	/* TODO // Activate the shader program */
	glUseProgram(program);
	/* TODO  // Make sure the buffer is bound. */
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	/* TODO  // Specify the location and data format for position attribute*/
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0);
	/* TODO  //Enable the generic vertex attribute for position*/
	glEnableVertexAttribArray(1);
	/* TODO // Specify the location and data format for color attribute */
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(4 * sizeof(float)));
	/* TODO  //Enable the generic vertex attribute for color*/
	glEnableVertexAttribArray(2);
	/* TODO //draw primitives from array data */
	glDrawArrays(GL_TRIANGLES, 0, 6);
}