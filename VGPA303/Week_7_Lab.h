#pragma once
#include "Functions.h"
#define GLM_ENABLE_EXPERIMENTAL
#include<glm/glm.hpp>
#include<glm/gtx/string_cast.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/normalize_dot.hpp>
#include<glm/gtc/matrix_transform.hpp>

const char* vs_source[] = {
	"#version 450 core\n"
	"layout(location = 0) in vec4 vPos;"
	"layout(location = 2) in vec3 vColor;"
	"layout(location = 3) uniform mat4 matrix;"
	"out vec4 vsColor; "
	"void main()"
	"{"
	"    gl_Position = vPos * matrix;"
	"    vsColor = vec4(vColor, 1.0);"
	"} "
};

const char* fs_source[] = {
	"#version 450 core \n"
	"in vec4 vsColor;"
	"out vec4 color;"
	"void main()"
	"{"
	"    color =  vsColor; "
	"} "
};

//DATA
GLfloat pos[] = {
	 0.25,  0.25, 0.0, 1.0,      //top right     0
	 0.25, -0.25, 0.0, 1.0,      //bottom right  1
	-0.25, -0.25, 0.0, 1.0      //bottom left   2
};
GLfloat colors[] = {
	1.0, 0.0, 0.0,     //Red
	0.0, 1.0, 0.0,     //Green
	0.0, 0.0, 1.0,     //Blue
};
GLuint indices[] = {
	0,1,2, //first triangle
};

// variables
GLuint vao, program;
GLuint vboPositions, vboColors;
GLuint ebo;
float speed = 0.0f;
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
	//vbo for position
	//Scale and move positions
	prepareVbo(vboPositions, pos, sizeof(pos));
	//activate va array
	connectBufferToAttrib(0, 4, 4, 0);
	//vbo for color
	prepareVbo(vboColors, colors, sizeof(colors));
	connectBufferToAttrib(2, 3, 3, 0);

	//Element buffer object
	prepareEbo(ebo, indices, sizeof(indices));

}

void render()
{
	GLfloat darkbg[] = { 0.0, 0.0, 0.0, 1.0 };
	glClearBufferfv(GL_COLOR, 0, darkbg);

	glUseProgram(program);
	glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.3f, 0.5f, 0.3f));
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 1.0f));
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f));
	glm::mat4 modelMatrix = translateMatrix * rotationMatrix * scaleMatrix;
	glUniformMatrix4fv(3, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid*)0);

	checkOpenGLError("render()");
}