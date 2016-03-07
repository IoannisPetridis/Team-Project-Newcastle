#version 150

uniform samplerCube cubeTex;
uniform vec3 cameraPos;

in Vertex {
	vec3 normal;
} IN;

out vec4 gl_FragColor;

void main(void) {

	//gl_FragColor = mix(texture(cubeNightTex,normalize(IN.normal)),texture(cubeNightTex,normalize(IN.normal)),(1-fadeSkyValue));
	
	gl_FragColor = texture(cubeTex,normalize(IN.normal));

	
}