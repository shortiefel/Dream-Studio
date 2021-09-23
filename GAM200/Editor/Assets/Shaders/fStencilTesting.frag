/* Start Header**********************************************************************************/
/*
@file    fSingleTesting.frag
@author  Chia Yi da		c.yida@digipen.edu
@date    13/09/2021
*/
/* End Header **********************************************************************************/

#version 450 core

layout (location=0) in vec3 vColor;

layout (location=0) out vec4 fFragColor;

void main () {
	// red colour
	fFragColor = vec4(1.0, 0.0, 0.0, 1.0);
}