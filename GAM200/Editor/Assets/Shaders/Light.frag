/* Start Header**********************************************************************************/
/*
@file    Light.frag
@author  Chia Yi da		c.yida@digipen.edu
@date    07/06/2021
*/
/* End Header **********************************************************************************/

#version 450 core

uniform sampler2D u_Textures[32];

layout (location=0) in vec4 vColor;
layout (location=1) in vec2 vTexture;
layout (location=2) in float vTextureIndex;

layout (location=0) out vec4 fColor;


void main () 
{
	// object - texture colour
    fColor = vColor;






}


// Ambient
/*
	float ambientStrength = uLightAmbient;
	vec3 ambient = ambientStrength * uLightColor;
	vec4 result = vec4(ambient, 1.0f);

    //fColor = result * texColor;

	int index = int(vTextureIndex);
	vec4 texColor = texture(u_Textures[0], vTexture) * vColor;
*/