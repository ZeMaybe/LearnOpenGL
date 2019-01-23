
#version 430 core 

in vec3 vertexColor;
in vec2 texCood;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixValue;

out vec4 FragColor;

void main()
{
     FragColor = mix(texture(texture1,texCood),texture(texture2,texCood),mixValue); 
    //FragColor = texture(texture1,texCood);
    //  FragColor = texture(texture2,texCood);
}