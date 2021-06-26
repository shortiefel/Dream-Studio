/* Start Header**********************************************************************************/
/*
@file    CameraComponent.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    26/06/2021
\brief
This file contain the Camera component


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef CAMERA_COMPONENT_HPP
#define CAMERA_COMPONENT_HPP

#include "Math/MathLib.hpp"

struct Camera2D {
    //GLObject* pgo = nullptr; // pointer to game object that embeds camera
    //Transform* transform = nullptr;
    //MathD::Mat3 world_to_ndc_xform = MathD::Mat3{};

    // window parameters
    int height{ 1000 };
    float ar = float{};

    bool isActive = true;

    Camera2D(bool active = true, int ht = 1000) :
        isActive{ active }, height{ ht } {}
};

#endif