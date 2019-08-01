#version 430 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormals;
layout(location = 2) in vec2 inTextcoords;


out vec2 Textcoords;
out vec3 Normal;

out vec3 FragPosition;
out vec3 CameraPosition;

uniform mat4 u_mvp;
uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;
uniform vec3 u_cameraPosition;
uniform vec4 u_clippingPlane;



void main()
{


vec4 fragPos = u_model * vec4(inPosition,1);
gl_ClipDistance[0] = dot( fragPos,u_clippingPlane);
gl_Position = u_projection * u_view * fragPos;

Textcoords = inTextcoords;
Normal = normalize(mat3(transpose(inverse(u_model))) * normalize(inNormals));
CameraPosition = u_cameraPosition;
FragPosition = fragPos.xyz;
}