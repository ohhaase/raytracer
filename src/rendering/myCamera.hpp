#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <cmath>
#include "globalVars.hpp"

class myCamera
{
public:
	GLFWwindow* window;

	glm::vec3 cameraPos = glm::vec3(-10.0f, 0.0f, 0.0f);
	glm::vec3 cameraDir = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 vertical = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 horizontal = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::vec3 ray_11 = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 horizontalStep = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 verticalStep = glm::vec3(0.0f, 0.0f, 0.0f);

	float FOV = 3.141592653f / 3.0f;

	float linVelocity = 1.0f;
	float angVelocity = 1.0f;

	float stepSize = 0.0f;
	float angleStep = 0.0f;

	myCamera(GLFWwindow* inWindow);
	void update(float dt);
	void printPos();

private:
	float outerPixelHorzDist = float(tan(FOV / 2.0f));
	float outerPixelVertDist = outerPixelHorzDist * (TEXTURE_WIDTH - 1.0f) / (TEXTURE_HEIGHT - 1.0f);

	void movement();
	void updateSteps(float dt);
};

