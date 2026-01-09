
#include "glad.h"
#include <GLFW/glfw3.h>

#include "shader.h"
#include "camera.h"
#include "model.h"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"// glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <filesystem>


#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
// #include "TinyGLTF/tiny_gltf.h"
namespace fs = std::filesystem;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
unsigned int loadTexture(const char *path);
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;





Camera camera(glm::vec3(0.0f, 1.0f, 10.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
float deltaTime = 0.0f;	
float lastFrame = 0.0f;
GLint success;
char infoLog[512];
int main()
{
glfwInit();
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
glfwWindowHint(GLFW_STENCIL_BITS, 8); // Request an 8-bit stencil buffer
GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
if (window == NULL)
{
std::cout << "Failed to create GLFW window" << std::endl;
glfwTerminate();
return -1;
}
glfwMakeContextCurrent(window);
glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
glfwSetCursorPosCallback(window, mouse_callback);
glfwSetScrollCallback(window, scroll_callback);
glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
{
std::cout << "Failed to initialize GLAD" << std::endl;
return -1;
}

Shader planets("/home/a/Desktop/FirstSoloProj/src/shaders/planets.vs", "/home/a/Desktop/FirstSoloProj/src/shaders/planets.fs");
Shader shaderSingleColor("/home/a/Desktop/FirstSoloProj/src/shaders/planets.vs","/home/a/Desktop/FirstSoloProj/src/shaders/shaderSingleColor.fs");
Model modelObjectMercury("/home/a/Desktop/FirstSoloProj/src/objects/mercury/Mercury 1K.obj");
Model sunGLTF("/home/a/Desktop/FirstSoloProj/src/objects/sun/scene.gltf");
unsigned int PurpleDiffuseMap=loadTexture("/home/a/Desktop/FirstSoloProj/src/purple.jpeg");
unsigned int SunPng=loadTexture("/home/a/Desktop/FirstSoloProj/src/sun.png");

float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

glm::vec3 pointLightPositions[] = {
        glm::vec3( 8.0f,  0.0f,  0.0f),
};
glm::vec3 pointLightColors[] = {
    glm::vec3(0.75f, 0.0f, 1.0f)
};
unsigned int VBO,PlanetsVAO;
glGenVertexArrays(1, &PlanetsVAO);
glGenBuffers(1,&VBO);
glBindVertexArray(PlanetsVAO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
// position attribute
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
// normal attribute
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
glEnableVertexAttribArray(1);
// texture attribute
glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
glEnableVertexAttribArray(2);

while (!glfwWindowShouldClose(window))
{
float currentFrame = static_cast<float>(glfwGetTime());
deltaTime = currentFrame - lastFrame;
lastFrame = currentFrame;

processInput(window);
glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
// glClearStencil(0);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

glUseProgram(planets.ID);
// Planet Global
glUniform3fv(glGetUniformLocation(planets.ID, "viewPos"), 1, &camera.Position[0]); 
glUniform1i(glGetUniformLocation(planets.ID, "material.diffuse"), 0); 
glUniform1i(glGetUniformLocation(planets.ID, "material.specular"), 1); 
glUniform1f(glGetUniformLocation(planets.ID, "material.shininess"), 5.0f); 
glUniform3f(glGetUniformLocation(planets.ID, "dirLight.direction"), -0.2f, -1.0f, -0.3f);		
glUniform3f(glGetUniformLocation(planets.ID, "dirLight.ambient"), 0.3f, 0.24f, 0.14f);	
glUniform3f(glGetUniformLocation(planets.ID, "dirLight.diffuse"), 0.7f, 0.42f, 0.26f); 
glUniform3f(glGetUniformLocation(planets.ID, "dirLight.specular"), 0.5f, 0.5f, 0.5f);
// // Point light 1
glUniform3f(glGetUniformLocation(planets.ID, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);		
glUniform3f(glGetUniformLocation(planets.ID, "pointLights[0].ambient"), pointLightColors[0].x * 0.1,  pointLightColors[0].y * 0.1,  pointLightColors[0].z * 0.1);		
glUniform3f(glGetUniformLocation(planets.ID, "pointLights[0].diffuse"), pointLightColors[0].x,  pointLightColors[0].y,  pointLightColors[0].z); 
glUniform3f(glGetUniformLocation(planets.ID, "pointLights[0].specular"), pointLightColors[0].x,  pointLightColors[0].y,  pointLightColors[0].z);
glUniform1f(glGetUniformLocation(planets.ID, "pointLights[0].constant"), 1.0f);
glUniform1f(glGetUniformLocation(planets.ID, "pointLights[0].linear"), 0.09);
glUniform1f(glGetUniformLocation(planets.ID, "pointLights[0].quadratic"), 0.032);	

// view/projection transformations
glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
glm::mat4 view = camera.GetViewMatrix();
planets.setMat4("projection", projection);
planets.setMat4("view", view);
//Every pixel of the next object drawn will be painted directly onto the screen, 
// glStencilMask(0x00), the guard locks the buffer.
// glStencilMask(0xFF), the guard allows you to write new values (like 1s)

// glEnable(GL_DEPTH_TEST);
// glEnable(GL_STENCIL_TEST);
// glStencilMask(0xFF);

// glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
// glStencilFunc(GL_ALWAYS,1,0xFF);

//Render SMALL Green Planet



glm::mat4 model = glm::mat4(1.0f);
planets.setMat4("model", model);
model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));

glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, SunPng);

glBindVertexArray(PlanetsVAO);


glDrawArrays(GL_TRIANGLES, 0, 36);



//Render BIG Purple Planet 

// glUseProgram(planets.ID);

// model = glm::mat4(1.0f);
// model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
// model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
// glBindVertexArray(PlanetsVAO);
// glActiveTexture(GL_TEXTURE0);
// glBindTexture(GL_TEXTURE_2D,PurpleDiffuseMap);
// planets.setMat4("model",model);
// glDrawArrays(GL_TRIANGLES, 0, 36);

// Render Sun Model
// model = glm::mat4(1.0f);
// model = glm::scale(model, glm::vec3(0.20f, 0.20f, 0.20f));	
// glUniformMatrix4fv(glGetUniformLocation(planets.ID, "model"), 1, GL_FALSE, &model[0][0]);
// sunGLTF.Draw(planets);


// // 2nd render pass which is my outline
// glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
// glStencilMask(0x00);
// glDisable(GL_DEPTH_TEST);
// shaderSingleColor.use(); // Im switching shader
// shaderSingleColor.setMat4("projection", projection);
// shaderSingleColor.setMat4("view", view);
// model = glm::mat4(1.0f);
// model = glm::scale(model, glm::vec3(0.27f, 0.27f, 0.27f)); 
// shaderSingleColor.setMat4("model", model);
// sunGLTF.Draw(shaderSingleColor);
// // Reset state
// glStencilMask(0xFF);
// glStencilFunc(GL_ALWAYS, 0, 0xFF);
// glEnable(GL_DEPTH_TEST);  





glfwSwapBuffers(window);
glfwPollEvents();
}
glDeleteProgram(planets.ID);
glDeleteBuffers(1, &VBO);
glfwTerminate();
return 0;
}
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)

{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
unsigned int loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        std::cout << "Texture WIN to load at path: " << path << std::endl;

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}