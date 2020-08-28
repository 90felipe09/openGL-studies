#pragma once 
// used to inform compiler to just load this header one time.
#define GLEW_NO_GLU
#define GLEW_STATIC
#include <GL/glew.h>

#define ASSERT(x) if(!(x)) __builtin_trap();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);