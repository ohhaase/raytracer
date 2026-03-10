#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class computeShader
{
public:
	// program ID
	unsigned int ID;

	// constructor reads and builds the shader
	computeShader(const char* filePath);

	// use/activate the shader
	void use();

	// Dispatch shader
	void dispatch();

	// utility uniform functions
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec3(const std::string& name, glm::vec3 inVec) const;
	void setVec2i(const std::string& name, glm::ivec2 inVec) const;
};



