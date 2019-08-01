#version 330 core

layout(location=0) in vec3 inPosition;
layout(location = 6) in ivec4 bone_ids;     
layout(location = 7) in vec4 weights;


uniform mat4 u_mvp;
uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;
uniform vec4 u_clippingPlane;

const int MAX_BONES = 200;
uniform mat4 bones[MAX_BONES];


void main()
{

mat4 bone_transform = bones[bone_ids[0]] * weights[0];
		bone_transform += bones[bone_ids[1]] * weights[1];
		bone_transform += bones[bone_ids[2]] * weights[2];
		bone_transform += bones[bone_ids[3]] * weights[3];
			
	vec4 boned_position = bone_transform * vec4(inPosition, 1.0); // transformed by bones
vec4 fragPos = u_model * boned_position;

gl_ClipDistance[0] = dot( fragPos,u_clippingPlane);



gl_Position = u_mvp  * boned_position;
}