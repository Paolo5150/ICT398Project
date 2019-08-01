#version 430 core


out vec4 FragColor; 
in vec2 Textcoords;


uniform sampler2D diffuse0;
uniform sampler2D special0;
uniform sampler2D godrays;
uniform float timer;
uniform int underwater;
uniform float camLightDot;


void main()
{
   
    vec3 godRaysText = texture(godrays,Textcoords).rgb;
	vec3 distortion = texture(special0,Textcoords).rgb;
	
	vec2 dudvTexture = texture(special0,vec2(Textcoords.x + timer/100.0f,Textcoords.y + timer/100.0f) * 3.0).rg * 2.0 - 1.0;
	vec2 dudvTexture2 = texture(special0,vec2(Textcoords.x - timer/100.0f,Textcoords.y + timer/100.0f) *3.0).rg * 2.0 - 1.0;
	
	vec2 totalDistortion = (0.08 * dudvTexture + 0.08* dudvTexture2) * underwater;
	
	totalDistortion = clamp(totalDistortion,vec2(0,0),vec2(1,1));	
	
	 vec3 diffuseColor = texture(diffuse0,Textcoords + totalDistortion).rgb;
	 
	 diffuseColor = mix(diffuseColor,godRaysText,0.25 * camLightDot);
	 vec3 diffuseColorBluish = diffuseColor * vec3(0.6,0.64,0.8);
	
	 vec3 total = mix(diffuseColor,diffuseColorBluish,underwater);
	
	gl_FragColor =  vec4(total,1.0);


} 

