#include "computeShader.hpp"

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "globalVars.hpp"

computeShader::computeShader(const std::string filePath)
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string computeCode;
	std::ifstream cShaderFile;

	// ensure ifstream objects can throw exceptions:
	cShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		cShaderFile.open(std::string(ASSET_DIR) + "shaders/" + filePath);
		std::stringstream cShaderStream;
		// read file's buffer contents into streams
		cShaderStream << cShaderFile.rdbuf();
		// close file handlers
		cShaderFile.close();
		// convert stream into string
		computeCode = cShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::COMPUTE_SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* cShaderCode = computeCode.c_str();


	//2. Compile shader
	unsigned int compute;
	int success;
	char infoLog[512];

	compute = glCreateShader(GL_COMPUTE_SHADER);
	glShaderSource(compute, 1, &cShaderCode, NULL);
	glCompileShader(compute);

	//Check for errors from the compilation
	glGetShaderiv(compute, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(compute, 512, NULL, infoLog);
		std::cout << "ERROR::COMPUTE_SHADER::COMPILATION_FAILED\n" << infoLog << "\n";
	}

	// Shader program
	ID = glCreateProgram();
	glAttachShader(ID, compute);
	glLinkProgram(ID);

	//Check for errors from the shader program
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::COMPUTE_SHADER::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// Delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(compute);
}


void computeShader::use()
{
	glUseProgram(ID);
}


void computeShader::dispatch()
{
	glDispatchCompute((unsigned int)TEXTURE_WIDTH / 10, (unsigned int)TEXTURE_HEIGHT / 10, 1);

	// Make sure writing to image has finished before reading
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}

void computeShader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}


void computeShader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}


void computeShader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}


void computeShader::setVec3(const std::string& name, glm::vec3 inVec) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), inVec[0], inVec[1], inVec[2]);
}


void computeShader::setVec2i(const std::string& name, glm::ivec2 inVec) const
{
	glUniform2i(glGetUniformLocation(ID, name.c_str()), inVec[0], inVec[1]);
}