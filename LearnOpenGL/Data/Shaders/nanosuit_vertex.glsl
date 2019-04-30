
#version 430 core

layout (location = 0) in vec3 aPos; 
layout (location = 1) in vec3 aNormal; 
layout (location = 2) in vec2 aTexCood;

out vec3 Normal;
out vec2 TexCood;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    gl_Position = proj*view*model*vec4(aPos,1.0f);	
    TexCood = aTexCood;
    Normal = mat3(transpose(inverse(model)))*aNormal;	
}