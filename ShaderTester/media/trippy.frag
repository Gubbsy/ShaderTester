#version 450 core

out vec4 fColor;
in float intensity;
in vec4 fragColour;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    //fColor = vec4(0.5, 0.4, 0.8, 1.0);
	//fColor = fragColour;
	vec3 colour = vec3(0.);
	colour = vec3(sin(intensity), cos(intensity), tan(intensity));
	vec4 col = vec4(colour, 1.0);

	fColor = texture(ourTexture, TexCoord) * col;
}
