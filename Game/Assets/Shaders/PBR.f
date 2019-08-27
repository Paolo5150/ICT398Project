#version 430 core
#define MAX_LIGHTS 10

out vec4 FragColor;

in vec2 Textcoords;
in vec3 Normal;
in vec3 Tangent;
in vec3 Binormal;
in vec3 FragPositionTS;
in vec3 CameraPositionTS;
in vec3 dirLightsTS[MAX_LIGHTS];
in vec3 pointLightsTS[MAX_LIGHTS];
in vec3 FragPosition;
in vec3 CameraPosition;

// material parameters
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

uniform sampler2D albedoMap;
uniform sampler2D normalMap;
uniform sampler2D metallicMap;
uniform sampler2D roughnessMap;
uniform sampler2D aoMap;
uniform samplerCube cubemap0;
uniform Material material;
uniform vec3 camPos;
uniform vec3 AmbientLight;

const float PI = 3.14159265359;
  
float DistributionGGX(vec3 N, vec3 H, float roughness);
float GeometrySchlickGGX(float NdotV, float roughness);
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness);
vec3 fresnelSchlick(float cosTheta, vec3 F0);
vec3 CalculatePointLights(vec3 N, vec3 V, vec3 F0, vec3 albedo, float metallic, float roughness);
vec3 CalculateDirectionalLights(vec3 N, vec3 V, vec3 F0, vec3 albedo, float metallic, float roughness);

float computeFresnelTerm(float fZero, vec3 vSurfaceToViewerDirection, vec3 vSurfaceNormal)
{
	float baseValue = 1.0 - dot(vSurfaceToViewerDirection, vSurfaceNormal);
	float exponential = pow(baseValue, 5.0) ;
	float fresnel = exponential + fZero * (1.0 - exponential) ;

	return fresnel ;
}

void main()
{		
	vec3 albedo     = pow(texture(albedoMap, Textcoords).rgb, vec3(2.2,2.2,2.2));
    vec3 normal     = texture(normalMap,Textcoords).rgb *2.0 -1.0;
    float metallic  = texture(metallicMap, Textcoords).r;
    float roughness = texture(roughnessMap, Textcoords).r;
    float ao        = texture(aoMap, Textcoords).r;
	
	
    vec3 N = normalize(normal);
    vec3 V = normalize(CameraPositionTS - FragPositionTS);
	
	vec3 CamToFrag = normalize(FragPosition - CameraPosition);
	vec3 reflection = reflect(CamToFrag,normalize(Normal));
	vec3 skyboxColor = texture(cubemap0,reflection).rgb * roughness * metallic;

    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedo, metallic);
	           
    // reflectance equation
    vec3 Lo = CalculatePointLights(N, V, F0, albedo, metallic, roughness); 
	
	Lo += CalculateDirectionalLights(N, V, F0, albedo, metallic, roughness); 
  
	vec3 rgbReflection = skyboxColor ;
	rgbReflection *= albedo * metallic ;
	rgbReflection *= computeFresnelTerm(0.5, -CamToFrag, normalize(Normal)) ; ;
	rgbReflection = min(rgbReflection, skyboxColor) ; // conservation of energy
	
    vec3 ambient = AmbientLight  * ao;
    vec3 color = ambient + Lo + rgbReflection ;
	
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2));  
   
    FragColor = vec4(color, 1.0);
}  

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a      = roughness*roughness;
    float a2     = a*a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;
	
    float num   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
	
    return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float num   = NdotV;
    float denom = NdotV * (1.0 - k) + k;
	
    return num / denom;
}
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2  = GeometrySchlickGGX(NdotV, roughness);
    float ggx1  = GeometrySchlickGGX(NdotL, roughness);
	
    return ggx1 * ggx2;
}

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}  

vec3 CalculateDirectionalLights(vec3 N, vec3 V, vec3 F0, vec3 albedo, float metallic, float roughness)
{
    vec3 Lo = vec3(0.0);
	
	for(int i=0; i < MAX_LIGHTS; i++)
	{
		if(i >= activeDirectionalLights) break;
		
		  // calculate per-light radiance
		vec3 L = -normalize(dirLightsTS[i]);
		
		vec3 H = normalize(V + L);
		vec3 radiance     = allDirLights[i].diffuseColor * allDirLights[i].intensity;        
			
			// cook-torrance brdf
		float NDF = DistributionGGX(N, H, roughness);        
		float G   = GeometrySmith(N, V, L, roughness);      
		vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);       
			
		vec3 kS = F;
		vec3 kD = vec3(1.0) - kS;
		kD *= 1.0 - metallic;	  
			
		vec3 numerator    = NDF * G * F;
		float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0);
		vec3 specular     = allDirLights[i].intensity * allDirLights[i].specularColor * allDirLights[i].intensity * numerator / max(denominator, 0.001);  
		
		float NdotL = max(dot(N, L), 0.0);                
		Lo += (kD * albedo / PI + specular) * radiance * NdotL; 
	}
	return Lo;
}

vec3 CalculatePointLights(vec3 N, vec3 V, vec3 F0, vec3 albedo, float metallic, float roughness)
{
    vec3 Lo = vec3(0.0);
	
	for(int i=0; i < MAX_LIGHTS; i++)
	{
		if(i >= activePointLights) break;
		
		  // calculate per-light radiance
		vec3 L = normalize(pointLightsTS[i] - FragPositionTS);
		
		vec3 H = normalize(V + L);
		float distance    = length(pointLightsTS[i] - FragPositionTS);
		float attenuation = allPointLights[i].intensity / (distance * distance);
		
		if(attenuation < 0.001) attenuation = 0;
		vec3 radiance     = allPointLights[i].diffuseColor * attenuation;        
			
			// cook-torrance brdf
		float NDF = DistributionGGX(N, H, roughness);        
		float G   = GeometrySmith(N, V, L, roughness);      
		vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);       
			
		vec3 kS = F;
		vec3 kD = vec3(1.0) - kS;
		kD *= 1.0 - metallic;	  
			
		vec3 numerator    = NDF * G * F;
		float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0);
		vec3 specular     = attenuation * allPointLights[i].intensity * allPointLights[i].specularColor * numerator / max(denominator, 0.001);  
				
			// add to outgoing radiance Lo
		float NdotL = max(dot(N, L), 0.0);                
		Lo += (kD * albedo / PI + specular) * radiance * NdotL; 
	}
	return Lo;
}