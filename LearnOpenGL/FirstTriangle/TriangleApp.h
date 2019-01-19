
#ifndef TriangleApp_h__
#define TriangleApp_h__

#include "GLCommon/OpenGLAPP.h"
#include "GLCommon/OpenGLShaderLoader.h"

class TriangleApp : public OpenGLApp
{
public:
	TriangleApp();
	~TriangleApp();

	bool Init()override;
	void OnResize(unsigned int width, unsigned int height)override;
	void ProcessInput()override;
	void UpdateScene()override;
	void Render()override;
	void ClearnUp()override;
private:
	void BUildVAO();

	//int m_shaderProgram = 0;
	OpenGLShaderLoader::Shader* m_shader = 0;
	unsigned int m_vao = 0;
	unsigned int m_vbo = 0;
	unsigned int m_ebo = 0;
};

#endif // TriangleApp_h__