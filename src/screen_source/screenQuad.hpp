#pragma once

#include "screen_source/shader.hpp"
#include "screen_source/myTexture.hpp"
#include "globalVars.hpp"

class screenQuad
{
public:

	shader ourShader{ "shaders/shader.vert", "shaders/shader.frag" };
	myTexture shaderOutput{ TEXTURE_WIDTH, TEXTURE_HEIGHT, 0 };

	unsigned int VBO, VAO;

	// Rectange vertices
	float vertices[20] = {
		// positions      // texture Coords
		-1.0f,  1.0f, 0.0f, 0.0f, 0.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 1.0f,
	};

	unsigned int indices[6] = {
		0, 1, 3, //first triangle
		1, 2, 3  //second triangle
	};


	// Functions
	screenQuad();

	void draw();
	void clear();
};