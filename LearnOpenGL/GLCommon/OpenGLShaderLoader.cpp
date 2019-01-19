
#include "GLCommon/OpenGLShaderLoader.h"
#include <fstream>

int OpenGLShaderLoader::LoadShaderFromString(const char* shaderSource, unsigned int shaderType)
{ 
	int shader = glCreateShader(shaderType);
	if (shader == 0)
	{
		std::cout << "ERROR::SHADER::CREATE_SHADER_FAILED!" << std::endl;
		return 0;
	}

	if (shader == GL_INVALID_ENUM)
	{
		std::cout << "ERROR::SHADER::INVALID_SHADER_TYPE!" << std::endl;
		return 0;
	}

	glShaderSource(shader, 1, &shaderSource, nullptr);
	glCompileShader(shader);

	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
		return 0;
	}

	return shader;
} 

int OpenGLShaderLoader::LoadShaderFromFile(const char* shaderPath, unsigned int shaderType)
{
	std::ifstream fin(shaderPath);
	if (!fin)
	{
		std::cout << "ERROR::SHADER::CAN NOT FIND SHADER FILE:\n\t" << shaderPath << std::endl;
		return 0;
	}

	fin.seekg(0, std::ios_base::end);
	int len = (int)fin.tellg();
	fin.seekg(0, std::ios_base::beg);

	if (len < 0)
	{
		std::cout << "ERROR::SHADER:: SHADER FILE IS EMPTY!" << std::endl;
		return 0;
	}

	char* shaderSource = new char[len + 1];
	memset(shaderSource, 0, len + 1);
	fin.read(shaderSource, len);
	
	int shader = LoadShaderFromString(shaderSource, shaderType);

	delete[] shaderSource;
	return shader; 
}

int OpenGLShaderLoader::LinkShaderProgram(std::vector<int> shaders)
{
	if (shaders.size() == 0)
	{
		std::cout << "ERROR::SHADER_PROGRAM::NO USABLE SHADER TO LINK!" << std::endl;
		return 0;
	}

	int shaderProgram = glCreateProgram();
	if (shaderProgram == 0)
	{
		std::cout << "ERROR::SHADER_PROGRAM::CREATE SHADER PROGRAM FAILED!" << std::endl;
		return 0;
	}

	auto i = shaders.begin();
	while (i != shaders.end())
	{
		glAttachShader(shaderProgram, *i);
		++i;
	}

	// Á´½Ó
	glLinkProgram(shaderProgram);

	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n\t" << infoLog << std::endl;
		return 0;
	}

	return shaderProgram;
}

OpenGLShaderLoader::Shader::Shader(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource, bool useFile)
{
	int vertexShader, fragmentShader;

	if (useFile)
	{
		vertexShader = LoadShaderFromFile(vertexShaderSource, GL_VERTEX_SHADER);
		fragmentShader = LoadShaderFromFile(fragmentShaderSource, GL_FRAGMENT_SHADER);
	}
	else
	{
		vertexShader = LoadShaderFromString(vertexShaderSource, GL_VERTEX_SHADER);
		fragmentShader = LoadShaderFromString(fragmentShaderSource, GL_FRAGMENT_SHADER);
	}

	assert(vertexShader != 0);
	assert(fragmentShader != 0);

	std::vector<int> shaders;
	shaders.push_back(vertexShader);
	shaders.push_back(fragmentShader);
	m_shaderProgram = LinkShaderProgram(shaders);

	assert(m_shaderProgram != 0);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

OpenGLShaderLoader::Shader::~Shader()
{

}

void OpenGLShaderLoader::Shader::Use()
{
	glUseProgram(m_shaderProgram); 
}

void OpenGLShaderLoader::Shader::SetBool(const GLchar* name, bool v) const
{
	glUniform1i(glGetUniformLocation(m_shaderProgram, name), (int)v);
} 

void OpenGLShaderLoader::Shader::SetInt(const GLchar* name, int v0) const
{
	glUniform1i(glGetUniformLocation(m_shaderProgram, name), v0); 
}

void OpenGLShaderLoader::Shader::SetInt(const GLchar* name, int v0, int v1) const
{
	glUniform2i(glGetUniformLocation(m_shaderProgram, name), v0, v1);
}

void OpenGLShaderLoader::Shader::SetInt(const GLchar* name, int v0, int v1, int v2) const
{
	glUniform3i(glGetUniformLocation(m_shaderProgram, name), v0, v1, v2);
}

void OpenGLShaderLoader::Shader::SetInt(const GLchar* name, int v0, int v1, int v2, int v3) const
{
	glUniform4i(glGetUniformLocation(m_shaderProgram, name), v0,v1,v2,v3);
}

void OpenGLShaderLoader::Shader::SetFloat(const GLchar* name, float v0) const
{
	glUniform1f(glGetUniformLocation(m_shaderProgram, name), v0);
}

void OpenGLShaderLoader::Shader::SetFloat(const GLchar* name, float v0, float v1) const
{
	glUniform2f(glGetUniformLocation(m_shaderProgram, name), v0, v1);
}

void OpenGLShaderLoader::Shader::SetFloat(const GLchar* name, float v0, float v1, float v2) const
{
	glUniform3f(glGetUniformLocation(m_shaderProgram, name), v0, v1,v2);
}

void OpenGLShaderLoader::Shader::SetFloat(const GLchar* name, float v0, float v1, float v2, float v3) const
{
	glUniform4f(glGetUniformLocation(m_shaderProgram, name), v0, v1, v2,v3);
}


