
#include "GLCommon/OpenGLUtility.h"

#include <iostream>
using namespace std;

void CheckGLError(const char* file, int line)
{
	GLenum error = glGetError();
	if (error == GL_NO_ERROR)
		return;
	
	std::cout << file << ":" << line << std::endl;
	switch (error)
	{
	case GL_INVALID_ENUM:
		std::cout << "GL_ERROR: GL_INVALID_ENUM" << std::endl;
		break;
	case GL_INVALID_VALUE:
		std::cout << "GL_ERROR: GL_INVALID_VALUE" << std::endl;
		break;
	case GL_INVALID_OPERATION:
		std::cout << "GL_ERROR:GL_INVALID_OPERATION " << std::endl;
		break;
	case GL_STACK_OVERFLOW:
		std::cout << "GL_ERROR: GL_STACK_OVERFLOW" << std::endl;
		break;
	case GL_STACK_UNDERFLOW:
		std::cout << "GL_ERROR: GL_STACK_UNDERFLOW" << std::endl;
		break;
	case GL_OUT_OF_MEMORY:
		std::cout << "GL_ERROR:GL_OUT_OF_MEMORY " << std::endl;
		break;
	default:
		std::cout << "GL_ERROR: " << error << std::endl;
		break;
	}
}