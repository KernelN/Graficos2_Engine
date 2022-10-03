#include "Program.h"
#include <glew/include/GL/glew.h>
#include <iostream>
#include <fstream>

Program::Program(ShaderData shaders[], unsigned int arrayLength)
{
	//https://docs.gl/gl4/glCreateProgram
	ID = glCreateProgram();

	//Compile all shaders and attach them to the program
	unsigned int shaderID;
	for (unsigned int i = 0; i < arrayLength; i++)
	{
		shaderID = CreateShader(shaders[i]);

		if (!(shaderID > 0)) continue;

		shadersCompiled.push(shaderID);
	}

	//https://docs.gl/gl4/glLinkProgram
	glLinkProgram(ID);

	//https://docs.gl/gl4/glValidateProgram
	glValidateProgram(ID);

	//ClearShaders();
}

Program::~Program()
{
	//https://docs.gl/gl4/glDeleteProgram
	glDeleteProgram(ID);
}

void Program::Bind() const
{
	//https://docs.gl/gl4/glUseProgram
	glUseProgram(ID);
}

void Program::Unbind() const
{
	//https://docs.gl/gl4/glUseProgram
	glUseProgram(ID);
}

void Program::SetUniform4f(const std::string& varName, float v1, float v2, float v3, float v4)
{
	glUniform4f(GetUniformLocation(varName), v1, v2, v3, v4);
}

void Program::SetUniformMat4f(const std::string& varName,const glm::mat4 & matrix)
{
	
	glUniformMatrix4fv(GetUniformLocation(varName), 1, GL_FALSE, &matrix[0][0]);
}

std::string Program::ReadFile(std::string fileDir)
{
	std::string shaderLine;
	std::string tempShader = "";

	std::ifstream inputStream;
	inputStream.open(fileDir);

	while (getline(inputStream, shaderLine))
	{
		tempShader += shaderLine + '\n';
	}

	inputStream.close();

	return tempShader;
}

unsigned int Program::CreateShader(ShaderData data)
{
	unsigned int shaderID = CompileShader(ReadFile(data.filePath), data.type);
	
	//If compilation failed, don't attach
	if (!(shaderID > 0)) return 0;

	//https://docs.gl/gl4/glAttachShader
	//Attaches a shader to the program
	glAttachShader(ID, shaderID);

	return shaderID;
}

unsigned int Program::CompileShader(const std::string& sourceCode, unsigned int type)
{
	//https://docs.gl/gl4/glCreateShader
	unsigned int id = glCreateShader(type);
	const char* src = sourceCode.c_str();
	glShaderSource(id, 1, &src, nullptr); //https://docs.gl/gl4/glShaderSource
	glCompileShader(id); //https://docs.gl/gl4/glCompileShader

	int result;

	//https://docs.gl/gl4/glGetShaderiv
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		
		char* message = (char*)alloca(length * sizeof(char));


		//https://docs.gl/gl4/glGetShaderInfoLog
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile: " << (type == GL_VERTEX_SHADER ? "vertex " : "fragment") << std::endl;
		std::cout << message << std::endl;

		//https://docs.gl/gl4/glDeleteShader
		glDeleteShader(id);

		return 0;
	}

	return id;
}

void Program::ClearAllShaders()
{
	while (!shadersCompiled.empty())
	{
		//https://docs.gl/gl4/glDeleteShader
		glDeleteShader(shadersCompiled.top());
		shadersCompiled.pop();
	}
}

int Program::GetUniformLocation(const std::string& varName)
{
	int location;

	//https://docs.gl/gl4/glGetUniformLocation
	//Returns the location of a uniform variable, returns -1 if any error happens
	location = glGetUniformLocation(ID, varName.c_str());

	if (location == -1)
	{
		std::cout << 
			"ERROR: Uniform Variable" + varName + " wasn't available / doesn't exist" 
			<< std::endl;
	}

	return location;
}
