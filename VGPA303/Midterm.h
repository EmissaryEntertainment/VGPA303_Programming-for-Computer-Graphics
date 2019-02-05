#pragma once
// Must include functions.h to get opengl functionality
#include "Functions.h";

// variables
GLuint vao;
GLuint vbo;
GLuint vco;
GLuint program;
GLuint program2;
GLuint offsetLocation;

//functions
void Prepare();
void Render(GLuint _render);

// Declare source code for vertex shader.
const char * vs_source[] =
{
	"#version 450 core                                                 \n"
	"layout(location = 0) uniform vec4 offset;                         \n"
	"layout(location = 1) in vec4 color;                               \n"
	"layout(location = 2) in vec4 vPos;                                \n"
	"out vec4 vs_color;                                                \n"
	"void main(void)                                                   \n"
	"{                                                                 \n"
	"    gl_Position = vPos + offset;                                  \n"
	"    vs_color = color;                                             \n"
	"}                                                                 \n"
};

// Declare source code for fragment shader.
const char * fs_source[] =
{
	"#version 450 core                             \n"
	"in vec4 vs_color;                             \n"
	"out vec4 color;                               \n"
	"void main()                                   \n"
	"{                                             \n"
	"    color = vs_color;                         \n"
	"}                                             \n"
};

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

		Render(program);
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
	program = PrepareShaderProgram(vs_source, fs_source);


	//glUseProgram(program);
	//offsetLocation = glGetAttribLocation(program,"offset");

	//create Vertex array object

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Prepare VBO
	// Step 1: Data
	GLfloat positions[] =
	{
		// Bottom square------------------
		-0.5,0.5,0.0,1.0, // Top left
		 0.5,0.5,0.0,1.0,  // Top Right
		 0.5,-0.5,0.0,1.0,  // Bottom right
		 0.5,-0.5,0.0,1.0, // Bottom right
		 -0.5,0.5,0.0,1.0, // Top left
		 -0.5,-0.5,0.0,1.0, // Bottom left
		//--------------------------------
		// Top triangle-------------------
		 0.5,1.3,0.0,1.0, // Top left
		 -0.5,1.3,0.0,1.0,  // Top Right
		 0.0,0.5,0.0,1.0,  // Bottom Tip
		//-------------------------------
		// Right square------------------
		0.2,0.6,0.0,1.0, // Bottom left
		0.3,0.6,0.0,1.0, // Bottom right
		0.3,0.7,0.0,1.0, // Top right
		0.2,0.6,0.0,1.0, // Bottom left
		0.3,0.7,0.0,1.0, // Top right
		0.2,0.7,0.0,1.0, // Top left
		//-------------------------------
		// Left square-------------------
		-0.2,0.6,0.0,1.0, // Bottom right
		-0.3,0.6,0.0,1.0, // Bottom left
		-0.3,0.7,0.0,1.0, // Top left
		-0.2,0.6,0.0,1.0, // Bottom right
		-0.3,0.7,0.0,1.0, // Top left
		-0.2,0.7,0.0,1.0 // Top right
		//-------------------------------
	};
	// Step 2: Generate buffer object
	glGenBuffers(1, &vbo);
	// Step 3: Bind buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// Step 4: Put the data into the buffer object
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	// Step 5: Enable vertex attributes
	glEnableVertexAttribArray(2); // 2 is the location of the accepting variable in the shader program
	// Step 6: Tell OpenGL how to load in the data from VBO
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, 0);

	GLfloat colors[] =
	{
		// Bottom square----------
		1.0,0.0,0.0, // Red
		0.0,1.0,0.0, // Green
		0.0,0.0,1.0, // Blue
		0.0,0.0,1.0, // Blue
		1.0,0.0,0.0, // Red
		0.0,1.0,0.0, // Green
		//------------------------
		// Top triangle-----------
		1.0,0.0,0.0, // Red
		0.0,1.0,0.0, // Green
		0.0,0.0,1.0, // Blue
		//------------------------
		// Right square-----------
		1.0,0.0,0.0, // Red
		0.0,1.0,0.0, // Green
		0.0,0.0,1.0, // Blue
		1.0,0.0,0.0, // Red
		0.0,0.0,1.0, // Blue
		0.0,1.0,0.0, // Green
		//------------------------
		// Left square------------
		1.0,0.0,0.0, // Red
		0.0,1.0,0.0, // Green
		0.0,0.0,1.0, // Blue
		1.0,0.0,0.0, // Red
		0.0,0.0,1.0, // Blue
		0.0,1.0,0.0, // Green
		//------------------------
	};
	glGenBuffers(1, &vco);
	// Step 3: Bind buffer
	glBindBuffer(GL_ARRAY_BUFFER, vco);
	// Step 4: Put the data into the buffer object
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	// Step 5: Enable vertex attributes
	glEnableVertexAttribArray(1); // 2 is the location of the accepting variable in the shader program
	// Step 6: Tell OpenGL how to load in the data from VBO
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(0));
}


void Render(GLuint _program)
{
	// Block below controls background color
	double currentTime = glfwGetTime();
	const GLfloat color[] = { -(float)sin(currentTime) *0.5f + 0.5, -(float)cos(currentTime) *0.5f + 0.5 , 0.7f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, color);

	// Assign the values to "offset"
	glUniform4f(0, 0.0f, -0.5f, 0.0f, 0.0f);
	glUseProgram(program);
	glDrawArrays(GL_TRIANGLES, 0, 21);
}