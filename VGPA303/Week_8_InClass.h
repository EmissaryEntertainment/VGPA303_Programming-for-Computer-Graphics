#pragma once
// OpenGL Host Program Skeleton
#define GLEW_STATIC
#define GLM_ENABLE_EXPERIMENTAL
#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Functions.h"

const char* vs_source[] = {
	"#version 450 core\n"
	"layout(location = 0) in vec4 vPos;"
	"layout(location = 0) uniform mat4 mx;"
	"void main()"
	"{"
	"    gl_Position = mx * vPos;"
	"} "
};

const char* fs_source[] = {
	"#version 450 core \n"
	"out vec4 color;"
	"void main()"
	"{"
	"    color =  vec4(1.0, 0.0, 0.0, 1.0); "
	"} "
};

GLfloat pos[] = {
	//First Triangle
	 0.5,  0.5, 0.0, 1.0,       //top right			0
	 0.5, -0.5, 0.0, 1.0,        //bottom right		1
	-0.5, -0.5, 0.0, 1.0,       //bottom left		2
};

// variables
GLuint vao, program;
GLuint vboPositions, vboColors, ebo;
float speed;
//functions
void prepare();
void render();
//


int Run()
{
	GLFWwindow* window;
	/* Initialize the library */
	if (!glfwInit())
		return -1;
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Color Interpolation Triangle", NULL, NULL);
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
	prepare();
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

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
	//vao
	prepareVao(vao);
	//program
	program = PrepareShaderProgram(vs_source, fs_source);
	//Positions
	//vbo for position

	prepareVbo(vboPositions, pos, sizeof(pos));
	connectBufferToAttrib(0, 4, 4, 0);

	checkOpenGLError("prepare()");
}

void render()
{
	speed += 0.001f;

	GLfloat darkbg[] = { 0.0, 0.0, 0.0, 1.0 };
	glClearBufferfv(GL_COLOR, 0, darkbg);

	glUseProgram(program);

	float rotationMatrix[] = { 1, 0, 0, 0,
							   0, cos((float)M_PI), sin((float)M_PI), 0,
							   0, -sin((float)M_PI), cos((float)M_PI), 0,
							   0, 0, 0, 1 };

	//First Triangle
	glm::mat4 t = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));
	glm::mat4 r = glm::rotate(glm::mat4(1.0f),glm::radians(speed * 100),glm::vec3(0.0f,0.0f,1.0f));
	glm::mat4 s = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	glm::mat4 model = t * r * s;
	glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(model));

	glDrawArrays(GL_TRIANGLES, 0, 3);

	//Second Triangle
	t = glm::translate(glm::mat4(1.0f), glm::vec3(0.5, 0.0, 0.0));
	model = t * r * s;
	glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(model));

	glDrawArrays(GL_TRIANGLES, 0, 3);

	if (speed == 0.001f)
	{
		std::cout << glm::to_string(model) << std::endl;
	}

	checkOpenGLError("render()");
}