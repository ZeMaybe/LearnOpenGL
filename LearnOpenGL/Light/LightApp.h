
#ifndef LightingMapsApp_h__
#define LightingMapsApp_h__

#include "GLCommon/OpenGLAPP.h"
#include "GLCommon/OpenGLShaderLoader.h"

class LightApp : public OpenGLApp
{
public:
	LightApp();
	~LightApp();

	bool Init()override;
	void UpdateScene()override;
	void Render()override;
	void ClearnUp()override;

private:
	void BUildVAO();

private:
	OpenGLShaderLoader::Shader* m_shader = 0;     // ×ÅÉ«Æ÷³ÌÐò
	unsigned int m_vao = 0;
	unsigned int m_vbo = 0;

	OpenGLShaderLoader::Shader* m_lightShader = 0;
	unsigned int m_lightVao = 0;

	glm::vec3 m_lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
}; 
#endif // LightingMapsApp_h__