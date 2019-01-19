
#ifndef OpenGLShaderLoader_h__
#define OpenGLShaderLoader_h__

#include "GLCommon/OpenGLUtility.h"
#include <vector>

namespace OpenGLShaderLoader
{
	// 从字符串编译shader
	int LoadShaderFromString(const char* shaderSource,unsigned int shaderType);

	// 从文件编译shader
	int LoadShaderFromFile(const char* shaderPath, unsigned int shaderType);

	// 链接shader程序
	int LinkShaderProgram(std::vector<int> shaders); 
}; 
#endif // OpenGLShaderLoader_h__