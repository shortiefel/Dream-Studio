// @file    OpenGLEngine.frag
// @author  c.yida@digipen.edu
// @date    07/06/2021

#version 450 core

layout (location=0) in vec3 vInterpColor;

layout (location=0) out vec4 fFragColor;

void main () {
	// Have to be in vec4 for fragment
	fFragColor = vec4(vInterpColor, 1.0);
}