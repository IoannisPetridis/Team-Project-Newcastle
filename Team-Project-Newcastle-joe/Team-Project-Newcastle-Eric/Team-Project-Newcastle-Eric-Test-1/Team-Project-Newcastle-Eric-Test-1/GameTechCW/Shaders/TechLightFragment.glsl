#version 400 core

uniform sampler2D diffuseTex;

uniform vec3  ambientColour;
uniform vec3  invLightDir;			//Directional Light
uniform vec3  cameraPos;
uniform float specularIntensity;

in Vertex	{
	vec3 worldPos;
	vec2 texCoord;
	vec4 colour;
	vec3 normal;
} IN;

out vec4 gl_FragColor;

const float levels = 3.0;

void main(void)	{
//Lighting Calculations
	vec3 normal 		= normalize(IN.normal);
	vec3 viewDir 		= normalize(cameraPos - IN.worldPos );
	vec3 halfDir 		= normalize(invLightDir + viewDir );
	float rFactor       = max(0.0, dot(halfDir , normal ));
	float dFactor       = max(0.0, dot(invLightDir , normal )) ;
    float sFactor       = pow(rFactor , specularIntensity );
	
	float level = floor(sFactor * levels);
	sFactor = level / levels;
	
	float level2 = floor(dFactor * levels);
	dFactor = level2 / levels;
	float level3 = floor(rFactor * levels);
	rFactor = level3 / levels;
	   
//Colour Computations
	vec4 texColour  = texture(diffuseTex, IN.texCoord);
	vec3 diffColour = IN.colour.rgb * texColour.rgb;
	vec3 specColour = min(diffColour + vec3(0.5f), vec3(1)); //Quick hack to approximate specular colour of an object, assuming the light colour is white
    vec3 col = ambientColour * diffColour 
			 + diffColour * dFactor
			 + specColour * sFactor* 0.33f;
		
//Output Final Fragment Colour
	gl_FragColor.rgb 	= col;
	gl_FragColor.a 		= IN.colour.a * texColour.a;
}