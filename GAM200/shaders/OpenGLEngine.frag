/* Start Header**********************************************************************************/
/*
@file    OpenGLEngine.frag
@author  Chia Yi da		c.yida@digipen.edu
@date    07/06/2021
*/
/* End Header **********************************************************************************/

#version 450 core

uniform sampler2D uTex2d;

layout (location=0) in vec3 vInterpColor;
layout (location=1) in vec2 vTexture;

layout (location=0) out vec4 fFragColor;

void main () {
	vec4 texColor = texture(uTex2d, vTexture);
	fFragColor = texColor;
}