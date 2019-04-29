
#version 430 core 
 
in vec2 texCood;
out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixValue;

void main()
{
     FragColor = mix(texture(texture1,texCood),texture(texture2,texCood),mixValue);
	 //FragColor = texture(texture1,texCood);
}