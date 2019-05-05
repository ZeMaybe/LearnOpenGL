
#include "NanosuitApp.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GLCommon/FileSystem.h"

NanosuitApp theApp;


NanosuitApp::NanosuitApp()
	:OpenGLApp("Nano suit")
{
}

NanosuitApp::~NanosuitApp()
{
	ClearnUp();
}

bool NanosuitApp::Init()
{
	if (!OpenGLApp::Init())
		return false;
	m_camera = new GLCommon::FPCamera(glm::vec3(0.0f, 0.0f, 3.0f));

	GLCommon::OpenGLFileSystem fs;
	m_shader = new GLCommon::Shader(fs.GetShaderFolder() + "nanosuit_vertex.glsl",
		fs.GetShaderFolder() + "nanosuit_fragment.glsl");


	m_borderShader = new GLCommon::Shader(fs.GetShaderFolder() + "nanosuit_vertex.glsl",
		fs.GetShaderFolder() + "border_fragment.glsl");


	m_model = new GLCommon::Model(fs.GetModelsFolder() + "nanosuit/nanosuit.obj");

	//glEnable(GL_DEPTH_TEST);

	return true;
}

void NanosuitApp::Render()
{
	OpenGLApp::Render(); 

	GL_CALL(glEnable(GL_DEPTH_TEST));
	glDepthFunc(GL_LESS);

	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);

	m_shader->Use();
	m_shader->SetMat4("view", m_camera->GetViewMatrix());
	m_shader->SetMat4("proj", m_camera->GetProjMatrix(1.0f*m_screenWidth / m_screenHeight, 0.1f, 100.0f));
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
	m_shader->SetMat4("model", model);
	m_model->Draw(*m_shader);

	model = glm::translate(model, glm::vec3(8.5f, 0.0f, 0.0f));
	m_shader->SetMat4("model", model);
	m_model->Draw(*m_shader);

	glDisable(GL_DEPTH_TEST);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilMask(0x00);

	m_borderShader->Use();
	m_borderShader->SetMat4("view", m_camera->GetViewMatrix());
	m_borderShader->SetMat4("proj", m_camera->GetProjMatrix(1.0f*m_screenWidth / m_screenHeight, 0.1f, 100.0f));
	
	model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(0.1009f, 0.1009f, 0.1009f));
	m_borderShader->SetMat4("model", model);
	m_model->Draw(*m_borderShader);

	model = glm::translate(model, glm::vec3(8.5f, 0.0f, 0.0f));
	m_borderShader->SetMat4("model", model);
	m_model->Draw(*m_borderShader);

	glEnable(GL_DEPTH_TEST);
	glStencilMask(0xFF);

	glfwSwapBuffers(m_screenWindow);
}

void NanosuitApp::ClearnUp()
{
	SAFE_DELETE_POINT(m_shader);
	SAFE_DELETE_POINT(m_borderShader);
	SAFE_DELETE_POINT(m_model);

	OpenGLApp::ClearnUp();
}
 