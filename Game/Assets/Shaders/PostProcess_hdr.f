#version 430 core


out vec4 FragColor; 
in vec2 Textcoords;


uniform sampler2D sceneTexture;

const float gamma     = 0.95;
const float exposure  = 1.2;
const float pureWhite = 1.0;

void main()
{     	

	
	vec3 color = texture(sceneTexture, Textcoords).rgb * exposure;

	float luminance = dot(color, vec3(0.2126, 0.7152, 0.0722));
	float mappedLuminance = (luminance * (1.0 + luminance/(pureWhite*pureWhite))) / (1.0 + luminance);

	vec3 mappedColor = (mappedLuminance / luminance) * color;

	FragColor = vec4(pow(mappedColor, vec3(1.0/gamma)), 1.0);
} 

