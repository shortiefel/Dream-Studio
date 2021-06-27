/* Start Header**********************************************************************************/
/*
@file    Graphic.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    16/06/2021
\brief
This file has the functions declaration to be called by the graphic system


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/


#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "Graphic/glslshader.hpp" // for GLSLShader
#include "pch.hpp"
#include "Math/MathLib.hpp"

namespace GraphicImplementation {
    struct GLModel {
        GLenum primitive_type = GLenum{}; // which OpenGL primitive to be rendered?
        GLuint primitive_cnt = GLuint{};
        GLuint vaoid = GLuint{}; // handle to VAO
        GLuint draw_cnt = GLuint{}; // how many elements of primitive of type
    };

    //struct GLObject {
    //    // orientation.x and orientation.y will be angle_disp and angle_speed respectively
    //    // both values specified in degrees
    //    MathD::Vec2 orientation = MathD::Vec2{};

    //    MathD::Vec2 scaling = MathD::Vec2{}; // scaling parameters
    //    MathD::Vec2 position = MathD::Vec2{}; // translatin vector coordinates
    //    MathD::Vec3 color = MathD::Vec3{};
    //    MathD::Mat3 mdl_to_ndc_xform = MathD::Mat3{}; // model (model-to-world) transform
    //    MathD::Mat3 mdl_xform = MathD::Mat3{}; // model-to-ndc transformation

    //    // function to initialize object's state
    //    void init();

    //    // function to render object's model (specified by index mdl_ref)
    //    // uses model transformation matrix mdl_to_ndc_xform matrix
    //    // and shader program specified by index shd_ref
    //    void draw() const;

    //    // function to update the object's model transformation matrix
    //    void update(GLdouble delta_time);
    //};
    
    extern std::map<std::string, GLModel> models;
    extern std::map<std::string, GLSLShader> shdrpgms;
    //static std::map<std::string, GLObject> objects;

    void setup_vao();
    void setup_shdr();
    //void create_square_instance();
}

#endif