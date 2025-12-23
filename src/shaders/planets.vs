#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord; 

out vec3 FragPos;
out vec3 Normal;
out vec3 vLightPos;
out vec2 TexCoord;

uniform vec3 LightPos; 

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(view * model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(view*model))) * aNormal;  
    vLightPos = vec3(view * vec4(LightPos, 1.0));
    TexCoord = aTexCoord;
    gl_Position = projection * vec4(FragPos, 1.0);
}