#include "Renderer.h"
#include <iostream>

void GLClearError(){
    // Get all errors. It will iterate till there's no errors in queue
    while(glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line){
    while(GLenum error = glGetError()){
        std::cout << "[OpenGL Error] (" << error << "):" << function << " " << file
        << ":" << line << std::endl;
        return false;
    }
    return true;
}