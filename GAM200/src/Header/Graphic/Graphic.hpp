/*
This file has the functions declaration to be called by the graphic system
*/

#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "pch.hpp"
#include "Math/Matrix.hpp"
#include "Math/Vector.hpp"
//#include "Graphic/glslshader.hpp"

namespace Graphic {
    struct GLModel {
        GLenum primitive_type = GLenum{}; // which OpenGL primitive to be rendered?
        GLuint primitive_cnt = GLuint{};
        GLuint vaoid = GLuint{}; // handle to VAO
        GLuint draw_cnt = GLuint{}; // how many elements of primitive of type
    };

    struct GLObject {
        // orientation.x and orientation.y will be angle_disp and angle_speed respectively
        // both values specified in degrees
        MathD::Vec2 orientation = MathD::Vec2{};

        MathD::Vec2 scaling = MathD::Vec2{}; // scaling parameters
        MathD::Vec2 position = MathD::Vec2{}; // translatin vector coordinates
        MathD::Vec3 color = MathD::Vec3{};
        MathD::Mat3 mdl_to_ndc_xform = MathD::Mat3{}; // model (model-to-world) transform
        MathD::Mat3 mdl_xform = MathD::Mat3{}; // model-to-ndc transformation


        std::map<std::string, GLModel>::iterator mdl_ref;
        //std::map<std::string, GLSLShader>::iterator shd_ref;



        // function to initialize object's state
        void init(std::ifstream& ifs);

        // function to render object's model (specified by index mdl_ref)
        // uses model transformation matrix mdl_to_ndc_xform matrix
        // and shader program specified by index shd_ref
        void draw() const;

        // function to update the object's model transformation matrix
        void update(GLdouble delta_time);
    };
}

#endif