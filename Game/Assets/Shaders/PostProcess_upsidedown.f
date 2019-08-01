#version 430 core


out vec4 FragColor; 
in vec2 Textcoords;


uniform sampler2D sceneTexture;

void main()
{     
	vec3 diffuseColor = texture(sceneTexture,Textcoords).rgb;
	gl_FragColor =  vec4(diffuseColor,1.0);
} 

