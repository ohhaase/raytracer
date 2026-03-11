#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/mat3x3.hpp>
#include <iostream>
#include "globalVars.hpp"
#include "rendering/myCamera.hpp"
#include "rendering/imageTexture.hpp"
#include "rendering/computeShader.hpp"
#include "screen_source/screenFuncs.hpp"
#include "screen_source/screenQuad.hpp"

#define checkError(a) if (a == NULL) return -1;

int main()
{
	// Initialize GLFW
	initializeGLFW();

	// Initialize window
	GLFWwindow* window = initializeWindow(SCR_WIDTH, SCR_HEIGHT);
	checkError(window);

	// Initialize GLAD
	int result = initializeGlad();
	checkError(result);

	// Make screen
	screenQuad screen;

	// Initialize Shaders
	// computeShader compShader("rayTracingShader.comp");
	computeShader compShader("grRayTracer.comp");

	// Textures
	// imageTexture sphereTexture("amogus.jpg", 1);
	imageTexture sphereTexture("stars2.jpg", 1);
	imageTexture diskTexture("diskTexture.png", 2);

	
	
	// Timing
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	int fCounter = 0;
	float currentFrame;

	
	// Camera stuff
	myCamera camera(window);


	//Disk :)
	float diskAngVel = -1.0;
	float diskAng = 0.0;

	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		// Timing
		currentFrame = float(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		if (fCounter > 500)
		{
			std::cout << "FPS: " << 1 / deltaTime << "\n";
			camera.printPos();
			fCounter = 0;
		}
		else
		{
			fCounter++;
		}


		// Camera stuff
		camera.update(deltaTime);

		// Rendering commands here
		screen.clear();

		sphereTexture.bind();
		diskTexture.bind();

		compShader.use();

		compShader.setVec3("camPos", camera.cameraPos);
		compShader.setVec3("ray_11", camera.ray_11);
		compShader.setVec3("horizontalStep", camera.horizontalStep);
		compShader.setVec3("verticalStep", camera.verticalStep);

		diskAng += diskAngVel * deltaTime;
		diskAng = std::fmod(diskAng, 2 * 3.1415926535897932384626433832795);
		compShader.setFloat("diskAng", diskAng);


		compShader.dispatch();
		
		screen.draw();

		// GLFW stuff
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//Terminate
	glfwTerminate();

	return 0;
}