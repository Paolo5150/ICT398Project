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

struct Material
{
vec3 color;
float shininess;
float UVScale;
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
uniform sampler2D diffuse0;
uniform sampler2D normal0;
uniform vec3 AmbientLight;

vec3 NormalToUse;
vec3 FragPosToUse;
vec3 CamPosToUse;

vec3 CalculatePointLights();
vec3 CalculateDirectionalLights();

void main()
{
   
   vec3 diffuseColor = texture(diffuse0,Textcoords).rgb;

    vec3 normalMap = texture(normal0,Textcoords * material.UVScale).rgb *2.0 -1.0;
   
	NormalToUse = normalize(normalMap);
	FragPosToUse = FragPositionTS;
	CamPosToUse = CameraPositionTS;

   
   vec3 DirLights = CalculateDirectionalLights();
   vec3 PointLights = CalculatePointLights();

   vec3 total = (AmbientLight + DirLights + PointLights) * diffuseColor* material.color;
	gl_FragColor =  vec4(total,1.0);

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
		vec3 fragToCam = normalize(CamPosToUse - FragPosToUse);
		vec3 reflection = reflect(lightdir,NormalToUse);
		
		float spec = pow(max(dot(fragToCam, reflection), 0.0),material.shininess );
		vec3 specular =  spec * allDirLights[i].specularColor ; 
		totalColor+=specular;
		
		//diffuse
		lightdir = normalize(dirLightsTS[i]);
		float d = max(0.0,dot(-lightdir,NormalToUse));
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
		vec3 lightToFrag = FragPosToUse - pointLightsTS[i];
		float distance = length(lightToFrag);
		float attenuation = allPointLights[i].intensity / distance ;
		vec3 lightdir = normalize(lightToFrag);
		vec3 fragToCam = normalize(CamPosToUse - FragPosToUse);
		vec3 reflection = reflect(lightdir,NormalToUse);
		
		float spec = pow(max(dot(fragToCam, reflection), 0.0),material.shininess );
		vec3 specular =  spec * allPointLights[i].specularColor ; 
		totalColor += specular * attenuation;
		
		//diffuse
		
		
		float d = max(0.0,dot(-normalize(lightdir),NormalToUse));
		vec3 diffuseColor = allPointLights[i].diffuseColor * d;		
		totalColor += diffuseColor * attenuation ;	
	}

	return totalColor;
}