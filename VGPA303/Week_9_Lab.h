#pragma once
/*
	Adapted from MovingTriangle.cpp
	Comment out #define GLEW_STATIC when using package.
*/
#define GLEW_STATIC
#include<iostream>

#include<GL/glew.h>
#include <GLFW/glfw3.h>

// Include GLM
#define GLM_ENABLE_EXPERIMENTAL
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/string_cast.hpp>
#include<glm/gtc/type_ptr.hpp>

#include<debug.h>
#include "functions.h"

//shader source
const char* vs_source[] = {
	"#version 450 core \n"
	"layout(location = 0) in vec3 vPos; "
	"layout(location = 1) in vec3 vNormal;"
	//"layout(location = 1) in vec3 vColor;"
	//"out vec3 color;"
	"layout(location = 0) uniform mat4 model; "
	"layout(location = 3) uniform mat4 view; "
	"layout(location = 4) uniform mat4 projection; "
	"out vec3 wPos;"
	"out vec3 normal;"
	"void main() { "
	"	 gl_Position = projection * view * model * vec4(vPos, 1.0); "
	"	wPos = vec3(model * vec4(vPos,1.0));"
	"	normal = vec3(transpose(inverse(model)) * vec4(vNormal, 0.0));"
	//"	 color = vColor; "
	"} "
};

const char* fs_source[] = {
	"#version 450 core \n"
	"in vec3 normal;"
	"in vec3 wPos;"
	"out vec4 fragmentColor;"
	"layout(location = 1) uniform vec3 cubeColor;"
	"layout(location = 2) uniform vec3 lightColor;"
	"layout(location = 5) uniform vec3 lightPos;"
	"layout(location = 6) uniform vec3 eyePos;"
	"void main() { "
	"float ambientFactor = 0.2;"
	"	vec3 ambientAmount = ambientFactor * lightColor;"
	//make sure normal vector is normalized
	"	vec3 norm = normalize(normal);"
	//calculate light direction
	"	vec3 lightDirection = normalize(lightPos - wPos);"
	//calculate diffuse amount => cos Theta
	"	float diffuseFactor = max(dot(norm, lightDirection),0.0);"
	"	vec3 diffuseAmount = diffuseFactor * lightColor;"
	//calculate the specular
	"	float specularFactor = 1.0f;"
	//view direction vector
	"	vec3 viewDirection = normalize(eyePos - wPos);"
	//reflection direction
	"	vec3 reflectionDirection = reflect(-lightDirection, normal);"
	//-lightDirection returns the direction from the wPos to the light
	"	float brightFactor = pow(max(dot(viewDirection, reflectionDirection), 0.0), 32);"
	"	vec3 specularAmount = specularFactor * brightFactor * lightColor;"
	"	vec3 result = (ambientAmount + diffuseAmount + specularAmount) * cubeColor;"
	"	fragmentColor = vec4(result, 1.0);"
	"} "
};

//DATA
GLfloat positions[] = {
	//back  red
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	//front  green
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,
	//left  blue
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	//right  white
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 //bottom  cyan
	 -1.0f, -1.0f, -1.0f,
	  1.0f, -1.0f, -1.0f,
	  1.0f, -1.0f,  1.0f,
	  1.0f, -1.0f,  1.0f,
	 -1.0f, -1.0f,  1.0f,
	 -1.0f, -1.0f, -1.0f,
	 //top  yellow
	 -1.0f,  1.0f, -1.0f,
	  1.0f,  1.0f, -1.0f,
	  1.0f,  1.0f,  1.0f,
	  1.0f,  1.0f,  1.0f,
	 -1.0f,  1.0f,  1.0f,
	 -1.0f,  1.0f, -1.0f,
};
GLfloat colors[] = {
	//red
	1.0f, 0.0, 0.0,
	1.0f, 0.0, 0.0,
	1.0f, 0.0, 0.0,
	1.0f, 0.0, 0.0,
	1.0f, 0.0, 0.0,
	1.0f, 0.0, 0.0,
	//green
	0.0f, 1.0f, 0.0,
	0.0f, 1.0f, 0.0,
	0.0f, 1.0f, 0.0,
	0.0f, 1.0f, 0.0,
	0.0f, 1.0f, 0.0,
	0.0f, 1.0f, 0.0,
	//blue
	0.0f, 0.0f, 1.0,
	0.0f, 0.0f, 1.0,
	0.0f, 0.0f, 1.0,
	0.0f, 0.0f, 1.0,
	0.0f, 0.0f, 1.0,
	0.0f, 0.0f, 1.0,
	//white
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	//light blue
	0.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f,
	//yellow
	1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
};
GLfloat normals[] ={ //normal information
	  0.0f,  0.0f, -1.0f,
	  0.0f,  0.0f, -1.0f,
	  0.0f,  0.0f, -1.0f,
	  0.0f,  0.0f, -1.0f,
	  0.0f,  0.0f, -1.0f,
	  0.0f,  0.0f, -1.0f,

	  0.0f,  0.0f,  1.0f,
	  0.0f,  0.0f,  1.0f,
	  0.0f,  0.0f,  1.0f,
	  0.0f,  0.0f,  1.0f,
	  0.0f,  0.0f,  1.0f,
	  0.0f,  0.0f,  1.0f,

	 -1.0f,  0.0f,  0.0f,
	 -1.0f,  0.0f,  0.0f,
	 -1.0f,  0.0f,  0.0f,
	 -1.0f,  0.0f,  0.0f,
	 -1.0f,  0.0f,  0.0f,
	 -1.0f,  0.0f,  0.0f,

	  1.0f,  0.0f,  0.0f,
	  1.0f,  0.0f,  0.0f,
	  1.0f,  0.0f,  0.0f,
	  1.0f,  0.0f,  0.0f,
	  1.0f,  0.0f,  0.0f,
	  1.0f,  0.0f,  0.0f,

	  0.0f, -1.0f,  0.0f,
	  0.0f, -1.0f,  0.0f,
	  0.0f, -1.0f,  0.0f,
	  0.0f, -1.0f,  0.0f,
	  0.0f, -1.0f,  0.0f,
	  0.0f, -1.0f,  0.0f,

	  0.0f,  1.0f,  0.0f,
	  0.0f,  1.0f,  0.0f,
	  0.0f,  1.0f,  0.0f,
	  0.0f,  1.0f,  0.0f,
	  0.0f,  1.0f,  0.0f,
	  0.0f,  1.0f,  0.0f
};

//variables
GLuint vao;
GLuint vbo, cbo;
GLuint nbo;
GLuint program;

float speed = 0.0f;
//functions
void prepare(); //everything that we need to prepare before rendering
void render(); //called in loop to present graphics

int Run()
{
	/* Initialize the library GLFW */
	if (!glfwInit())
		return -1;
	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window = glfwCreateWindow(640, 480, "3D Lighting", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
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
	//Eable depth test
	glEnable(GL_DEPTH_TEST);
	//vao
	prepareVao(vao);
	program = PrepareShaderProgram(vs_source, fs_source);

	prepareVbo(vbo, positions, sizeof(positions));
	connectBufferToAttrib(0, 3, 3, 0);
	prepareVbo(nbo, normals, sizeof(normals));
	connectBufferToAttrib(1, 3, 3, 0);


	checkOpenGLError("Prepare()");
}

void render()
{
	speed += 0.6f;
	GLfloat darkbg[] = { 0.0, 0.0, 0.0, 1.0 };
	glClearBufferfv(GL_COLOR, 0, darkbg);

	//Clear the screen
	glClear(GL_DEPTH_BUFFER_BIT);

	glUseProgram(program);
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	glm::vec3 eyePos = glm::vec3(3, 3, 3);
	glm::mat4 View = glm::lookAt(
		eyePos, // Camera is at (3,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up
	);
	glm::mat4 translateMx = glm::mat4(1.0f);
	glm::mat4 rotateMxX = glm::rotate(glm::mat4(1.0f), glm::radians(speed), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotateMxY = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rotateMxZ = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 rotateMx = rotateMxZ * rotateMxY * rotateMxX;

	glm::mat4 scaleMx = glm::mat4(1.0f);
	glm::mat4 Model = translateMx * rotateMx * scaleMx;
	glm::mat4 mvp = Projection * View * Model;
	glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(Model));
	glUniformMatrix4fv(3, 1, GL_FALSE, glm::value_ptr(View));
	glUniformMatrix4fv(4, 1, GL_FALSE, glm::value_ptr(Projection));

	//cubeColor
	glm::vec3 cColor = glm::vec3(1.0f, 0.5f, 0.3f);
	glUniform3fv(1, 1, glm::value_ptr(cColor));

	//lightColor
	glm::vec3 lColor = glm::vec3(0.0f, 1.0f, 0.0f);
	glUniform3fv(2, 1, glm::value_ptr(lColor));

	//lightPos
	glm::vec3 lPos = glm::vec3(-1.0f, 0.0f, 2.0f);
	glUniform3fv(5, 1, glm::value_ptr(lPos));

	//eyePos
	glUniform3fv(6, 1, glm::value_ptr(eyePos));

	glDrawArrays(GL_TRIANGLES, 0, 6 * 2 * 3);

	checkOpenGLError("Render()");
}