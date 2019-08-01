#version 330 core

layout(location=0) in vec3 inPosition;


uniform mat4 u_mvp;
uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;
uniform vec4 u_clippingPlane;


void main()
{
vec4 fragPos = u_model * vec4(inPosition,1);

gl_ClipDistance[0] = dot( fragPos,u_clippingPlane);



gl_Position = u_projection * u_view * fragPos;
}