/* Start Header**********************************************************************************/
/*
@file    OpenGLEngine.frag
@author  Chia Yi da		c.yida@digipen.edu
@date    07/06/2021
*/
/* End Header **********************************************************************************/

#version 450 core

uniform sampler2D uTex2d;
uniform int uID;

layout (location=0) in vec3 vInterpColor;
layout (location=1) in vec2 vTexture;

layout (location=0) out vec4 fFragColor;


void main () {
	switch (uID) { 
	case 0:
	// object - texture colour
		vec4 texColor = texture(uTex2d, vTexture);
		fFragColor = texColor;
		break;
	case 1:
	// collider - red colour
		fFragColor = vec4(1.0, 0.0, 0.0, 1.0);
		break;
	}
}