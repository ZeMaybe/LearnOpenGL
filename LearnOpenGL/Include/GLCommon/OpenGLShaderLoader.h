
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


	class Shader
	{
	public:
		Shader(const GLchar* vertexShaderSource,const GLchar* fragmentShaderSource,bool useFile = true);
		~Shader();

		void Use(); 

		void SetBool(const GLchar* name, bool v)const;
		void SetFloat(const GLchar* name, float v0)const;
		void SetFloat(const GLchar* name, float v0,float v1)const;
		void SetFloat(const GLchar* name, float v0,float v1,float v2)const;
		void SetFloat(const GLchar* name, float v0,float v1,float v2,float v3)const;
		void SetInt(const GLchar* name, int v0)const;
		void SetInt(const GLchar* name, int v0,int v1)const;
		void SetInt(const GLchar* name, int v0,int v1,int v2)const;
		void SetInt(const GLchar* name, int v0,int v1,int v2,int v3)const;

	private:
		int m_shaderProgram = 0; 
	};

}; 
#endif // OpenGLShaderLoader_h__