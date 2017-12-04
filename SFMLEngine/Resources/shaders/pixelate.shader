#shader vertex
void main()
{
	// transform the vertex position
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

	// transform the texture coordinates
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

	// forward the vertex color
	gl_FrontColor = gl_Color;
}

#shader fragment
uniform sampler2D texture;
uniform float pixel_threshold;

void main()
{
	float factor = 1.0 / (pixel_threshold + 0.001);
	vec2 pos = floor(gl_TexCoord[0].xy * factor + 0.5) / factor;
	gl_FragColor = texture2D(texture, pos) * gl_Color;
}
