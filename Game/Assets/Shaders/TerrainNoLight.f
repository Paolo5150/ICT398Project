#version 430 core
#define MAX_LIGHTS 10

out vec4 FragColor; 

in vec2 Textcoords;
in float HeightRatio;

struct Material
{
vec3 color;
float shininess;
float UVScale;
};



uniform Material material;
uniform sampler2D diffuse0; //Sand
uniform sampler2D diffuse1; //grass
uniform sampler2D diffuse2; //Rock

uniform vec3 AmbientLight;







vec3 GenerateTerrainColor()
{
    vec3 terrainColor = vec3(0.0, 0.0, 0.0);
    float height = max(0.0f,(HeightRatio));;
    float regionMin = 0.0;
    float regionMax = 1.0;
    float regionRange = 0.0;
    float regionWeight = 0.0;
    

    regionMin = -0.5f;
    regionMax = 0.4f;
    regionRange = regionMax - regionMin;
    regionWeight = (regionRange - abs(height - regionMax)) / regionRange;
    regionWeight = max(0.0, regionWeight);
    terrainColor += regionWeight * texture(diffuse0,Textcoords * material.UVScale).rgb;
	

    regionMin = 0.5f;
    regionMax = 1.0f;
    regionRange = regionMax - regionMin;
    regionWeight = (regionRange - abs(height - regionMax)) / regionRange;
    regionWeight = max(0.0, regionWeight);
    terrainColor += regionWeight * texture(diffuse2,Textcoords * material.UVScale).rgb;
	
	
    regionMin = 0.1f;
    regionMax = 0.4f;
    regionRange = regionMax - regionMin;
    regionWeight = (regionRange - abs(height - regionMax)) / regionRange;
    regionWeight = max(0.0, regionWeight);
	
    terrainColor += regionWeight * texture(diffuse1,Textcoords * material.UVScale).rgb;

    return terrainColor;
}


void main()
{
   
	vec3 colorRatio = vec3(max(0.4,HeightRatio));     
  
   vec3 terrainColor =  GenerateTerrainColor();
   vec3 total =   colorRatio * terrainColor* material.color;

	gl_FragColor =  vec4(total,1.0);

} 

