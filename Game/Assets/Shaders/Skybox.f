#version 430 core

out vec4 FragColor; 
in vec3 textCoords;


uniform samplerCube cubemap0;


void main()
{
 
 vec3 cubemap = texture(cubemap0,textCoords).rgb;
FragColor =  vec4(cubemap,1.0);


} 