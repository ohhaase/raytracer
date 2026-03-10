#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>


void initializeGLFW();

GLFWwindow* initializeWindow(int width, int height);

int initializeGlad();

void processInput(GLFWwindow* window);
