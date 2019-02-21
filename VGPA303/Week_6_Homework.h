#pragma once
// OpenGL Host Program Skeleton
#include "Functions.h"

const char* vs_source[] = {
	"#version 450 core\n"
	"layout(location = 0) in vec4 vPos;"
	"layout(location = 1) uniform vec4 uColor;"
	"out vec4 vsColor; "
	"void main()"
	"{"
	"    gl_Position = vPos;"
	"    vsColor = uColor;"
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
	 0.5,  0.5, 0.0, 1.0,      //top right     0
	 0.5, -0.5, 0.0, 1.0,      //bottom right  1
	-0.5, -0.5, 0.0, 1.0,      //bottom left   2
	-0.5,  0.5, 0.0, 1.0,      //top left      3
	 0.0, 1.0, 0.0, 1.0,       //top middle    4
	-0.25, 0.1, 0.0, 1.0,      //left window   5
	 0.25, 0.1, 0.0, 1.0,      //right window  6
	0.0, -0.40, 0.0, 1.0,      //door          7
	0.0, -0.25, 0.0, 1.0       //door          8
};
GLuint indices[] = {
	0,1,2, //first triangle
	0,2,3, //second triangle
	3,0,4, //roof triangle
	5,     //left window
	6,     //right window
	7,     //door
	8      //door
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
	prepareVbo(vboPositions, pos, sizeof(pos));
	//activate va array
	connectBufferToAttrib(0, 4, 4, 0);
	//Element buffer object
	prepareEbo(ebo, indices, sizeof(indices));

}

void render()
{
	GLfloat darkbg[] = { 0.0, 0.0, 0.0, 1.0 };
	glClearBufferfv(GL_COLOR, 0, darkbg);

	glUseProgram(program);
	glUniform4f(1, 1.0,0.0,0.0,1.0);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)0);
	glUniform4f(1, 0.0,1.0,0.0,1.0);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid*)(6 * sizeof(float)));
	glUniform4f(1, 1.0,1.0,1.0,1.0);
	glPointSize(50);
	glDrawElements(GL_POINTS, 4, GL_UNSIGNED_INT, (GLvoid*)(9*sizeof(float)));
	checkOpenGLError("render()");
}