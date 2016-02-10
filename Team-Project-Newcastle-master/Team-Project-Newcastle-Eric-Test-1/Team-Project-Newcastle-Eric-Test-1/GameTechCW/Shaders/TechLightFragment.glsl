#version 150 core

uniform sampler2D diffuseTex;
uniform sampler2D bumpTex;

uniform vec3  ambientColour;
uniform vec3  invLightDir;			//Directional Light
uniform vec3  cameraPos;
uniform float specularIntensity;

uniform int lightSize;
uniform vec4 lightColour[20];
uniform vec3 lightPos[20];
uniform float lightRadius[20];
uniform float bright[20];
uniform vec3 isOn[20];

in Vertex	{
	vec3 worldPos;
	vec2 texCoord;
	vec4 colour;
	vec3 normal;
	vec3 tangent;
	vec3 binormal;
} IN;

out vec4 gl_FragColor;

void main(void)	{
//Lighting Calculations

	// mat3 TBN = mat3(IN.tangent,IN.binormal,IN.normal);
	// vec3 normal = normalize(TBN * (texture(bumpTex,IN.texCoord).rgb*2.0-1.0));
//Original
	// vec3 incident = normalize(lightPos[0]-IN.worldPos);
	 vec3 normal 		= normalize(IN.normal);
	 vec3 viewDir 		= normalize(cameraPos - IN.worldPos );
	 vec3 halfDir 		= normalize(invLightDir + viewDir );
	 float rFactor       = max(0.0, dot(halfDir , normal ));
	
	 float dFactor       = max(0.0, dot(invLightDir , normal )) ;
     float sFactor       = pow(rFactor , specularIntensity );
	 
	 vec3 incident;
	 float dist;
	 float atten;
	   
// //Colour Computations
	 vec4 texColour  = texture(diffuseTex, IN.texCoord);
	 vec3 diffColour = IN.colour.rgb * texColour.rgb;
	 vec3 specColour = min(diffColour + vec3(0.5f), vec3(1)); //Quick hack to approximate specular colour of an object, assuming the light colour is white
     vec3 col =  (diffColour * dFactor) + (specColour * sFactor * 0.33f); 
	 
	for(int i=0;i<lightSize;i++)
	{
	  incident 		= normalize(lightPos[i]-IN.worldPos);
	  normal 		= normalize(IN.normal);
	  //normal = normalize(TBN * (texture(bumpTex,IN.texCoord).rgb*2.0-1.0));
	  viewDir 		= normalize(cameraPos - IN.worldPos );
	  halfDir 		= normalize(incident + viewDir );
	  rFactor       = max(0.0, dot(halfDir , normal ));
	  
	  dist = length(lightPos[i] - IN.worldPos);
	  atten = 1.0 - clamp(dist/lightRadius[i],0.0,1.0);
	  
	  dFactor       = max(0.0, dot(incident , normal )) ;
      sFactor       = pow(rFactor , specularIntensity );
	 
// //Colour Computations
	  texColour  = texture(diffuseTex, IN.texCoord);
	  diffColour = IN.colour.rgb * texColour.rgb;
	  specColour = min(diffColour + vec3(0.5f), vec3(1)); //Quick hack to approximate specular colour of an object, assuming the light colour is white
	  col =col + (diffColour * dFactor* atten) + (specColour * sFactor * 0.33f);
	}
	//ambient		  
	col =col + ambientColour * diffColour ;
			  
// //Output Final Fragment Colour
	gl_FragColor.rgb 	= col;
	gl_FragColor.a 		= IN.colour.a * texColour.a;
}