#version 450 core

out vec4 fColor;
in float intensity;
in vec4 fragColour;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
	if (intensity > 0.95)
		fColor = fragColour * vec4(0.8,0.8,0.8 , 1) * texture(ourTexture, TexCoord);
	else if (intensity > 0.5)
		fColor = fragColour * vec4(0.7,0.7,0.7 , 1) * texture(ourTexture, TexCoord);
	else if (intensity > 0.25)
		fColor = fragColour * vec4(0.6,0.6,0.6 , 1) * texture(ourTexture, TexCoord);
	else
		fColor = fragColour * vec4(0.5,0.5,0.5 , 1) * texture(ourTexture, TexCoord);
}
