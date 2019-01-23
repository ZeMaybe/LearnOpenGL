
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
	OpenGLShaderLoader::Shader* m_shader = 0;     // 着色器程序
	OpenGLImageLoader::Texture2D m_texture01;     // 纹理1 -- 砖墙  
	OpenGLImageLoader::Texture2D m_texture02;     // 纹理2 -- 笑脸

	unsigned int m_vao = 0;
	unsigned int m_vbo = 0;
	unsigned int m_ebo = 0;
};



#endif // TextureApp_h__