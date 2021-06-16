#ifndef RENDERER_COMPONENT_HPP
#define RENDERER_COMPONENT_HPP

//#include "Math/Matrix.hpp"

#include "Graphic/Graphic.hpp"
#include "Graphic/glslshader.hpp"
#include "Math/Matrix.hpp"
#include "pch.hpp"

struct Renderer2D {
	MathD::Mat3 mdl_to_ndc_xform;

	std::map<std::string, GraphicImplementation::GLModel>::iterator mdl_ref;
	std::map<std::string, GLSLShader>::iterator shd_ref;

	Renderer2D(std::map<std::string, GraphicImplementation::GLModel>::iterator m, std::map<std::string, GLSLShader>::iterator s) :
		mdl_ref{ m }, shd_ref{ s } {}
	Renderer2D() : mdl_ref{ GraphicImplementation::models.begin() }, shd_ref{ GraphicImplementation::shdrpgms.begin() } {}
};

#endif