#pragma once
#define GLEW_STATIC
#include< iostream>
#include< GL/glew.h>
#include < GLFW/glfw3.h>

#include< glm/glm.hpp>
#include< glm/gtc/matrix_transform.hpp>
#include< glm/gtc/type_ptr.hpp>

#include< debug.h>
#include "Functions.h"

//Shader source
const char* vs_source[] = {
	"#version 460 core\n"
	"layout(location = 0) in vec3 vPos; "
	"layout(location = 1) in vec3 vColor; "
	"layout(location = 0) uniform mat4 MVP;"
	"out vec4 color; "
	"void main() { "
	"    gl_Position = MVP * vec4(vPos, 1.0);"
	"    color = vec4(vColor, 1.0); "
	"}"
};

const char* fs_source[] = {
	"#version 460 core \n "
	"in vec4 color; "
	"out vec4 fragColor; "
	"void main() {"
	"    fragColor = color; "
	"} "
};
//DATA
GLfloat positions[] = {
	//front
	 1, -1,  1,        //0
	 1,  1,  1,        //1
	-1,  1,  1,        //2
	-1, -1,  1,        //3
	//back
	 1, -1, -1,        //4
	 1,  1, -1,        //5
	-1,  1, -1,        //6
	-1, -1, -1         //7
};
GLfloat colors[] = {
	1,0,0,
	0,1,0,
	0,0,1,
	1,1,1,

	1,0,0,
	0,1,0,
	0,0,1,
	1,1,1,
};
GLuint indices[] = {
	0,1,2,0,2,3, //front
	7,6,5,7,5,4, //back
	3,2,6,3,6,7, //left
	4,5,1,4,1,0, //right
	1,5,6,1,6,2, //top
	4,0,3,4,3,7 }; //bottom
//variables
GLuint vao, program;
GLuint vbo, cbo;
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
	window = glfwCreateWindow(640, 480, "3D Cube", NULL, NULL);
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
	glEnable(GL_DEPTH_TEST);
	//vao
	prepareVao(vao);
	//program
	program = PrepareShaderProgram(vs_source, fs_source);
	//vbo
	//prepare
	prepareVbo(vbo, positions, sizeof(positions));
	//connect
	connectBufferToAttrib(0, 3, 3, 0);
	prepareVbo(cbo, colors, sizeof(colors));
	connectBufferToAttrib(1, 3, 3, 0);
	//ebo
	//prepare
	prepareEbo(ebo, indices, sizeof(indices));

	checkOpenGLError("prepare()");

}

void render()
{

	speed += 0.001f;
	GLfloat darkbg[] = { 0.0, 0.0, 0.0, 1.0 };
	glClearBufferfv(GL_COLOR, 0, darkbg);
	glClear(GL_DEPTH_BUFFER_BIT);

	//Use the shader program we prepare
	glUseProgram(program);
	//provide uniform values
	//model: do nothing
	glm::mat4 t = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));
	glm::mat4 r = glm::rotate(glm::mat4(1.0f), glm::radians(speed * 1000), glm::vec3(1.0f, 1.0f, 1.0f));
	glm::mat4 s = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	glm::mat4 model = t * r*s;
	//view matrix
	glm::mat4 view = glm::lookAt(
		//camera is at (4, 3, 3) in world space
		glm::vec3(4, 3, 3),
		//where the camera is pointing at
		glm::vec3(0, 0, 0),
		//camera is looking up
		glm::vec3(0, 1, 0)
	);
	//project matrix
	glm::mat4 project = glm::perspective(
		//fov
		glm::radians(45.0f),
		//window ratio
		4.0f/3.0f,
		//near-field
		0.1f,
		//far-field
		100.0f
	);

	//combine them
	glm::mat4 mvp = project * view * model; // order matters!
	glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(mvp));
	//Draw
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLvoid*)0);

	t = glm::translate(glm::mat4(1.0f), glm::vec3(2.0, 0.0, 0.0));
	r = glm::rotate(glm::mat4(1.0f), glm::radians(-speed * 1000), glm::vec3(0.0f, 1.0f, 0.0f));
	model = t * r * s;
	mvp = project * view * model; // order matters!
	glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(mvp));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLvoid*)0);

	t = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0, 0.0, 0.0));
	r = glm::rotate(glm::mat4(1.0f), glm::radians(speed * 1000), glm::vec3(0.0f, 1.0f, 0.0f));
	model = t * r * s;
	mvp = project * view * model; // order matters!
	glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(mvp));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLvoid*)0);

	t = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 2.0));
	r = glm::rotate(glm::mat4(1.0f), glm::radians(-speed * 1000), glm::vec3(0.0f, 1.0f, 0.0f));
	model = t * r * s;
	mvp = project * view * model; // order matters!
	glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(mvp));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLvoid*)0);

	t = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -2.0));
	r = glm::rotate(glm::mat4(1.0f), glm::radians(speed * 1000), glm::vec3(0.0f, 1.0f, 0.0f));
	model = t * r * s;
	mvp = project * view * model; // order matters!
	glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(mvp));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLvoid*)0);

	checkOpenGLError("render()");
}
