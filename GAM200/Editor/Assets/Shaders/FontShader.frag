/* Start Header**********************************************************************************/
/*
@file    FontShader.frag
@author  Goh See Yong Denise	g.seeyongdenise@digipen.edu
@date    28/10/2021
*/
/* End Header **********************************************************************************/

#version 450 core

uniform sampler2D text;
uniform vec3 textColor;

layout (location=0) in vec2 TexCoords;

layout (location=0) out vec4 color;

void main()
{    
    	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);	 
   	//colour
    	color = vec4(textColor, 1.0) * sampled;
}  