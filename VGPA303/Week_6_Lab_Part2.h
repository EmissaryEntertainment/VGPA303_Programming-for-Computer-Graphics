#pragma once
// OpenGL Host Program Skeleton
#include "Functions.h"

const char* vs_source[] = {
	"#version 450 core\n"
	"layout(location = 0) in vec4 vPos;"
	"layout(location = 2) in vec3 vColor;"
	"out vec4 vsColor; "
	"void main()"
	"{"
	"    gl_Position = vPos;"
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
	 0.0,  0.75, 0.0, 1.0,      //top middle     0
	 0.0, -0.75, 0.0, 1.0,      //bottom middle  1
	-0.75,  0.0, 0.0, 1.0,      //right side     2
	 0.75,  0.0, 0.0, 1.0       //left side      3
};
GLfloat colors[] = {
	1.0, 0.0, 0.0,    //Red
	0.0, 1.0, 0.0,    //Green
	1.0, 1.0, 1.0,    //White
	0.0, 0.0, 1.0     //Blue
};
GLuint indices[] = {
	0,1,2, //first triangle
	0,1,3 //second triangle
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

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)0);

	checkOpenGLError("render()");
}