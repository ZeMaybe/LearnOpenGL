
#include "GLCommon/OpenGLAPP.h"

int main()
{
	if (OpenGLApp::theApp == 0)
	{
		std::cout << "Fatal error : theApp is null!" << std::endl;
		return -1;
	}

	if (!OpenGLApp::theApp->Init())
	{
		std::cout << "Fatal error : Init failed!" << std::endl;
		return -1;
	}

	OpenGLApp::theApp->Run();

	OpenGLApp::theApp->ClearnUp();

	return 0;
}