#version 430 core
#define MAX_LIGHTS 10

out vec4 FragColor; 

in vec2 Textcoords;
in vec3 Normal;
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


uniform vec3 AmbientLight;

void main()
{
   
    vec3 diffuseColor = texture(diffuse0,Textcoords * material.UVScale).rgb;
   
    vec3 total =  diffuseColor* material.color;

	gl_FragColor =  vec4(total,1.0);


} 

