
#ifndef LightCaster_h__
#define LightCaster_h__

#include "GLCommon/OpenGLAPP.h"
#include "GLCommon/OpenGLShaderLoader.h"
#include "GLCommon/OpenGLTexture.h"

class LightCasterApp :public OpenGLApp
{
public:
	LightCasterApp();
	~LightCasterApp();

	bool Init()override;
	void UpdateScene()override;
	void Render()override;
	void ClearnUp()override;

private:
	void BUildVAO();

private:
	GLCommon::Shader* m_shader = 0;     // 着色器程序
	unsigned int m_vao = 0;
	unsigned int m_vbo = 0;

	GLCommon::Texture2D m_diffuseMap;     // 漫反射贴图
	GLCommon::Texture2D m_specularMap;    // 漫反射贴图

	GLCommon::Shader* m_pointLightShader = 0;
	unsigned int m_pointLightVao = 0;

	glm::vec3 m_directionLightDirection = glm::vec3(-0.2f, -1.0f, -0.3f);
	glm::vec3 m_pointLightPosition = glm::vec3(1.2f, 1.0f, 2.0f);
};

/*
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
*/


#endif // LightCaster_h__