
#include "LightingMapsApp.h"

LightingMapsApp theApp;


LightingMapsApp::LightingMapsApp()
	:OpenGLApp("LightingMaps")
{
}

LightingMapsApp::~LightingMapsApp()
{
	ClearnUp();
}

bool LightingMapsApp::Init()
{
	if (!OpenGLApp::Init())
		return false;

	m_camera = new OpenGLCamera::FPCamera(glm::vec3(0.0f, 0.0f, 10.0f));

	m_shader = new OpenGLShaderLoader::Shader("../GLSL/lightingmaps_vertex.glsl",
		"../GLSL/lightingmaps_fragment.glsl");
	m_lightShader = new OpenGLShaderLoader::Shader("../GLSL/light_vertex2.glsl",
		"../GLSL/light_fragment2.glsl");

	BUildVAO();

	m_diffuseMap.Load("../Images/box.png");
	m_specularMap.Load("../Images/box_specular.png");

	m_shader->Use();
	m_shader->SetInt("material.diffuse", 0);
	m_shader->SetInt("material.specular", 1);	

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_diffuseMap.Texture());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_specularMap.Texture());

	glEnable(GL_DEPTH_TEST);
	return true;
}

void LightingMapsApp::UpdateScene()
{
	//m_lightPos.y = sin(glfwGetTime()) * 5;
	//m_lightPos.x = cos(glfwGetTime()) * 5;
}

void LightingMapsApp::Render()
{
	OpenGLApp::Render();

	m_shader->Use();
	m_shader->SetMat4("view", m_camera->GetViewMatrix());
	m_shader->SetMat4("proj", m_camera->GetProjMatrix(1.0f*m_screenWidth / m_screenHeight, 0.1f, 100.0f));
	m_shader->SetVec3("lightPos", m_lightPos);
	m_shader->SetVec3("viewPos", m_camera->m_position);
	m_shader->SetVec3("lightColor", 1.0f, 1.0f, 1.0f);
	m_shader->SetVec3("material.ambient", 1.0f, 0.5f, 0.31f);
	m_shader->SetVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
	m_shader->SetVec3("material.specular", 0.5f, 0.5f, 0.5f);
	m_shader->SetFloat("material.shininess", 32.0f); 

	m_shader->SetVec3("light.ambient", 0.2f, 0.2f, 0.2f);
	m_shader->SetVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
	m_shader->SetVec3("light.specular", 1.0f, 1.0f, 1.0f);

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

	// light cube
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, m_lightPos);
	model = glm::scale(model, glm::vec3(0.2f));

	m_lightShader->Use();
	m_lightShader->SetMat4("model", model);
	m_lightShader->SetMat4("view", m_camera->GetViewMatrix());
	m_lightShader->SetMat4("proj", m_camera->GetProjMatrix(1.0f*m_screenWidth / m_screenHeight, 0.1f, 100.0f));
	glBindVertexArray(m_lightVao);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glfwSwapBuffers(m_screenWindow);
}

void LightingMapsApp::ClearnUp()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteVertexArrays(1, &m_lightVao);
	glDeleteBuffers(1, &m_vbo);

	SAFE_DELETE_POINT(m_shader);
	SAFE_DELETE_POINT(m_lightShader);

	OpenGLApp::ClearnUp();
}

void LightingMapsApp::BUildVAO()
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

	// light vao
	glGenVertexArrays(1, &m_lightVao);
	glBindVertexArray(m_lightVao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

/*
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



*/