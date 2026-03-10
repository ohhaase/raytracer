#include "imageTexture.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#pragma warning(push, 0) // suppress warnings from this library?
#include "stb_image/stb_image.h"
#pragma warning(pop)

imageTexture::imageTexture(const char* fileName, int textureNum)
{
	GLtextureNum = textureNum;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(fileName, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture: " << stbi_failure_reason() << std::endl;
	}

	textureHeight = height;
	textureWidth = width;
}


void imageTexture::bind()
{
	glActiveTexture(GL_TEXTURE0 + GLtextureNum);
	glBindTexture(GL_TEXTURE_2D, texture);
}
