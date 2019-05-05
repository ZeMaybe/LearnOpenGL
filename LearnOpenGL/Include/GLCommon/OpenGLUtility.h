
#ifndef OpenGLUtility_h__
#define OpenGLUtility_h__

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <assert.h>

#define SAFE_DELETE_POINT(p) if(p){delete p; p = 0;}
#define SAFE_DELETE_ARRAY(p) if(p){delete [] p;p = 0;}

void CheckGLError(const char* file, int line);

#define GL_CALL(x)  do { x;CheckGLError(__FILE__,__LINE__);} while(0)

#endif // OpenGLUtility_h__