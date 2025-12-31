#version 330 core
out vec4 FragColor;

struct Material {
sampler2D diffuse;
sampler2D specular;    
float shininess;

}; 

struct Light {
vec3 position;
vec3 ambient;
vec3 diffuse;
vec3 specular;
};

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;
  
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
// ambient is background light. Light is bouncing around. 
//Comes from indirect source like a wall
vec3 ambient = light.ambient  * texture(material.diffuse, TexCoords).rgb;
  	
// diffuse directional light scattered evenly. Light directly hits object
// Issues is light can be created as absolute darkness without light hitting it
vec3 norm = normalize(Normal);
vec3 lightDir = normalize(light.position - FragPos);
float diff = max(dot(norm, lightDir), 0.0);
vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  
    
// specular Shine
// Some parts of an object shine or dont. 
vec3 viewDir = normalize(viewPos - FragPos);
vec3 reflectDir = reflect(-lightDir, norm);  
float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;  

float distance = length(light.position - FragPos);
float constant  = 1.0;
float linear    = 0.09;
float quadratic = 0.032;
float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));
diffuse  *= attenuation;
specular *= attenuation;


vec3 phongShading = ambient + diffuse + specular;
FragColor = vec4(phongShading, 1.0);
} 