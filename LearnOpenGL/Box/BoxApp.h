
#ifndef BoxApp_h__
#define BoxApp_h__

#include "GLCommon/OpenGLAPP.h"
#include "GLCommon/OpenGLShaderLoader.h"
#include "GLCommon/OpenGLTexture.h"

class BoxApp : public OpenGLApp
{
public:
	BoxApp();
	~BoxApp();

	bool Init()override;
	void OnResize(unsigned int width, unsigned int height)override;
	void ProcessInput()override;
	void UpdateScene()override;
	void Render()override;
	void ClearnUp()override;

private:
	void BUildVAO();

private:
	GLCommon::Shader* m_shader = 0;     // 着色器程序
	GLCommon::Texture2D m_texture01;     // 纹理1 -- 砖墙  
	GLCommon::Texture2D m_texture02;     // 纹理2 -- 笑脸

	unsigned int m_vao = 0;
	unsigned int m_vbo = 0;
	//unsigned int m_ebo = 0;
};

#endif // BoxApp_h__