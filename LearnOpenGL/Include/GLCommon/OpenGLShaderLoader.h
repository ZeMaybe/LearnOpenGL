
#ifndef OpenGLShaderLoader_h__
#define OpenGLShaderLoader_h__

#include "GLCommon/OpenGLUtility.h"
#include <vector>

namespace OpenGLShaderLoader
{
	// ���ַ�������shader
	int LoadShaderFromString(const char* shaderSource,unsigned int shaderType);

	// ���ļ�����shader
	int LoadShaderFromFile(const char* shaderPath, unsigned int shaderType);

	// ����shader����
	int LinkShaderProgram(std::vector<int> shaders); 
}; 
#endif // OpenGLShaderLoader_h__