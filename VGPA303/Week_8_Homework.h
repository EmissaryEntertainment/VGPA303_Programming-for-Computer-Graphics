#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include<iostream>
#include<glm/glm.hpp>
#include<glm/gtx/string_cast.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/normalize_dot.hpp>
#include<glm/gtc/matrix_transform.hpp>

glm::vec4 points[] = {
	 {0.25,  0.25, 0.0, 1.0},      //top right     0
	 {0.25, -0.25, 0.0, 1.0},      //bottom right  1
	 {-0.25, -0.25, 0.0, 1.0}      //bottom left   2
};

int main()
{
	glm::mat4 translateMatrix = glm::mat4(1.0f);
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	std::cout << "Translation matrix: " << glm::to_string(translateMatrix) << "\nRotation matrix: " << glm::to_string(rotationMatrix) << "\nScale matrix: " << glm::to_string(rotationMatrix) << std::endl;
	glm::mat4 modelMatrix = translateMatrix * rotationMatrix * scaleMatrix;
	std::cout << "Model matrix: " << glm::to_string(modelMatrix) << std::endl;

	for (int i = 0; i < points->length(); i++)
	{
		std::cout << "Rotated triangle point " << i + 1 << ": " << glm::to_string(points[i] * modelMatrix) << std::endl;
	}


	system("pause");
	return 0;
}