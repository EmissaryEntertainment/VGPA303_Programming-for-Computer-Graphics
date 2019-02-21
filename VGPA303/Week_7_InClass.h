#pragma once
// Week 7 for GLM
#define GLM_ENABLE_EXPERIMENTAL
#include<iostream>
#include<glm/glm.hpp>
#include<glm/gtx/string_cast.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/normalize_dot.hpp>
#include<glm/gtc/matrix_transform.hpp>

int Run()
{
	std::cout << "------------ VECTOR ------------\n" << std::endl;
	//VECTOR
	//constructor
	glm::vec2 testVec2(3.0f,4.0f);
	std::cout << glm::to_string(testVec2) << std::endl;

	glm::vec3 testVec3(1.0f, 2.0f,3.0f);
	std::cout << glm::to_string(testVec3) << std::endl;

	float data[] = { 1,2,3,4 };
	glm::vec4 testVec4 = glm::make_vec4(data);
	std::cout << glm::to_string(testVec4) << std::endl;

	std::cout << "The length of the Vec(1,2,3) is: " << sqrt(testVec3.x*testVec3.x + testVec3.y*testVec3.y + testVec3.z*testVec3.z) << std::endl;

	std::cout << "glm::length() returns: " << glm::length(testVec3) << std::endl;

	std::cout <<"Vec3 * 0.5 = " << glm::to_string(testVec3 * 0.5f) << std::endl;

	std::cout << "The unit vector is: " << glm::to_string(testVec2 / glm::length(testVec2)) << std::endl;

	std::cout << "glm::normalize() for Vec3 returns: " << glm::to_string(glm::normalize(testVec3)) << std::endl;

	glm::vec3 v(1, 2, 3), k(4, 5, 6);
	std::cout << "glm add() for v and k returns: " << glm::to_string(v + k) << std::endl;

	std::cout << "glm::normalizeDot() of v and k returns: " << glm::normalizeDot(v, k) << std::endl;

	std::cout <<"glm::dot(v,k) returns: "<< glm::dot(v, k) << std::endl;

	glm::mat4 identityMatrix(1.0f);
	std::cout << glm::to_string(identityMatrix) << std::endl;
	/*
	((1.000000, 0.000000, 0.000000, 0.000000), 
	(0.000000, 1.000000, 0.000000, 0.000000), 
	(0.000000, 0.000000, 1.000000, 0.000000), 
	(0.000000, 0.000000, 0.000000, 1.000000))
	*/

	float data2[] = { 1,2,3,4 };
	glm::mat2 matrix2x2 = glm::make_mat2(data2);
	std::cout << glm::to_string(matrix2x2) << std::endl;

	std::cout << "\n------------ TRANSLATION ------------\n" << std::endl;
	//CONSTRUCTING A TRANSLATION MATRIX

	//Move a point 1 unit on x-axis, 2 on y-axis, and 3 on z-axis
	glm::vec4 point(1, 0, 0, 1.0f);

	glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 2.0f, 3.0f));
	glm::vec3 translatedPoint = translateMatrix * point;
	std::cout<<"Translated point: " << glm::to_string(translatedPoint) << std::endl;

	//scale the point by 2 on x-axis, 2 on y-axis, and 2 on z-axis
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f));
	glm::vec4 scaledPoint = scaleMatrix * point;
	std::cout<<"Scaled point: " << glm::to_string(scaledPoint) << std::endl;

	//Rotate the point 90 degrees around z-axis
	glm::mat4 rotationMatrixZ = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f,0.0f,1.0f));
	glm::vec4 rotatedPoint = rotationMatrixZ * point;
	std::cout << "Rotated point: " << glm::to_string(rotatedPoint) << std::endl;

	system("pause");
	return 0;`
}