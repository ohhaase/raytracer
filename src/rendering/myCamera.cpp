#include "myCamera.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>
#include <glm/geometric.hpp>
#include <glm/gtx/string_cast.hpp>
#include <cmath>
#include "globalVars.hpp"
#include <iostream>


myCamera::myCamera(GLFWwindow* inWindow)
{
	window = inWindow;
}


void myCamera::update(float dt)
{
	updateSteps(dt);
	movement();

	horizontal = glm::cross(vertical, cameraDir);

	glm::vec3 unitCamDir = glm::normalize(cameraDir);
	glm::vec3 unitHorizontal = glm::normalize(horizontal);
	glm::vec3 unitVertical = glm::cross(unitCamDir, unitHorizontal);

	horizontalStep = 2.0f * outerPixelHorzDist / (TEXTURE_WIDTH - 1.0f) * unitHorizontal;
	verticalStep = 2.0f * outerPixelVertDist / (TEXTURE_HEIGHT - 1.0f) * unitVertical;

	ray_11 = unitCamDir - outerPixelHorzDist * unitHorizontal + outerPixelVertDist * unitVertical;
}


void rotateVectorZ(glm::vec3& inVec, float theta)
{
	glm::mat3 rotMat = glm::mat3(cos(theta), sin(theta), 0, -sin(theta), cos(theta), 0, 0, 0, 1);

	inVec = rotMat * inVec;
}


void rotateVectorAboutVector(glm::vec3& inVec, glm::vec3 rotVec, float theta)
{
	float cT = cos(theta);
	float cT2 = 1 - cos(theta);
	float sT = sin(theta);
	float x = rotVec.x;
	float y = rotVec.y;
	float z = rotVec.z;

	// https://en.wikipedia.org/wiki/Rotation_matrix#Rotation_matrix_from_axis_and_angle
	glm::mat3 rotMat = glm::mat3(cT + x*x*cT2, x*y*cT2 + z*sT, z*x*cT2 - z*sT, // first column
								 x*y*cT2 - z*sT, cT + y*y*cT2, z*y*cT2 + x*sT, // second column
								 x*z*cT2 + y*sT, y*z*cT2 - x*sT, cT + z*z*cT2); // third column

	inVec = rotMat * inVec;
}


void myCamera::movement()
{

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		linVelocity = 5.0f;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		linVelocity = 1.0f;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		cameraPos += stepSize * cameraDir;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		cameraPos -= stepSize * cameraDir;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		cameraPos -= stepSize * horizontal;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		cameraPos += stepSize * horizontal;
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		cameraPos += stepSize * vertical;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		cameraPos -= stepSize * vertical;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		rotateVectorZ(cameraDir, -angleStep);
	}

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		rotateVectorZ(cameraDir, angleStep);
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		rotateVectorAboutVector(cameraDir, horizontal, -angleStep);
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		rotateVectorAboutVector(cameraDir, horizontal, angleStep);
	}
}


void myCamera::updateSteps(float dt)
{
	stepSize = linVelocity * dt;
	angleStep = angVelocity * dt;
}


void myCamera::printPos()
{
	std::cout << "Position: " << glm::to_string(cameraPos) << "\n";
}