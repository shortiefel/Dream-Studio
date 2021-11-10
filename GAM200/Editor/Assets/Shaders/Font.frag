/* Start Header**********************************************************************************/
/*
@file    Font.frag
@author  Chia Yi da		c.yida@digipen.edu
@date    1/11/2021
*/
/* End Header **********************************************************************************/

#version 450 core

uniform sampler2D u_FontTexture[32];

layout (location=0) in vec3 vColor;
layout (location=1) in vec2 vTexture;
layout (location=2) in float vTextureIndex;

layout (location=0) out vec4 fColor;


void main()
{    
	// object - font colour
	int index = int(vTextureIndex);
	vec4 c = vec4(1.0, 1.0, 1.0, texture(u_FontTexture[index], vTexture).r);
	fColor = vec4(vColor, 1.0) * c;
}