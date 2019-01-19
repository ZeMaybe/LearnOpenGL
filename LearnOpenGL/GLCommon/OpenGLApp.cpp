
#include "GLCommon/OpenGLAPP.h"

OpenGLApp* OpenGLApp::theApp = 0;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	assert(window == OpenGLApp::theApp->ScreenWindow());

	OpenGLApp::theApp->OnResize(width,height);
}

OpenGLApp::OpenGLApp(char* windowTitle /*= "OpenGLWnd"*/)
	:m_windowTitle(windowTitle)
{
	theApp = this;
}

OpenGLApp::OpenGLApp(char* windowTitle, unsigned int screenWidth, unsigned int screenHeight, 
	int glVersionMajor, int glVersionMinor, int glProfile)
	:m_windowTitle(windowTitle)
	,m_screenWidth(screenWidth)
	,m_screenHeight(screenHeight)
	,m_glVersionMajor(glVersionMajor)
	,m_glVersionMinor(glVersionMinor)
	,m_glProfile(glProfile)
{
	theApp = this;
}

OpenGLApp::~OpenGLApp()
{

}

bool OpenGLApp::Init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_glVersionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_glVersionMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, m_glProfile);

	m_screenWindow = glfwCreateWindow(800, 600, m_windowTitle, NULL, NULL);
	if (m_screenWindow == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_screenWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}
	glfwSetFramebufferSizeCallback(m_screenWindow, framebuffer_size_callback);

	return true;
}

void OpenGLApp::OnResize(unsigned int width, unsigned int height)
{
	m_screenWidth = width;
	m_screenHeight = height; 
	glViewport(0, 0, width, height); 
}

void OpenGLApp::ProcessInput()
{
	if (glfwGetKey(m_screenWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_screenWindow, true);
}

void OpenGLApp::Render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	//glClear(GL_DEPTH_BUFFER_BIT);
}

void OpenGLApp::Run()
{
	OpenGLApp::OnResize(m_screenWidth, m_screenHeight);

	while (!glfwWindowShouldClose(m_screenWindow))
	{ 
		ProcessInput();

		Render();

		glfwPollEvents(); 
	}
	
	/*
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glfwSwapBuffers(window);
	*/
}

void OpenGLApp::ClearnUp()
{
	glfwTerminate(); 
}

