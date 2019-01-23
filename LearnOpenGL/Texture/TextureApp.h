
#ifndef TextureApp_h__
#define TextureApp_h__

#include "GLCommon/OpenGLAPP.h"
#include "GLCommon/OpenGLShaderLoader.h"
#include "GLCommon/OpenGLTexture.h"

class TextureApp : public OpenGLApp 
{
public:
	TextureApp();
	~TextureApp();

	bool Init()override;
	void OnResize(unsigned int width, unsigned int height)override;
	void ProcessInput()override;
	void UpdateScene()override;
	void Render()override;
	void ClearnUp()override;

private:
	void BUildVAO();

private:
	OpenGLShaderLoader::Shader* m_shader = 0;     // ��ɫ������
	OpenGLImageLoader::Texture2D m_texture01;     // ����1 -- שǽ  
	OpenGLImageLoader::Texture2D m_texture02;     // ����2 -- Ц��

	unsigned int m_vao = 0;
	unsigned int m_vbo = 0;
	unsigned int m_ebo = 0;
};



#endif // TextureApp_h__