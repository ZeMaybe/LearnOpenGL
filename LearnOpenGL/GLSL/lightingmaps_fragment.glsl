
#version 430 core 
 

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;	
};
 
out vec4 FragColor;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform Material material;
uniform Light light;

in vec3 Normal;
in vec3 WorldPos;
in vec2 TexCoords;

void main()
{ 
	// ambient
	vec3 ambient = light.ambient*vec3(texture(material.diffuse,TexCoords));

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - WorldPos);
	float diff = max(dot(norm,lightDir),0.0f);
	vec3 diffuse = light.diffuse*diff*vec3(texture(material.diffuse,TexCoords));

	// specular	
	vec3 viewDir = normalize(viewPos - WorldPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);
	vec3 specular = light.specular*spec*vec3(texture(material.specular,TexCoords));

	FragColor = vec4(ambient+diffuse+specular,1.0f); 
}