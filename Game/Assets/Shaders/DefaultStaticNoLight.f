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


uniform Material material;
uniform sampler2D diffuse0;
uniform samplerCube cubemap0;

uniform vec3 AmbientLight;

void main()
{
   
    vec3 diffuseColor = texture(diffuse0,Textcoords * material.UVScale).rgb;
    vec3 CamToFrag = normalize(FragPosition - CameraPosition);
    vec3 reflection = reflect(CamToFrag,Normal);
    vec3 skyboxColor = texture(cubemap0,reflection).rgb;
   
    vec3 total =  diffuseColor* material.color;
   
    vec3 mixTotal = mix(total,skyboxColor,material.reflectivness);
	gl_FragColor =  vec4(mixTotal,1.0);


} 

