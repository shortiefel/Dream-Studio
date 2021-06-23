/* Start Header**********************************************************************************/
/*
@file    OpenGLEngine.frag
@author  Chia Yi da		c.yida@digipen.edu
@date    07/06/2021
\brief


*/
/* End Header **********************************************************************************/

#version 450 core

layout (location=0) in vec3 vInterpColor;

layout (location=0) out vec4 fFragColor;

void main () {
	// Have to be in vec4 for fragment
	fFragColor = vec4(vInterpColor, 1.0);
}