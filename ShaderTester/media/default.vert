
#version 400 core

layout( location = 0 ) in vec3 vPosition;
layout( location = 1 ) in vec4 vColour;
layout( location = 2 ) in vec3 vNormal;
layout (location = 3) in vec2 aTexCoord;

uniform mat4 mv_matrix;
uniform mat4 p_matrix;

out vec4 fragColour;
out vec2 TexCoord;


void
main()
{
	// view-space coordinate
    vec4 P = mv_matrix * vec4(vPosition,1.0);

	fragColour = vColour;

	gl_Position = p_matrix * P;
	TexCoord = aTexCoord;
}
