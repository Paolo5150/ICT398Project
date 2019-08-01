#version 430 core
#define MAX_LIGHTS 10
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormals;
layout(location = 2) in vec2 inTextcoords;
layout(location = 3) in vec3 inColor;
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
out float HeightRatio;
out vec4 fragLightSpaces[MAX_LIGHTS];
out vec3 vertexColor;
out float fogVisibility;

uniform mat4 u_mvp;
uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;
uniform vec3 u_cameraPosition;
uniform vec4 u_clippingPlane;
uniform float u_maxHeight;
uniform int shadowMapCount;

const float fogDensity = 0.0007;
const float fogGradient = 1.5;


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

	vertexColor = inColor;
	vec4 fragPos = u_model * vec4(inPosition,1);
	HeightRatio = inPosition.y;
	gl_ClipDistance[0] = dot( fragPos,u_clippingPlane);

	clipSpace =  u_mvp * vec4(inPosition,1.0);
	gl_Position = clipSpace;

	Textcoords = inTextcoords;

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
	
	vec3 viewPosition = (u_view * fragPos).xyz;
	float dist = length(viewPosition);
	fogVisibility = exp(-pow(dist * fogDensity,fogGradient));
	fogVisibility = clamp(fogVisibility,0.0,1.0);
	
	fragLightSpaces[0] = allDirLights[0].lightSpace * vec4(fragPos.xyz,1.0);

	
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