/* Start Header**********************************************************************************/
/*
@file    FontShader.frag
@author  Goh See Yong Denise	g.seeyongdenise@digipen.edu
@date    28/10/2021
*/
/* End Header **********************************************************************************/

#version 330 core
in vec2 TexCoords;
layout (location=0) out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);	 
    // red colour
    color = vec4(1.0, 0.0, 0.0, 1.0);
}  