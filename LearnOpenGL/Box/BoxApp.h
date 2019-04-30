
#ifndef BoxApp_h__
#define BoxApp_h__

#include "GLCommon/OpenGLAPP.h"
#include "GLCommon/OpenGLShaderLoader.h"
#include "GLCommon/OpenGLTexture.h"
#include "GLCommon/Model.h"

class BoxApp : public OpenGLApp
{
public:
	BoxApp();
	~BoxApp();

	bool Init()override;
	void UpdateScene()override;
	void Render()override;
	void ClearnUp()override;

private:
	void BUildVAO();

private:
	GLCommon::Shader* m_shader = 0;     // ��ɫ������
	GLCommon::Texture2D m_texture01;     // ����1 -- שǽ  
	GLCommon::Texture2D m_texture02;     // ����2 -- Ц��

	unsigned int m_vao = 0;
	unsigned int m_vbo = 0;
};

#endif // BoxApp_h__