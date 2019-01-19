
#ifndef TriangleApp_h__
#define TriangleApp_h__

#include "GLCommon/OpenGLAPP.h"

class TriangleApp : public OpenGLApp
{
public:
	TriangleApp();
	~TriangleApp();

	bool Init()override;
	void OnResize(unsigned int width, unsigned int height)override;
	void ProcessInput()override;
	void Render()override;
	void ClearnUp()override;
private:
	void LoadShader();
	void BUildVAO();

	int m_shaderProgram = 0;
	unsigned int m_vao = 0;
	unsigned int m_vbo = 0;
	unsigned int m_ebo = 0;
};

#endif // TriangleApp_h__