#define STB_IMAGE_IMPLEMENTATION
#include "glad.h"
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include "shader.h"
#include "camera.h"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"// glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
unsigned int loadTexture(const char *path);
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 2.0f));
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
glEnable(GL_DEPTH_TEST);
Shader planets("/home/a/Desktop/FirstSoloProj/src/shaders/planets.vs", "/home/a/Desktop/FirstSoloProj/src/shaders/planets.fs");
Shader sun("/home/a/Desktop/FirstSoloProj/src/shaders/sun.vs", "/home/a/Desktop/FirstSoloProj/src/shaders/sun.fs");
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

unsigned int VBO,SunVAO,PlanetsVAO;
glGenVertexArrays(1, &SunVAO);
glGenBuffers(1,&VBO);

glBindVertexArray(SunVAO);
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
//SUN Texture
unsigned int sunTextureImage;
glGenTextures(1, &sunTextureImage);
glBindTexture(GL_TEXTURE_2D, sunTextureImage);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
int width, height, nrChannels;
unsigned char *data = stbi_load("/home/a/Desktop/FirstSoloProj/src/sun.png", &width, &height, &nrChannels, 0);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
glGenerateMipmap(GL_TEXTURE_2D);
stbi_image_free(data);
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

// Planets Texture
// Mercury Texture
unsigned int MercuryDiffuseMap = loadTexture("/home/a/Desktop/FirstSoloProj/src/mercury.jpeg");
unsigned int MercurySpecularMap = loadTexture("/home/a/Desktop/FirstSoloProj/src/mercurySpecMap.jpeg");

//Venus
unsigned int VenusDiffuseMap=loadTexture("/home/a/Desktop/FirstSoloProj/src/venus.jpg");
unsigned int VenusSpecularMap=loadTexture("/home/a/Desktop/FirstSoloProj/src/venusSpecMap.jpg");
glEnable(GL_DEPTH_TEST);

glm::vec3 lightPos = glm::vec3(0.0f,0.0f,0.0f);
glm::vec3 specularMaterial = glm::vec3(0.0f);
while (!glfwWindowShouldClose(window))
{
float currentFrame = static_cast<float>(glfwGetTime());
deltaTime = currentFrame - lastFrame;
lastFrame = currentFrame;

processInput(window);

glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//activate shader when setting uniforms/drawing objects
glUseProgram(sun.ID); 
glActiveTexture(GL_TEXTURE0); // Tell OpenGL we are using slot 0
glBindTexture(GL_TEXTURE_2D, sunTextureImage);
glUniform1i(glGetUniformLocation(sun.ID, "sunTexture"), 0);
glUniform3f(glGetUniformLocation(sun.ID, "objectColor"), 1.0f, 1.0f, 1.0f);
// view/projection transformations
glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
glm::mat4 view = camera.GetViewMatrix();
glUniformMatrix4fv(glGetUniformLocation(sun.ID, "projection"), 1, GL_FALSE, &projection[0][0]);
glUniformMatrix4fv(glGetUniformLocation(sun.ID, "view"), 1, GL_FALSE, &view[0][0]);
// world transformation
glm::mat4 model = glm::mat4(1.0f);
float sunSize = 2.6f;
model = glm::scale(model, glm::vec3(sunSize)); // a smaller cube

glUniformMatrix4fv(glGetUniformLocation(sun.ID, "model"), 1, GL_FALSE, &model[0][0]);
// render the SUN
glBindVertexArray(SunVAO);
glBindTexture(GL_TEXTURE_2D, sunTextureImage);
glDrawArrays(GL_TRIANGLES, 0, 36);

//Planets
glUseProgram(planets.ID);

// Global Material Properties
planets.setInt("material.diffuse",0);
planets.setInt("material.specular", 1);
//light properties Global
planets.setVec3("light.position", 0.0f, 0.0f, 0.0f);
planets.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

//material properties
glUniformMatrix4fv(glGetUniformLocation(planets.ID, "view"), 1, GL_FALSE, &view[0][0]);
glUniformMatrix4fv(glGetUniformLocation(planets.ID, "projection"), 1, GL_FALSE, &projection[0][0]);

// //Mercury
// Lighting
planets.setVec3("light.diffuse", 1.0f, 1.0f, 0.9f); 
planets.setVec3("light.ambient", 0.05f, 0.05f, 0.05f); 
// Materials
planets.setVec3("material.ambient", 0.1f, 0.1f, 0.1f);  
planets.setFloat("material.shininess", 16.0f);
// bind diffuse map
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, MercuryDiffuseMap);
// bind specular map
glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_2D, MercurySpecularMap);

model = glm::mat4(1.0f);
model = glm::rotate(model, (float)glfwGetTime()*glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
model = glm::translate(model, glm::vec3(sunSize+3.0f, 0.0f, 0.0f));
model = glm::rotate(model, (float)glfwGetTime()*3.0f, glm::vec3(0.0, 1.0, 0.0));
model = glm::scale(model, glm::vec3(0.6f)); // a smaller cube
glUniformMatrix4fv(glGetUniformLocation(planets.ID, "model"), 1, GL_FALSE, &model[0][0]);
glBindVertexArray(PlanetsVAO);
glDrawArrays(GL_TRIANGLES, 0, 36);

// render the Venus Planet
//Lighting
planets.setVec3("light.diffuse", 0.7f, 0.6f, 0.4f); 
planets.setVec3("light.ambient", 0.3f, 0.2f, 0.1f);
// Materials 
planets.setVec3("material.ambient", 0.4f, 0.2f, 0.1f);  
planets.setFloat("material.shininess", 2.0f);
// bind diffuse map
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, VenusDiffuseMap);
// bind specular map
glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_2D, VenusSpecularMap);
model = glm::mat4(1.0f);
model = glm::rotate(model, (float)glfwGetTime()*glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
model = glm::translate(model, glm::vec3(sunSize+7.0f, 0.0f, 0.0f));
model = glm::rotate(model, (float)glfwGetTime()*5.0f, glm::vec3(0.0, 1.0, 0.0));
model = glm::scale(model, glm::vec3(0.9f)); // a smaller cube
glUniformMatrix4fv(glGetUniformLocation(planets.ID, "model"), 1, GL_FALSE, &model[0][0]);
glBindVertexArray(PlanetsVAO);
glDrawArrays(GL_TRIANGLES, 0, 36);

glfwSwapBuffers(window);
glfwPollEvents();
}
glDeleteVertexArrays(1, &SunVAO);
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