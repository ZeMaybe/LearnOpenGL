
#include "GLCommon/OpenGLAPP.h"

OpenGLApp* OpenGLApp::theApp = 0;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	assert(window == OpenGLApp::theApp->ScreenWindow());

	OpenGLApp::theApp->OnResize(width,height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	assert(window == OpenGLApp::theApp->ScreenWindow());

	OpenGLApp::theApp->OnMouseMove(xpos, ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	assert(window == OpenGLApp::theApp->ScreenWindow());

	OpenGLApp::theApp->OnMouseScroll(xoffset, yoffset);
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
	SAFE_DELETE_POINT(m_camera);
}

bool OpenGLApp::Init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_glVersionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_glVersionMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, m_glProfile);

	m_screenWindow = glfwCreateWindow(m_screenWidth, m_screenHeight, m_windowTitle, NULL, NULL);
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
	glfwSetCursorPosCallback(m_screenWindow, mouse_callback);
	glfwSetScrollCallback(m_screenWindow, scroll_callback);

	//glfwSetInputMode(m_screenWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_CULL_FACE);

	return true;
}

void OpenGLApp::OnResize(unsigned int width, unsigned int height)
{
	m_screenWidth = width;
	m_screenHeight = height; 
	glViewport(0, 0, width, height); 
}

void OpenGLApp::OnMouseMove(double xpos, double ypos)
{
	static bool isFirstMouse = true;
	if (isFirstMouse)
	{
		m_lastMouseX = xpos;
		m_lastMouseY = ypos;
		isFirstMouse = false;
	}

	float xoffset = xpos - m_lastMouseX;
	float yoffset = ypos - m_lastMouseY;

	m_lastMouseX = xpos;
	m_lastMouseY = ypos;

	if (m_camera)
		m_camera->ProcessMouseMovement(xoffset, yoffset);
}

void OpenGLApp::OnMouseScroll(double xoffset, double yoffset)
{
	if (m_camera)
		m_camera->ProcessMouseScroll(yoffset);
}

void OpenGLApp::ProcessInput()
{
	if (glfwGetKey(m_screenWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_screenWindow, true);

	if (m_camera)
	{
		if (glfwGetKey(m_screenWindow, GLFW_KEY_W) == GLFW_PRESS)
			m_camera->ProcessKeyboard(GLCommon::FORWARD, m_deltaTime);
		if (glfwGetKey(m_screenWindow, GLFW_KEY_S) == GLFW_PRESS)
			m_camera->ProcessKeyboard(GLCommon::BACKWARD, m_deltaTime);
		if (glfwGetKey(m_screenWindow, GLFW_KEY_A) == GLFW_PRESS)
			m_camera->ProcessKeyboard(GLCommon::LEFT, m_deltaTime);
		if (glfwGetKey(m_screenWindow, GLFW_KEY_D) == GLFW_PRESS)
			m_camera->ProcessKeyboard(GLCommon::RIGHT, m_deltaTime);
	}
}

void OpenGLApp::Render()
{
	//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void OpenGLApp::UpdateScene()
{

}

void OpenGLApp::Run()
{
	OpenGLApp::OnResize(m_screenWidth, m_screenHeight);

	double currentFrame;

	while (!glfwWindowShouldClose(m_screenWindow))
	{ 
		currentFrame = glfwGetTime();
		m_deltaTime = currentFrame - m_lastFrame;
		m_lastFrame = currentFrame;

		ProcessInput();
		UpdateScene();

		Render();

		glfwPollEvents(); 
	}	
}

void OpenGLApp::ClearnUp()
{
	glfwTerminate(); 
}

