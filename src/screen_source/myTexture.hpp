#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class myTexture
{
public: 
	unsigned int texture;
	int textureWidth;
	int textureHeight;
	int GLtextureNum;

	myTexture(int height, int width, int textureNum);
	void bind();
};