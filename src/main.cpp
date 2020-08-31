#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <thread>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

// In project files
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 600

void changeColor(
    float* red, 
    float* blue, 
    float* green, 
    float* redIncrement,
    float* blueIncrement,
    float* greenIncrement
    ){
    if(*red > 1.0f){
        *redIncrement = -0.002f;
    }
    else if(*red < 0.0f){
        *redIncrement = 0.002f;
    }

    if(*blue > 1.0f){
        *blueIncrement = -0.004f;
    }
    else if(*blue < 0.0f){
        *blueIncrement = 0.004f;
    }

    if(*green > 1.0f){
        *greenIncrement = -0.006f;
    }
    else if(*green < 0.0f){
        *greenIncrement = 0.006f;
    }

    *red += *redIncrement;
    *blue += *blueIncrement;
    *green += *greenIncrement;
}

int main(){
    GLFWwindow* window;

    if(!glfwInit()){
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WINDOW_HEIGHT, WINDOW_WIDTH, "OpenGL Renderer", NULL, NULL);
    if (!window){
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if(glewInit() != GLEW_OK){
        std::cout << "Error in glewInit()" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        float positions[] = {
            -0.5f, -0.5f, 0.0f, 0.0f,   // 0
             0.5f, -0.5f, 1.0f, 0.0f,   // 1
             0.5f,  0.5f, 1.0f, 1.0f,   // 2
            -0.5f,  0.5f, 0.0f, 1.0f    // 3
        };

        unsigned int indices[6] = {
            0, 1, 2,
            2, 3, 0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        float zoomMagnitude = 1.0f;
        float aspectRatio = WINDOW_HEIGHT/WINDOW_WIDTH;
        float baseLimit = 1.5f;
        glm::mat4 proj = glm::ortho(
            -1 * baseLimit * aspectRatio * zoomMagnitude,
             baseLimit * aspectRatio * zoomMagnitude,
            -1 * baseLimit * zoomMagnitude,
             baseLimit * zoomMagnitude,
            -1.0f * zoomMagnitude,
             1.0f * zoomMagnitude);

        Shader shader("../src/res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0, 0, 0, 1.0f);
        shader.SetUniform4mat("u_MVP", proj);

        float red = 0.5f;
        float blue = 0.2f;
        float green = 0.8f;

        float redIncrement = 0.002f;
        float blueIncrement = 0.004f;
        float greenIncrement = 0.006f;

        int counter = 0;
        int counterLimit = 20;
        
        Texture texture("../src/res/img/Obama.jpg");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        Renderer renderer;
        
        float zoomIncrement = 0.01f;
        while(!glfwWindowShouldClose(window)){
            renderer.Clear();

            renderer.Draw(va, ib, shader);
            shader.SetUniform4f("u_Color", red, green, blue, 1.0f);

            if (counter == counterLimit){
                // changeColor(&red, &blue, &green, &redIncrement, &blueIncrement, &greenIncrement);
                if (zoomMagnitude >= 1.5f){
                    zoomIncrement = -0.01f;
                }
                if (zoomMagnitude <= 0.5f){
                    zoomIncrement = 0.01f;
                }
                zoomMagnitude += zoomIncrement;
                proj = glm::ortho(
                    -1 * baseLimit * aspectRatio * zoomMagnitude,
                    baseLimit * aspectRatio * zoomMagnitude,
                    -1 * baseLimit * zoomMagnitude,
                    baseLimit * zoomMagnitude,
                    -1.0f * zoomMagnitude,
                    1.0f * zoomMagnitude);
                shader.SetUniform4mat("u_MVP", proj);
                counter = 0;
            }
            counter += 1;
            GLCall(glfwSwapBuffers(window));
            GLCall(glfwPollEvents());
        }
    }
    glfwTerminate();
    return 0;

}