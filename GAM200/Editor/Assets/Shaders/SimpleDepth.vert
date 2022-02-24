/* Start Header**********************************************************************************/
/*
@file    SimpleDepth.vert
@author  Chia Yi da		c.yida@digipen.edu
@date    02/06/22

Used for depth calculation for Shadow Mapping (Lights and Shadows)
*/
/* End Header **********************************************************************************/
 
#version 450 core

uniform mat4 uLightSpaceMatrix;
uniform mat4 uLightProjection;
uniform mat4 uLightView;

layout (location=0) in vec2 aVertexPosition;
layout (location=1) in vec4 aVertexColor;
layout (location=2) in vec2 aVertexTexture;
layout (location=3) in float aTextureIndex;
layout (location=4) in vec2 aTPosition;
layout (location=5) in vec2 aTScale;
layout (location=6) in float aTRotation;

layout (location=1) out vec2 vTexture;

out VS_OUT {
    vec3 fragPos;
    vec3 normal;
    vec2 texCoords;
    vec4 fragPosLightSpace;
} vs_out;


void main() 
{
	// Compute uModel_to_NDC matrix
	mat4 uModel_to_NDC = mat4(
		// Translate
		mat4(vec4(1.f, 0.f, 0.f, 0.f),
			 vec4(0, 1.f, 0.f, 0.f),
			 vec4(0, 0.f, 1.f, 0.f),
			 vec4(aTPosition.x, aTPosition.y, 0.0f, 1.f))
		*
		// Rotate
		mat4(vec4(cos(aTRotation), sin(aTRotation), 0.f, 0.f),
			 vec4(-sin(aTRotation), cos(aTRotation), 0.f, 0.f),
			 vec4(0.f, 0.f, 1.f, 0.f),
			 vec4(0.f, 0.f, 0.f, 1.f))
		*
		// Scale
		mat4(vec4(aTScale.x, 0.f, 0.f, 0.f),
			 vec4(0.f, aTScale.y, 0.f, 0.f),
			 vec4(0.f, 0.f, 1.f, 0.f),
			 vec4(0.f, 0.f, 0.f, 1.f))
		);


	vs_out.fragPos = vec3(uModel_to_NDC * vec4(aVertexPosition, 0.f, 1.f));
    vs_out.normal = transpose(inverse(mat3(uModel_to_NDC))) * vec3(0.f, 1.f, 0.f);
    vs_out.texCoords = aVertexTexture;
    vs_out.fragPosLightSpace = uLightSpaceMatrix * vec4(vs_out.fragPos, 1.0);
	
    gl_Position = uLightProjection * uLightView * vec4(vs_out.fragPos, 1.0);

	//gl_Position = vec4(vec2(uLightMatrix * uModel_to_NDC * vec4(aVertexPosition, 0.f, 1.f)), 0.0, 1.0);
}