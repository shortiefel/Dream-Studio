/* Start Header**********************************************************************************/
/*
@file    OpenGLEngine.frag
@author  Chia Yi da		c.yida@digipen.edu
@date    07/06/2021
*/
/* End Header **********************************************************************************/

#version 450 core

uniform sampler2D uTex2d;

layout (location=0) in vec3 vColor;
layout (location=1) in vec2 vTexture;
//layout (location=2) in float vTextureIndex;

layout (location=0) out vec4 fColor;


void main () 
{
	// object - texture colour
	vec4 texColor = texture(uTex2d, vTexture);
	fColor = texColor;
	
	//fColor = vec4(vTextureIndex, vTextureIndex, vTextureIndex, 1.0);
}