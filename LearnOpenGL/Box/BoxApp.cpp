
#include "BoxApp.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

BoxApp theApp;

BoxApp::BoxApp()
	:OpenGLApp("Box")
{ 
}

BoxApp::~BoxApp()
{
	SAFE_DELETE_POINT(m_shader);
}

bool BoxApp::Init()
{
	if (!OpenGLApp::Init())
		return false;

	m_camera = new OpenGLCamera::FPCamera();

	m_shader = new OpenGLShaderLoader::Shader("../GLSL/box_vertex.glsl",
		"../GLSL/box_fragment.glsl");

	m_texture01.Load("../Images/wall.jpg");
	m_texture02.Load("../Images/awesomeface.png");

	// 测试模型加载 -- 无实际解析代码
	Assimp::Importer importer;
	const aiScene * scene = importer.ReadFile("../Models/nanosuit/nanosuit.obj", aiProcess_Triangulate | aiProcess_FlipUVs);

	BUildVAO();

	m_shader->Use();
	m_shader->SetInt("texture1", 0);
	m_shader->SetInt("texture2", 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture01.Texture());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_texture02.Texture());

	glBindVertexArray(m_vao);

	glEnable(GL_DEPTH_TEST);

	return true;
}


void BoxApp::OnResize(unsigned int width, unsigned int height)
{
	OpenGLApp::OnResize(width, height);
}

void BoxApp::ProcessInput()
{
	OpenGLApp::ProcessInput();
}

void BoxApp::UpdateScene()
{
	float mixValue = (sin(glfwGetTime()) + 1.0f)*0.5f;
	m_shader->SetFloat("mixValue", mixValue);

	//glm::mat4 model = glm::mat4(1.0f);
	//model = glm::rotate(model, (float)glfwGetTime()*glm::radians(-55.0f), glm::vec3(1.0f, 1.0f, 0.0f));
	//m_shader->SetMat4x4("model", glm::value_ptr(model));

	//float radius = 20.0f;
	//float camX = sin(glfwGetTime())*radius;
	//float camZ = cos(glfwGetTime())*radius;
	//glm::mat4 view = glm::mat4(1.0f);
	//view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0, 1.0, 0.0));
	//m_shader->SetMat4("view", view);

	glm::mat4 view = m_camera->GetViewMatrix();
	m_shader->SetMat4("view", view);

	//glm::mat4 projection = glm::mat4(1.0f);
	//projection = glm::perspective(glm::radians(45.0f), (1.0f*m_screenWidth) / (1.0f*m_screenHeight), 0.1f, 100.0f);
	//m_shader->SetMat4("proj", projection);
	m_shader->SetMat4("proj", m_camera->GetProjMatrix(1.0f*m_screenWidth / m_screenHeight, 0.1f, 100.0f));
}


void BoxApp::Render()
{
	OpenGLApp::Render();

	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
		float angle = 20.0f * (i+1);
		model = glm::rotate(model, (float)glfwGetTime()*glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		m_shader->SetMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	glfwSwapBuffers(m_screenWindow);
}

void BoxApp::ClearnUp()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	OpenGLApp::ClearnUp();
}

void BoxApp::BUildVAO()
{
	// vertices
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	//unsigned int indices[] = {
	//	0,1,3,
	//	1,2,3
	//};

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}
