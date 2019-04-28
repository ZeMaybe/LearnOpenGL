
#ifndef LightApp_h__
#define LightApp_h__

#include "GLCommon/OpenGLAPP.h"
#include "GLCommon/OpenGLShaderLoader.h"
#include "GLCommon/OpenGLTexture.h"

class LightingMapsApp : public OpenGLApp
{
public:
	LightingMapsApp();
	~LightingMapsApp();

	bool Init()override;
	void UpdateScene()override;
	void Render()override;
	void ClearnUp()override;

private:
	void BUildVAO();

private:
	OpenGLShaderLoader::Shader* m_shader = 0;     // 着色器程序
	unsigned int m_vao = 0;
	unsigned int m_vbo = 0;

	OpenGLImageLoader::Texture2D m_diffuseMap;     // 漫反射贴图
	OpenGLImageLoader::Texture2D m_specularMap;     // 漫反射贴图
	
	OpenGLShaderLoader::Shader* m_lightShader = 0;
	unsigned int m_lightVao = 0;

	glm::vec3 m_lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
};
#endif // LightApp_h__