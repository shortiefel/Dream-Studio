/* Start Header**********************************************************************************/
/*
@file    FontShader.frag
@author  Goh See Yong Denise	g.seeyongdenise@digipen.edu
@date    28/10/2021
*/
/* End Header **********************************************************************************/

#version 450 core

layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 TexCoords;

uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(vertex.xy, 120.0, 1.0);
    TexCoords = vertex.zw;
}  