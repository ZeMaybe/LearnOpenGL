
#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCood;

uniform mat4 transform;

out vec3 vertexColor;
out vec2 texCood;

void main()
{
    gl_Position = transform*vec4(aPos,1.0f);        

    vertexColor = aColor;
    texCood = aTexCood;
}