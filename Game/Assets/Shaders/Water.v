#version 430 core
#define MAX_LIGHTS 10
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormals;
layout(location = 2) in vec2 inTextcoords;
layout(location = 4) in vec3 inTangent;
layout(location = 5) in vec3 inBinormal;

struct DirectionalLight
{
	mat4 lightSpace;
	vec3 position;
	vec3 rotation;
	vec3 diffuseColor;
	vec3 specularColor;
	float intensity;
	

};

struct PointLight
{
	vec3 position;
	vec3 rotation;
	vec3 diffuseColor;
	vec3 specularColor;
	float intensity;

};


out vec2 Textcoords;
out vec3 Normal;
out vec3 Tangent;
out vec3 Binormal;
out vec3 FragPosition;
out vec3 CameraPosition;
out float HasNormalMap;
out vec3 FragPositionTS;
out vec3 CameraPositionTS;
out vec3 dirLightsTS[MAX_LIGHTS];
out vec3 pointLightsTS[MAX_LIGHTS];
out vec4 clipSpace;

uniform mat4 u_mvp;
uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;
uniform vec3 u_cameraPosition;
uniform float u_hasNormalMap;



//All directional lights
layout (std140, binding = 1) uniform AllDirectionalLights
{
	DirectionalLight allDirLights[MAX_LIGHTS];
	int activeDirectionalLights;

};

//All point lights
layout (std140, binding = 2) uniform AllPointLights
{
	PointLight allPointLights[MAX_LIGHTS];
	int activePointLights;
};


void main()
{


	vec4 fragPos = u_model * vec4(inPosition,1);

	clipSpace =  u_mvp * vec4(inPosition,1.0);
	gl_Position = clipSpace;

	Textcoords = inTextcoords;
	HasNormalMap = u_hasNormalMap;
	Normal = normalize(mat3(transpose(inverse(u_model))) * normalize(inNormals));
	Tangent =  normalize(mat3(transpose(inverse(u_model))) * normalize(inTangent));
	Binormal =  normalize(mat3(transpose(inverse(u_model))) * normalize(inBinormal));

	CameraPosition = u_cameraPosition;
	FragPosition = fragPos.xyz;


	vec3 T = normalize(Tangent);
	vec3 B = normalize(Binormal);
	vec3 N = normalize(Normal);
	mat3 TBN = transpose(mat3(T,B,N));
	CameraPositionTS = TBN * CameraPosition;
	FragPositionTS = TBN * FragPosition;
	
	for(int i=0; i<MAX_LIGHTS;i++)
	{
		if(i >= activeDirectionalLights) break;	
		dirLightsTS[i] = TBN * allDirLights[i].rotation ;
	}
	
	for(int i=0; i<MAX_LIGHTS;i++)
	{
		if(i >= activePointLights) break;	
		pointLightsTS[i] = TBN * allPointLights[i].position ;
	}
	
	
	



}