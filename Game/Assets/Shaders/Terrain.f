#version 430 core
#define MAX_LIGHTS 10

out vec4 FragColor; 

in vec2 Textcoords;
in vec3 Normal;
in vec3 Tangent;
in vec3 Binormal;
in vec3 FragPosition;
in vec3 CameraPosition;
in vec3 FragPositionTS;
in vec3 CameraPositionTS;
in float HasNormalMap;
in vec3 dirLightsTS[MAX_LIGHTS];
in vec3 pointLightsTS[MAX_LIGHTS];
in vec4 fragLightSpaces[MAX_LIGHTS];
in vec4 clipSpace;
in float HeightRatio;
in vec3 vertexColor;
in float fogVisibility;

struct Material
{
vec3 color;
float shininess;
float UVScale;
float height_scale;
};

// Light buffers

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

uniform Material material;
uniform sampler2D diffuse0; //Sand
uniform sampler2D height0;


uniform sampler2D shadowMap[MAX_LIGHTS]; //shadowmap

uniform int shadowMapCount;

uniform vec3 AmbientLight;


vec3 CalculatePointLights();
vec3 CalculateDirectionalLights();
vec3 NormalToUse;

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{ 
    float height =  texture(height0, texCoords).r;    
    vec2 p = viewDir.xy / viewDir.z * (height * material.height_scale);
    return texCoords - p;    
}



float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}


float ShadowCalculation();

void main()
{

   vec3 DirLights =  CalculateDirectionalLights();   
   vec3 PointLights = CalculatePointLights();
   
   	float shadowFactor = ShadowCalculation();
	float shadowAlpha = max(0.0,(1000 - length(FragPosition - CameraPosition)) / 1000.0);
	float shadowColor = (1.0  - shadowFactor* shadowAlpha )  ;
   
   vec3 viewDir = FragPositionTS - CameraPositionTS;
   vec2 TextureCoordinates = ParallaxMapping(Textcoords,viewDir);
   vec3 terrainColor =  texture(diffuse0,TextureCoordinates * material.UVScale).rgb;
   vec3 total =  shadowColor *(AmbientLight + DirLights + PointLights) * terrainColor* material.color;

   vec3 mixFog = mix(vec3(0.321,0.3529,0.3550),total,fogVisibility);
	gl_FragColor =  vec4(total,1.0);

} 

float ShadowCalculation()
{

	float shadow = 0;
	for(int i=0; i < MAX_LIGHTS; i++) 
	{
	if(i >= shadowMapCount) break;
		vec3 projCoords = fragLightSpaces[i].xyz / fragLightSpaces[i].w;

		projCoords = projCoords * 0.5 + 0.5;

		float closestDepth = texture(shadowMap[i], projCoords.xy).r; 

		float currentDepth = projCoords.z;

		float bias = 0.002;
		shadow += currentDepth - bias > closestDepth  ? 0.7 : 0.0; 
	

	}

    return shadow;
} 


vec3 CalculateDirectionalLights()
{
	vec3 totalColor = vec3(0,0,0);

	int i = 0;
	for(; i < MAX_LIGHTS; i++)
	{
	if(i >= activeDirectionalLights) break;

		//Specular
		vec3 lightdir = normalize(dirLightsTS[i]);
		vec3 fragToCam = normalize(CameraPositionTS - FragPositionTS);
		vec3 reflection = reflect(lightdir,NormalToUse);
		float spec = pow(max(dot(fragToCam, reflection), 0.0),material.shininess );
		vec3 specular =  spec * allDirLights[i].specularColor ; 
		
		totalColor+=specular;
		
		//diffuse
		lightdir = normalize(allDirLights[i].rotation);
		float d = max(0.0,dot(-lightdir,Normal));
		vec3 diffuseColor = allDirLights[i].diffuseColor * d;
		diffuseColor *= allDirLights[i].intensity;
		totalColor += diffuseColor;	
	
	}
	return totalColor;
}

vec3 CalculatePointLights()
{
	vec3 totalColor = vec3(0,0,0);

	int i = 0;
	for(; i < MAX_LIGHTS; i++)
	{
	if(i >= activePointLights) break;
	
		//Specular

		//diffuse
		vec3 lightToFrag = FragPosition - allPointLights[i].position;
		vec3 lightdir = normalize(lightToFrag);

		float distance = length(lightToFrag);
		float attenuation = allPointLights[i].intensity / distance ;
		
		float d = max(0.0,dot(-normalize(lightdir),Normal));
		vec3 diffuseColor = allPointLights[i].diffuseColor * d;		
		totalColor += diffuseColor * attenuation ;	
	}

	return totalColor;
}