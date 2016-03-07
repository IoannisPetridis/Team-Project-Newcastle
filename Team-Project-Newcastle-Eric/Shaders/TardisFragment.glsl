#version 150
uniform sampler2D diffuseTex;
uniform sampler2DShadow shadowTex1;
uniform sampler2D bumpTex;

uniform vec3 cameraPos;
uniform int lightSize;
uniform vec4 lightColour[70];
uniform vec3 lightPos[70];
uniform float lightRadius[70];
uniform float bright[70];
uniform vec3 isOn[70];
uniform float fadeValue;


in Vertex {
	vec4 colour;
	vec2 texCoord;
	vec3 normal;
	vec3 tangent;
	vec3 binormal;
	vec3 worldPos;
	vec4 shadowProj;
} IN;

out vec4 gl_FragColor;

void main(void){
	//base diffuse
	vec4 diffuse = texture(diffuseTex,IN.texCoord);
	mat3 TBN = mat3(IN.tangent,IN.binormal,IN.normal);
	vec3 normal = normalize(TBN*(texture(bumpTex,IN.texCoord).rgb * 2.0 -1.0));
	//---------------------------------
	vec3 incident = normalize(lightPos[0]-IN.worldPos);
		float lambert = max(0.0,dot(incident,normal));
		float dist = length(lightPos[0] - IN.worldPos);
		float atten = 1.0 - clamp(dist/lightRadius[0],0.0,1.0);
		
		//view vector
		vec3 viewDir = normalize(cameraPos - IN.worldPos);
		
		//half angle vector
		vec3 halfDir = normalize(incident + viewDir);

		//calculate the specular reflection
		float rFactor = max(0.0,dot(halfDir,normal));
		//shiny
		float sFactor =pow(rFactor,25.0);
		
		float shadow = 1.0; // New !
		if( IN.shadowProj . w > 0.0) { // New !
		shadow = textureProj ( shadowTex1 , IN.shadowProj );
		
		 //shadow = 0;
		}
		 lambert *= shadow; // New !
		
		vec3 colour = (diffuse.rgb * lightColour[0].rgb)*bright[0]*isOn[0];
		//add specularity
		colour += (lightColour[0].rgb * sFactor) * 0.33*isOn[0]; 
		// single light
		gl_FragColor += vec4(colour * atten * lambert, diffuse.a); //multiple light
	
		//gl_FragColor =vec4(shadow,0,0,1);
	//---------------------------------
	
	 for(int i=1;i<lightSize;i++)
	 {
		 incident = normalize(lightPos[i]-IN.worldPos);
		 lambert = max(0.0,dot(incident,normal));
		 dist = length(lightPos[i] - IN.worldPos);
		 atten = 1.0 - clamp(dist/lightRadius[i],0.0,1.0);
		
		 //view vector
		 viewDir = normalize(cameraPos - IN.worldPos);
		
		 //half angle vector
		 halfDir = normalize(incident + viewDir);

		 //calculate the specular reflection
		 rFactor = max(0.0,dot(halfDir,normal));
		 //shiny
		 sFactor =pow(rFactor,25.0);

		
		 colour = (diffuse.rgb * lightColour[i].rgb)*bright[i]*isOn[i];
	
		 //add specularity
		 colour += (lightColour[i].rgb * sFactor) * 0.33*isOn[i]; 
		 // single light
		 gl_FragColor += vec4(colour * atten * lambert, diffuse.a); //multiple light
	}
	
	// //ambient light
	 gl_FragColor.rgb += (diffuse.rgb * vec4(1,1,1,1).rgb) * 0.5;
	
	//fadeing
	//gl_FragColor.a=fadeValue;
	
}