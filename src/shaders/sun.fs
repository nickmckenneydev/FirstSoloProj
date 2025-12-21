#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D sunTexture; 
uniform vec3 objectColor; // Added this declaration!

void main()
{
    // Now the shader knows what objectColor is
    FragColor = texture(sunTexture, TexCoord) * vec4(objectColor, 1.0);
}