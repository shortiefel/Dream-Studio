/* Start Header**********************************************************************************/
/*
@file    Camera.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    19/06/2021
\brief
This file contains function declaration for camera

*/
/* End Header **********************************************************************************/

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "pch.hpp"
#include "Math/MathLib.hpp"
#include "Component/Graphics/TransformComponent.hpp"

namespace GraphicImplementation {
    struct Camera2D {
        //GLObject* pgo = nullptr; // pointer to game object that embeds camera
        Transform* transform = nullptr;

        //MathD::Vec2 right = MathD::Vec2{}, up = MathD::Vec2{};
        MathD::Mat3 world_to_ndc_xform = MathD::Mat3{};

        // window parameters
        GLint height{ 1000 }; // limited between 500 to 2000
        GLfloat ar = GLfloat{};

        //// window change parameters
        //GLint min_height{ 500 }, max_height{ 2000 };
        //// height is increasing if 1 and decreasing if -1
        //GLint height_chf_dir{ 1 };
        //// increments by which window height is changed per z key press
        //GLint height_chg_val{ 5 };

        // camera's speed
        GLfloat linear_speed{ 2.f };


        void init(GLFWwindow*, Transform*);
        void update(GLFWwindow*);
    };

    extern Camera2D camera2d;
}

#endif