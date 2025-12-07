#version 330 core
out vec4 FragColor;  
in vec3 ourColor;
uniform float offset;

void main()
{
    FragColor = vec4(ourColor.x,ourColor.y+offset,ourColor.z, 1.0);
}