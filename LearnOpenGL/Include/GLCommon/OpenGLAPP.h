
#ifndef OpenGLAPP_h__
#define OpenGLAPP_h__

#include "GLCommon/OpenGLUtility.h"
#include "GLCommon/OpenGLCamera.h"

class OpenGLApp
{
public:
	OpenGLApp(char* windowTitle = "OpenGLWnd");
	OpenGLApp(char* windowTitle, unsigned int screenWidth, unsigned int screenHeight,
		int glVersionMajor, int glVersionMinor, int glProfile);
	virtual ~OpenGLApp();

	virtual bool Init(); 

	virtual void OnResize(unsigned int width, unsigned int height);
	virtual void OnMouseMove(double xpos,double ypos);
	virtual void OnMouseScroll(double xoffset,double yoffset);

	virtual void ProcessInput();
	virtual void Render();
	virtual void UpdateScene();

	void Run();

	virtual void ClearnUp();

	static OpenGLApp* theApp;

public:
	char* WindowTitle() { return m_windowTitle; }
	GLFWwindow* ScreenWindow() { return m_screenWindow; }
	unsigned int ScreenWidth() { return m_screenWidth; }
	unsigned int ScreenHeight() { return m_screenHeight; }

protected:
	char* m_windowTitle;
	unsigned int m_screenWidth = 800;
	unsigned int m_screenHeight = 600;
	int m_glVersionMajor = 4;
	int m_glVersionMinor = 3;
	int m_glProfile = GLFW_OPENGL_CORE_PROFILE;

	GLFWwindow* m_screenWindow = 0;

	double m_lastFrame = 0.0;
	float m_deltaTime = 0.0f;

	double m_lastMouseX = 0.0;
	double m_lastMouseY = 0.0;

	GLCommon::FPCamera* m_camera = 0;
};

#endif // OpenGLAPP_h__