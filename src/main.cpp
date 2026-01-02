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


glm::vec3 pointLightPositions[] = {
        glm::vec3( 8.0f,  0.0f,  0.0f),
};

glm::vec3 pointLightColors[] = {
    glm::vec3(0.75f, 0.0f, 1.0f)
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
unsigned int MercurySpecularMap = loadTexture("/home/a/Desktop/FirstSoloProj/src/mercurySpecMap.jpg");

//Venus
unsigned int VenusDiffuseMap=loadTexture("/home/a/Desktop/FirstSoloProj/src/venus.jpg");
unsigned int VenusSpecularMap=loadTexture("/home/a/Desktop/FirstSoloProj/src/venusSpecMap.jpg");
//Purple!
unsigned int PurpleDiffuseMap=loadTexture("/home/a/Desktop/FirstSoloProj/src/purple.jpeg");
glEnable(GL_DEPTH_TEST);

glm::vec3 lightPos = glm::vec3(0.0f,0.0f,0.0f);
glm::vec3 specularMaterial = glm::vec3(0.0f);
while (!glfwWindowShouldClose(window))
    {
// per-frame time logic
// --------------------
float currentFrame = static_cast<float>(glfwGetTime());
deltaTime = currentFrame - lastFrame;
lastFrame = currentFrame;

processInput(window);

glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glUseProgram(sun.ID); 
glActiveTexture(GL_TEXTURE0); 
glBindTexture(GL_TEXTURE_2D, sunTextureImage);
glUniform1i(glGetUniformLocation(sun.ID, "sunTexture"), 0);
glUniform3f(glGetUniformLocation(sun.ID, "objectColor"), 1.0f, 1.0f, 1.0f);
// view/projection transformations
glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
glm::mat4 view = camera.GetViewMatrix();
glUniformMatrix4fv(glGetUniformLocation(sun.ID, "projection"), 1, GL_FALSE, &projection[0][0]);
glUniformMatrix4fv(glGetUniformLocation(sun.ID, "view"), 1, GL_FALSE, &view[0][0]);

//Render the Sun
glm::mat4 model = glm::mat4(1.0f);
float sunSize = 1.6f;
model = glm::scale(model, glm::vec3(sunSize)); // a smaller cube
glUniformMatrix4fv(glGetUniformLocation(sun.ID, "model"), 1, GL_FALSE, &model[0][0]);
glBindVertexArray(SunVAO);
glBindTexture(GL_TEXTURE_2D, sunTextureImage);
glDrawArrays(GL_TRIANGLES, 0, 36); 


// Planets    
glUseProgram(planets.ID);
//Global Material Prop
planets.setInt("material.diffuse",0);
planets.setInt("material.specular", 1);
planets.setFloat("material.shininess", 32.0f);

// directional light
glUniform3f(glGetUniformLocation(planets.ID, "dirLight.direction"), -0.2f, -1.0f, -0.3f);		
glUniform3f(glGetUniformLocation(planets.ID, "dirLight.ambient"), 0.3f, 0.24f, 0.14f);	
glUniform3f(glGetUniformLocation(planets.ID, "dirLight.diffuse"), 0.7f, 0.42f, 0.26f); 
glUniform3f(glGetUniformLocation(planets.ID, "dirLight.specular"), 0.5f, 0.5f, 0.5f);
// Point light 1
glUniform3f(glGetUniformLocation(planets.ID, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);		
glUniform3f(glGetUniformLocation(planets.ID, "pointLights[0].ambient"), pointLightColors[0].x * 0.1,  pointLightColors[0].y * 0.1,  pointLightColors[0].z * 0.1);		
glUniform3f(glGetUniformLocation(planets.ID, "pointLights[0].diffuse"), pointLightColors[0].x,  pointLightColors[0].y,  pointLightColors[0].z); 
glUniform3f(glGetUniformLocation(planets.ID, "pointLights[0].specular"), pointLightColors[0].x,  pointLightColors[0].y,  pointLightColors[0].z);
glUniform1f(glGetUniformLocation(planets.ID, "pointLights[0].constant"), 1.0f);
glUniform1f(glGetUniformLocation(planets.ID, "pointLights[0].linear"), 0.09);
glUniform1f(glGetUniformLocation(planets.ID, "pointLights[0].quadratic"), 0.032);		
// SpotLight
glUniform3f(glGetUniformLocation(planets.ID, "spotLight.position"), camera.Position.x, camera.Position.y, camera.Position.z);	
glUniform3f(glGetUniformLocation(planets.ID, "spotLight.direction"), camera.Front.x, camera.Front.y, camera.Front.z);
glUniform3f(glGetUniformLocation(planets.ID, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);	
glUniform3f(glGetUniformLocation(planets.ID, "spotLight.diffuse"), 0.8f, 0.8f, 0.0f); 
glUniform3f(glGetUniformLocation(planets.ID, "spotLight.specular"), 0.8f, 0.8f, 0.0f);
glUniform1f(glGetUniformLocation(planets.ID, "spotLight.constant"), 1.0f);
glUniform1f(glGetUniformLocation(planets.ID, "spotLight.linear"), 0.09);
glUniform1f(glGetUniformLocation(planets.ID, "spotLight.quadratic"), 0.032);			
glUniform1f(glGetUniformLocation(planets.ID, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
glUniform1f(glGetUniformLocation(planets.ID, "spotLight.outerCutOff"), glm::cos(glm::radians(13.0f)));

planets.setVec3("viewPos", camera.Position);
glUniformMatrix4fv(glGetUniformLocation(planets.ID, "view"), 1, GL_FALSE, &view[0][0]);
glUniformMatrix4fv(glGetUniformLocation(planets.ID, "projection"), 1, GL_FALSE, &projection[0][0]);

// world transformation
model = glm::mat4(1.0f);
planets.setMat4("model", model);
glBindVertexArray(PlanetsVAO);

glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, MercuryDiffuseMap);

glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_2D, MercurySpecularMap);

model = glm::mat4(1.0f);
model = glm::translate(model, glm::vec3( 0.0f,  0.0f,  0.0f));

model = glm::rotate(model, (float)glfwGetTime() * glm::radians(30.0f), glm::vec3(0.0, 1.0, 0.0));
model = glm::translate(model, glm::vec3(sunSize + 2.0f, 0.0f, 0.0f));
model = glm::rotate(model, (float)glfwGetTime() * 0.5f, glm::vec3(0.0, 1.0, 0.0));
model = glm::scale(model, glm::vec3(0.4f));
glUniformMatrix4fv(glGetUniformLocation(planets.ID, "model"), 1, GL_FALSE, &model[0][0]);
glDrawArrays(GL_TRIANGLES, 0, 36);

glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, VenusDiffuseMap);
glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_2D, VenusSpecularMap);

model = glm::mat4(1.0f);
model = glm::translate(model, glm::vec3( 0.0f,  0.0f,  0.0f));
model = glm::rotate(model, (float)glfwGetTime() * glm::radians(30.0f), glm::vec3(0.0, 1.0, 0.0));
model = glm::translate(model, glm::vec3(sunSize + 3.0f, 0.0f, 0.0f));
model = glm::rotate(model, (float)glfwGetTime() * 0.5f, glm::vec3(0.0, 1.0, 0.0));
model = glm::scale(model, glm::vec3(0.3f));
glUniformMatrix4fv(glGetUniformLocation(planets.ID, "model"), 1, GL_FALSE, &model[0][0]);
glDrawArrays(GL_TRIANGLES, 0, 36);



glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, PurpleDiffuseMap);
model = glm::mat4(1.0f);
model = glm::translate(model, pointLightPositions[0]);
glUniformMatrix4fv(glGetUniformLocation(planets.ID, "model"), 1, GL_FALSE, &model[0][0]);
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