
#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
uniform vec4 timeColor;

out vec4 vertexColor;

void main()
{
    gl_Position = vec4(aPos,1.0f);        
    vertexColor = vec4(aColor,1.0f);
    //vertexColor *= timeColor;
}