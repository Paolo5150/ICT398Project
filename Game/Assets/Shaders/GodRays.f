#version 430 core
out vec4 color;
uniform sampler2D diffuse0;


const int NUM_SAMPLES = 100 ;
in vec2 Textcoords;

void main()
    {	
		float exposure = 0.0034;
		float decay = 1.0;
		float density = 0.84;
		float weight = 5.65;
		vec2 lightPositionOnScreen = vec2(0.5,0.5);
    	vec2 deltaTextCoord = vec2( Textcoords - lightPositionOnScreen.xy );
		vec2 textureCoords = Textcoords;
    	deltaTextCoord *= 1.0 /  float(NUM_SAMPLES) * density;
    	float illuminationDecay = 1.0;
	
	
    	for(int i=0; i < NUM_SAMPLES ; i++)
        {
                 textureCoords -= deltaTextCoord;
                 vec4 sam = texture2D(diffuse0, textureCoords );
			
                 sam *= illuminationDecay * weight;

                 color += sam;

                 illuminationDecay *= decay;
         }
         color *= exposure;
    }