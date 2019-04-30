
#version 430 core 

in vec3 Normal;
in vec2 TexCood;

out vec4 FragColor;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_height1;
uniform sampler2D test;
uniform sampler2D test1;

void main()
{
    FragColor = texture(texture_diffuse1,TexCood);
}