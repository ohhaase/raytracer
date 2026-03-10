#include "myTexture.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

myTexture::myTexture(int height, int width, int textureNum)
{
	textureHeight = height;
	textureWidth = width;
	GLtextureNum = textureNum;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, textureWidth, textureHeight, 0, GL_RGBA, GL_FLOAT, NULL);

	glBindImageTexture(0, texture, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA32F);
}


void myTexture::bind()
{
	glActiveTexture(GL_TEXTURE0 + GLtextureNum);
	glBindTexture(GL_TEXTURE_2D, texture);
}