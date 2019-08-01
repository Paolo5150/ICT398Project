#version 430 core

layout(location =0 ) in vec3 inPosition;

out vec3 localPos;

uniform mat4 u_mvp;
uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;




void main()
{

localPos = inPosition;
mat4 viewNoTrans = u_view;
viewNoTrans[3][0] = 0;
viewNoTrans[3][1] = 0;
viewNoTrans[3][2] = 0;


vec4 position = u_projection * viewNoTrans * vec4(inPosition,1);
 gl_Position = position;
}