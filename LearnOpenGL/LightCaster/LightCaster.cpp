
#include "LightCaster.h"
#include "GLCommon/FileSystem.h"

LightCasterApp theApp;

LightCasterApp::LightCasterApp()
	:OpenGLApp("Light caster")
{

}
LightCasterApp::~LightCasterApp()
{
	ClearnUp();
}

bool LightCasterApp::Init()
{
	if (!OpenGLApp::Init())
		return false;

	m_camera = new GLCommon::FPCamera(glm::vec3(0.0f, 0.0f, 10.0f));

	GLCommon::OpenGLFileSystem fs;
	m_shader = new GLCommon::Shader(fs.GetShaderFolder() + "lightcaster_vertex.glsl",
		fs.GetShaderFolder() + "lightcaster_fragment.glsl");
	m_pointLightShader = new GLCommon::Shader(fs.GetShaderFolder() + "light_vertex2.glsl",
		fs.GetShaderFolder() + "light_fragment2.glsl");

	BUildVAO();

	m_diffuseMap.Load(fs.GetTextureFolder() + "box.png");
	m_specularMap.Load(fs.GetTextureFolder() + "box_specular.png");
	m_shader->Use();

	// material
	m_shader->SetInt("material.diffuse", 0);
	m_shader->SetInt("material.specular", 1); 
	m_shader->SetFloat("material.shininess", 32.0f);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_diffuseMap.Texture());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_specularMap.Texture());

	// direction light
	m_shader->SetVec3("dirLight.ambient", 0.2f, 0.2f, 0.2f);
	m_shader->SetVec3("dirLight.diffuse", 0.5f, 0.5f, 0.5f);
	m_shader->SetVec3("dirLight.specular", 1.0f, 1.0f, 1.0f);
	m_shader->SetVec3("dirLight.direction",m_directionLightDirection);

	// point light
	m_shader->SetFloat("pointLight.constant", 1.0f);
	m_shader->SetFloat("pointLight.linear", 0.09f);
	m_shader->SetFloat("pointLight.quadratic", 0.032f);
	m_shader->SetVec3("pointLight.position", m_pointLightPosition);
	m_shader->SetVec3("pointLight.ambient", 0.2f, 0.2f, 0.2f);
	m_shader->SetVec3("pointLight.diffuse", 0.5f, 0.5f, 0.5f);
	m_shader->SetVec3("pointLight.specular", 1.0f, 1.0f, 1.0f);

	// spot light
	m_shader->SetVec3("spotLight.ambient", 0.2f, 0.2f, 0.2f);
	m_shader->SetVec3("spotLight.diffuse", 0.5f, 0.5f, 0.5f);
	m_shader->SetVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
	m_shader->SetFloat("spotLight.constant", 1.0f);
	m_shader->SetFloat("spotLight.linear", 0.09f);
	m_shader->SetFloat("spotLight.quadratic", 0.032f);
	m_shader->SetFloat("spotLight.cutoff", glm::cos(glm::radians(12.5f)));
	m_shader->SetFloat("spotLight.outerCutoff", glm::cos(glm::radians(17.5f)));

	glEnable(GL_DEPTH_TEST);
	return true;
}

void LightCasterApp::UpdateScene()
{

}
void LightCasterApp::Render()
{
	OpenGLApp::Render();

	m_shader->Use();
	m_shader->SetMat4("view", m_camera->GetViewMatrix());
	m_shader->SetMat4("proj", m_camera->GetProjMatrix(1.0f*m_screenWidth / m_screenHeight, 0.1f, 100.0f));
	m_shader->SetVec3("viewPos", m_camera->m_position);

	m_shader->SetVec3("spotLight.position", m_camera->m_position);
	m_shader->SetVec3("spotLight.direction", m_camera->m_front);

	glBindVertexArray(m_vao);

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	for (unsigned int i = 0; i < 10; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.0f * (i + 1);
		model = glm::rotate(model, /*(float)glfwGetTime()**/glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		m_shader->SetMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}


	// point light cube
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, m_pointLightPosition);
	model = glm::scale(model, glm::vec3(0.2f));

	m_pointLightShader->Use();
	m_pointLightShader->SetMat4("model", model);
	m_pointLightShader->SetMat4("view", m_camera->GetViewMatrix());
	m_pointLightShader->SetMat4("proj", m_camera->GetProjMatrix(1.0f*m_screenWidth / m_screenHeight, 0.1f, 100.0f));
	glBindVertexArray(m_pointLightVao);
	glDrawArrays(GL_TRIANGLES, 0, 36); 

	glfwSwapBuffers(m_screenWindow); 
}

void LightCasterApp::ClearnUp()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteVertexArrays(1, &m_pointLightVao);
	glDeleteBuffers(1, &m_vbo);

	SAFE_DELETE_POINT(m_shader);
	SAFE_DELETE_POINT(m_pointLightShader);

	OpenGLApp::ClearnUp();
}


void LightCasterApp::BUildVAO()
{
	// vertices
	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	// Ìî³ä¶¥µãÊý¾Ý
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// vao
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// point light vao
	glGenVertexArrays(1, &m_pointLightVao);
	glBindVertexArray(m_pointLightVao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
} 

 