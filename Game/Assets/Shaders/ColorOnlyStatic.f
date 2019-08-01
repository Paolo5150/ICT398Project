#version 330 core

layout (location = 0) out vec4 FragColor; 



struct Material
{
vec3 color;
};

uniform Material material;


void main()
{

FragColor =  vec4(material.color,1.0);




} 