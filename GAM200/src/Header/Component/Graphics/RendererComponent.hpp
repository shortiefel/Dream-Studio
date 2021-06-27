/* Start Header**********************************************************************************/
/*
@file    RendererComponent.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    19/06/2021
\brief
This file contain the renderer2D struct to be used by the ECS and various system


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef RENDERER_COMPONENT_HPP
#define RENDERER_COMPONENT_HPP

//#include "pch.hpp"
//#include "Graphic/glslshader.hpp"
#include "Graphic/Graphic.hpp"
#include "Math/Matrix.hpp"

class GLSLShader;
struct Renderer2D {
	MathD::Mat3 mdl_to_ndc_xform;

	std::map<std::string, GraphicImplementation::GLModel>::iterator mdl_ref;
	std::map<std::string, GLSLShader>::iterator shd_ref;

	Renderer2D(std::map<std::string, GraphicImplementation::GLModel>::iterator m, std::map<std::string, GLSLShader>::iterator s) :
		mdl_ref{ m }, shd_ref{ s } {}
	Renderer2D() : mdl_ref{ GraphicImplementation::models.begin() }, shd_ref{ GraphicImplementation::shdrpgms.begin() } {}
};

#endif