#define GLEW_NO_GLU
#define GLEW_STATIC
#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <thread>

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 600

int main(){
    GLFWwindow* window;

    if(!glfwInit()){
        return -1;
    }

    
    window = glfwCreateWindow(WINDOW_HEIGHT, WINDOW_WIDTH, "Game Engine", NULL, NULL);
    if (!window){
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK){
        std::cout << "Error in glewInit()" << std::endl;
    }

    unsigned int a;
    glGenBuffers(1, &a);

    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);

        glVertex2f(-0.5f, -0.5f);
        glVertex2f( 0.0f,  0.5f);
        glVertex2f( 0.5f, -0.5f);
        glEnd();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


}