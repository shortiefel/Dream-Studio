/* Start Header**********************************************************************************/
/*
@file    OpenGLEngine.vert
@author  Chia Yi da		c.yida@digipen.edu
@date    07/06/2021
*/
/* End Header **********************************************************************************/
  

#version 450 core
 
uniform mat3 uModel_to_NDC;
uniform int uID;
uniform mat3 Collider_Matrix;

layout (location=0) in vec2 aVertexPosition;
layout (location=1) in vec3 aVertexColor;
layout (location=2) in vec2 aVertexTexture;

layout (location=0) out vec3 vColor;
layout (location=1) out vec2 vTexture;


void main() {
	switch (uID) {
	case 0:
	// object position
		gl_Position = vec4(vec2(uModel_to_NDC * vec3(aVertexPosition, 1.f)), 0.0, 1.0);
		break;
	case 1:
	// collider position
		gl_Position = vec4(vec2(Collider_Matrix * vec3(aVertexPosition, 1.f)), 0.0, 1.0);
		break;
	}

	vColor = aVertexColor;
	vTexture = aVertexTexture;
}