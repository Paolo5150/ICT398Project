#version 430 core

layout(location = 0) in vec3 inPosition;
layout(location = 2) in vec2 inTextcoords;


out vec2 Textcoords;



void main()
{


gl_Position = vec4(inPosition,1.0);

Textcoords = vec2(inTextcoords.x,  inTextcoords.y);


}