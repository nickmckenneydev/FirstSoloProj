#include "glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
GLfloat vertices[] = {
    -0.5,-0.5f,0.0f,
    0.5,-0.5f,0.0f,
    0.0f,0.5f,0.0f

};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);//Converts normal coords to screen coords
}
void processInput(GLFWwindow *window){
if(glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS){
    glfwSetWindowShouldClose(window, true);
}
}
int main()
{
  glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
 if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    GLuint VBO;
    glGenBuffers(1,&VBO);//generates buffer ID

    while (!glfwWindowShouldClose(window)){//Render Loop. Each time its one frame
        processInput(window);
            glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0f,0.0f,0.0f,1.0f);
    
 glfwSwapBuffers(window);//This is double buffering. Swapping front buffer and back. Allows to avoid not seeing pixel by pixel drawing
    glfwPollEvents();//any events are triggered. Like keyboard or mouse
    }

glfwTerminate();
return 0;
}

//graphics pipeline is 2 parts
//transform 3d coord into 2d coord
//2d coord into color pixels// settings
