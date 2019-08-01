#version 430 core
#define MAX_LIGHTS 10
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormals;
layout(location = 2) in vec2 inTextcoords;
layout(location = 3) in vec3 inColor;
layout(location = 4) in vec3 inTangent;
layout(location = 5) in vec3 inBinormal;



out vec2 Textcoords;
out float HeightRatio;


uniform mat4 u_mvp;
uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;






void main()
{

	HeightRatio = inPosition.y;
	gl_Position = u_mvp * vec4(inPosition,1);
	Textcoords = inTextcoords;
}