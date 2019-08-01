#version 430 core
#define MAX_LIGHTS 10

out vec4 FragColor; 

in vec2 Textcoords;
in vec3 Normal;
in vec3 FragPosition;
in vec3 CameraPosition;

struct Material
{
vec3 color;
float shininess;
float UVScale;
float reflectivness;
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
uniform vec3 AmbientLight;
uniform samplerCube cubemap0;

vec3 CalculatePointLights();
vec3 CalculateDirectionalLights();

void main()
{
   
   vec3 diffuseColor = texture(diffuse0,Textcoords * material.UVScale).rgb;
   
   vec3 CamToFrag = normalize(FragPosition - CameraPosition);
   vec3 reflection = reflect(CamToFrag,normalize(Normal));
   vec3 skyboxColor = texture(cubemap0,reflection).rgb;
   
   vec3 DirLights = CalculateDirectionalLights();
   vec3 PointLights = CalculatePointLights();

   vec3 total = (AmbientLight + DirLights + PointLights) * diffuseColor* material.color;
   
   vec3 mixTotal = mix(total,skyboxColor,material.reflectivness);
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
		vec3 lightdir = normalize(allDirLights[i].rotation);
		vec3 fragToCam = normalize(CameraPosition - FragPosition);
		vec3 reflection = reflect(lightdir,Normal);
		
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
		vec3 lightToFrag = FragPosition - allPointLights[i].position;
		float distance = length(lightToFrag);
		float attenuation = allPointLights[i].intensity / distance ;
		vec3 lightdir = normalize(lightToFrag);
		vec3 fragToCam = normalize(CameraPosition - FragPosition);
		vec3 reflection = reflect(lightdir,Normal);
		
		float spec = pow(max(dot(fragToCam, reflection), 0.0),material.shininess );
		vec3 specular =  spec * allPointLights[i].specularColor ; 
		totalColor += specular * attenuation;
		
		//diffuse
		
		
		float d = max(0.0,dot(-normalize(lightdir),Normal));
		vec3 diffuseColor = allPointLights[i].diffuseColor * d;		
		totalColor += diffuseColor * attenuation ;	
	}

	return totalColor;
}