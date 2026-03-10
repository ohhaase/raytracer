#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class imageTexture
{
public:
	unsigned int texture;
	int textureWidth;
	int textureHeight;
	int GLtextureNum;

	imageTexture(const char* fileName, int textureNum);
	void bind();
};

