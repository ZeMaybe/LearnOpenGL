#version 430 core 

in vec3 Normal;
in vec3 WorldPos;
in vec2 TexCoords;

out vec4 FragColor;


struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

// 方向光
struct DirectionLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// 点光
struct PointLight
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

// 聚光
struct SpotLight
{
    vec3 position;
    vec3 direction;
    float cutoff;        // 切角的余弦值
    float outerCutoff;   // 外切角的余弦值

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform vec3 viewPos;
uniform Material material;
uniform DirectionLight dirLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;

vec3 CalcDirLight(DirectionLight light,vec3 normal,vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(normal,lightDir),0.0f);

    vec3 reflectDir = reflect(-lightDir,normal);
    float spec = pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);

    vec3 ambient = light.ambient*vec3(texture(material.diffuse,TexCoords));
    vec3 diffuse = light.diffuse*diff*vec3(texture(material.diffuse,TexCoords));
	vec3 specular = light.specular*spec*vec3(texture(material.specular,TexCoords));

     return ambient + diffuse + specular;
}

vec3 CalcPointLight(PointLight light,vec3 normal,vec3 worldPos,vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - worldPos);
    float diff = max(dot(normal,lightDir),0.0f);
    vec3 reflectDir = reflect(-lightDir,normal);
    float spec = pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);

    float distance = length(light.position - worldPos);
    float attenuation = 1.0f/(light.constant +
                                light.linear * distance + 
                                light.quadratic * distance * distance);    // 计算点光源衰减率

    vec3 ambient = light.ambient*vec3(texture(material.diffuse,TexCoords)) * attenuation;
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,TexCoords)) * attenuation;
    vec3 specular = light.specular * spec * vec3(texture(material.specular,TexCoords)) * attenuation;

     return ambient + diffuse + specular;
}

vec3 CalcSpotLight(SpotLight light,vec3 normal,vec3 worldPos,vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - worldPos);

    // 强度
    float theta = dot(lightDir,normalize(-light.direction));
    float epsilon = light.cutoff - light.outerCutoff;
    float intensity = clamp((theta-light.outerCutoff)/epsilon,0.0f,1.0f);

    // 衰减
    float distance = length(light.position - worldPos);
    float attenuation = 1.0f/(light.constant +
                                light.linear * distance + 
                                light.quadratic * distance * distance);    // 计算点光源衰减率

    float diff = max(dot(normal,lightDir),0.0f);
    vec3 reflectDir = reflect(-lightDir,normal);
    float spec = pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);


    vec3 ambient = light.ambient*vec3(texture(material.diffuse,TexCoords))*attenuation*intensity;
    vec3 diffuse = light.diffuse*diff*vec3(texture(material.diffuse,TexCoords))*attenuation*intensity;
    vec3 specular = light.specular*spec*vec3(texture(material.specular,TexCoords))*attenuation*intensity;

    return ambient + diffuse + specular; 
}


void main()
{
    vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - WorldPos);

    vec3 result;
    // direction light
    result += CalcDirLight(dirLight,norm,viewDir);

    // point light
    result += CalcPointLight(pointLight,norm,WorldPos,viewDir);

    // spot light
    result += CalcSpotLight(spotLight,norm,WorldPos,viewDir);

    FragColor = vec4(result,1.0f); 
}