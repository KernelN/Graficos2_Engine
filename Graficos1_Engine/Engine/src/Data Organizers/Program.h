#pragma once
#include <string>
#include <stack>
#include <glm/glm.hpp>

struct ShaderData
{
	const std::string& filePath;
	unsigned int type;
};

class Program
{
public:
	Program(ShaderData shaders[], unsigned int arrayLength);
	~Program();
	void Bind() const;
	void Unbind() const;
	void SetUniform4f(const std::string& varName, float v1, float v2, float v3, float v4);
	void SetUniformMat4f(const std::string& varName, const glm::mat4& matrix);
private:
	unsigned int ID;
	std::stack<unsigned int> shadersCompiled;

	//Reads a File and returns it's contents
	std::string ReadFile(std::string fileDir);
	//Creates a Shader, attaches it to the program and returns it's id
	unsigned int CreateShader(ShaderData data);
	//Compiles Shader and returns it's id
	unsigned int CompileShader(const std::string& sourceCode, unsigned int type);
	//Clears all compiled and attached shaders from memory
	void ClearAllShaders();
	//Returns OpenGL Uniform locations
	int GetUniformLocation(const std::string& varName);
};