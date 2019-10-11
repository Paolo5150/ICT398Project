#version 430 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormals;
layout(location = 2) in vec2 inTextcoords;


out vec2 Textcoords;
out vec3 Normal;



uniform mat4 u_mvp;
uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;
uniform vec3 u_cameraPosition;
uniform vec4 u_clippingPlane;
uniform vec3 scale;
uniform vec3 position;


void main()
{

mat4 modelView = u_view * u_model;
vec3 scaleOrig = vec3(modelView[0][0],modelView[1][1],modelView[2][2]);

mat4 noRot = modelView;

noRot[0][0] = u_model[0][0];
noRot[0][1] = 0;
noRot[0][2] = 0;

noRot[1][0] = 0;
noRot[1][1] = u_model[1][1];
noRot[1][2] = 0;

noRot[2][0] = 0;
noRot[2][1] = 0;
noRot[2][2] = u_model[2][2];



gl_Position = u_projection * noRot * vec4(inPosition,1.0);



Textcoords = inTextcoords;


}