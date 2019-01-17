#pragma once
/*************************
Answer the question:

1. (10 pts) List all stages of the OpenGL pipeline
	Vertex Fetch->Vertex Shader->Tessellation Control Shader->Tessellation->Tessellation Evaluation Shader->
	Geometry Shader->Rasterization->Fragment Shader->Framebuffer Operations

2. (10 pts) What stages are fixed function?
	Vertex Fetch, Tessellation, Rasterization, Framebuffer Operations

3. (10 pts) What stages are programmable?
	Vertex Shader, Tessellation Control Shader, Tessellation Evaluation Shader, Geometry Shader, Fragment Shader

4. (10 pts) Summarize the steps you need to take to create an OpenGL context
	First you must link all libraries needed for openGL such as GLEW and GLFW.
	Then you create a reference to the GLFwindow class in order to call functions from it.
	You must then create a window specifying its size and name.
	Once you have created the window then you can modify its contents.

5. (10 pts) Make the following code work
	DONE

6. (10 pts) What is your OpenGL version on your computer? How did you find the information?
	OpenGL Version: 4.6.0 NVIDIA 399.24, found using glGetString(GL_VERSION)

7. (10 pts) what is your GLSL version on your computer? How did you find the information?
	GLSL Version: 4.60 NVIDIA, found using glGetString(GL_SHADING_LANGUAGE_VERSION)

8. Specify the function API
	a. (10 pts) glfwCreateWindow();
	Creates a window with specified X and Y sizes, and name.

	b. (10 pts)	glClear();
	Clear buffers to preset values, or value input in the parameters section

	c. (10 pts)	glfwSwapBuffers();
	Swaps the front and back buffers of the specified window.

**************************/

//THE FOLLOWING CODE IS FOR WEEK 1  OUT OF CLASS HOMEWORK.

#define GLEW_STATIC

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int Week1Homework(void)
{
	GLFWwindow* window;
	if (!glfwInit())
		return -1;
	window = glfwCreateWindow(200, 200, "Homework 01", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW Failed\n";
		glfwTerminate();
		system("pause");
		return -1;
	}

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	system("pause");
	glfwTerminate();
	return 0;
}