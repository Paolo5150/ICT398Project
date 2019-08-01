#version 430 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormals;
layout(location = 2) in vec2 inTextcoords;
layout(location = 4) in vec3 inTangent;
layout(location = 5) in vec3 inBinormal;
layout(location = 6) in ivec4 bone_ids;     
layout(location = 7) in vec4 weights;


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

const int MAX_BONES = 200;
uniform mat4 bones[MAX_BONES];

void main()
{


	mat4 bone_transform = bones[bone_ids[0]] * weights[0];
		bone_transform += bones[bone_ids[1]] * weights[1];
		bone_transform += bones[bone_ids[2]] * weights[2];
		bone_transform += bones[bone_ids[3]] * weights[3];
			
	vec4 boned_position = bone_transform * vec4(inPosition, 1.0); // transformed by bones
	
vec4 fragPos = u_model * vec4(inPosition, 1.0);
gl_ClipDistance[0] = dot( fragPos,u_clippingPlane);
gl_Position = u_mvp  * boned_position;

Normal = normalize( u_model * bone_transform* vec4(normalize(inNormals),0.0)).xyz;


CameraPosition = u_cameraPosition;
FragPosition = fragPos.xyz;


}