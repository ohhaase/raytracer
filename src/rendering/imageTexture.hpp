#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class imageTexture
{
public:
	unsigned int texture;
	int textureWidth;
	int textureHeight;
	int GLtextureNum;

	imageTexture(const std::string fileName, int textureNum);
	void bind();
};

