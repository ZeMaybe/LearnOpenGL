
#include "TriangleApp.h"
#include "GLCommon/FileSystem.h"

TriangleApp theApp;

TriangleApp::TriangleApp()
	:OpenGLApp("Triangle")
{

}

TriangleApp::~TriangleApp()
{
	SAFE_DELETE_POINT(m_shader);
}

bool TriangleApp::Init()
{
	if(!OpenGLApp::Init())
		return false;

	GLCommon::OpenGLFileSystem fs;
	m_shader = new GLCommon::Shader(fs.GetShaderFolder() + "first_triangle_vertex.glsl",
		fs.GetShaderFolder() + "first_triangle_fragment.glsl");

	BUildVAO();

	m_shader->Use();
	glBindVertexArray(m_vao);

	return true;
}

void TriangleApp::OnResize(unsigned int width, unsigned int height)
{
	OpenGLApp::OnResize(width, height);
}

void TriangleApp::ProcessInput()
{
	OpenGLApp::ProcessInput();
}

void TriangleApp::UpdateScene()
{
	float timeValue = glfwGetTime();
	float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
	float redValue = cos(greenValue)/2.0f + 0.5f;
	m_shader->SetFloat("timeColor",redValue,greenValue,greenValue,1.0f);	
}

void TriangleApp::Render()
{
	OpenGLApp::Render();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glfwSwapBuffers(m_screenWindow);
}

void TriangleApp::ClearnUp()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);
	OpenGLApp::ClearnUp();
}

void TriangleApp::BUildVAO()
{
	// vertices
	float vertices[] = {
		// pos            // color
		0.5f,0.5f,0.0f,   1.0f,1.0f,1.0f,    // top right
		0.5f,-0.5f,0.0f,  1.0f,1.0f,0.0f,    // bottom right
		-0.5f,-0.5f,0.0f, 1.0f,0.0f,0.0f,    // bottom left
		-0.5f,0.5f,0.0f,  0.0f,0.0f,0.0f     // top left
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
		
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

//const char * vertexShaderSource = "#version 430 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"void main()\n"
//"{\n"
//"	gl_Position = vec4(aPos,1.0);\n"
//"}\n\0";
//
//const char* fragmentShaderSource = "#version 430 core\n"
//"out vec4 FragColor;\n"
//"void main()\n"
//"{\n"
//"	FragColor = vec4(0.5f);\n"
//"}\n\0";
