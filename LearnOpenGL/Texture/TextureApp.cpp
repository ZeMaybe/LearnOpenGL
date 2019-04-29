
#include "TextureApp.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GLCommon/FileSystem.h"

TextureApp theApp;

TextureApp::TextureApp()
	:OpenGLApp("Texture")
{
}

TextureApp::~TextureApp()
{
	SAFE_DELETE_POINT(m_shader);
}

bool TextureApp::Init()
{
	if (!OpenGLApp::Init())
		return false;

	GLCommon::OpenGLFileSystem fs;
	m_shader = new OpenGLShaderLoader::Shader(fs.GetShaderFolder()+"texture_vertex.glsl", 
		fs.GetShaderFolder()+"texture_fragment.glsl");

	m_texture01.Load(fs.GetTextureFolder()+"wall.jpg");
	m_texture02.Load(fs.GetTextureFolder()+"awesomeface.png");

	BUildVAO();

	m_shader->Use();
	m_shader->SetInt("texture1", 0);
	m_shader->SetInt("texture2", 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture01.Texture());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_texture02.Texture()); 

	glBindVertexArray(m_vao);
	return true;
}

void TextureApp::OnResize(unsigned int width, unsigned int height)
{
	OpenGLApp::OnResize(width, height);
}

void TextureApp::ProcessInput()
{
	OpenGLApp::ProcessInput(); 
}

void TextureApp::UpdateScene()
{
	float mixValue = (sin(glfwGetTime()) + 1.0f)*0.5f;
	m_shader->SetFloat("mixValue", mixValue); 

	glm::mat4x4 trans = glm::mat4x4(1.0f);
	trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
	trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
	m_shader->SetMat4("transform", trans);
}

void TextureApp::Render()
{
	OpenGLApp::Render();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glfwSwapBuffers(m_screenWindow); 
}

void TextureApp::ClearnUp()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);
	OpenGLApp::ClearnUp();
}

void TextureApp::BUildVAO()
{
	// vertices
	float vertices[] = {
		// pos            // color        // uv
		0.5f,0.5f,0.0f,   1.0f,0.0f,0.0f, 1.0f, 1.0f, // top right
		0.5f,-0.5f,0.0f,  0.0f,1.0f,0.0f, 1.0f, 0.0f, // bottom right
		-0.5f,-0.5f,0.0f, 0.0f,0.0f,1.0f, 0.0f, 0.0f, // bottom left
		-0.5f,0.5f,0.0f,  0.5f,0.5f,0.5f, 0.0f, 1.0f  // top left
	};
	unsigned int indices[] = {
		0,1,3,
		1,2,3
	};

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}
