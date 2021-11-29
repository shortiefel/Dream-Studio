/* Start Header**********************************************************************************/
/*
@file    Collision.frag
@author  Chia Yi da		c.yida@digipen.edu
@date    07/06/2021
*/
/* End Header **********************************************************************************/

#version 450 core

layout (location=0) in vec4 vColor;

layout (location=0) out vec4 fFragColor;


void main () 
{
	// Line colour is based on user
	fFragColor = vColor;
}