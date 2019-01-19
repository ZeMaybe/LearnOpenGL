
#ifndef OpenGLUtility_h__
#define OpenGLUtility_h__

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <assert.h>

#define SAFE_DELETE_POINT(p) if(p){delete p; p = 0;}
#define SAFE_DELETE_ARRAY(p) if(p){delete [] p;p = 0;}

#endif // OpenGLUtility_h__