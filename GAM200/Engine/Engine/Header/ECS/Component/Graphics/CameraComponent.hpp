/* Start Header**********************************************************************************/
/*
@file    CameraComponent.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    26/06/2021
\brief
This file contain the Camera component


//Serialize list
-string:    pathname
-float:     fov
-float:     AR
-bool:      isActive


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef CAMERA_COMPONENT_HPP
#define CAMERA_COMPONENT_HPP

#include "Engine/Header/ECS/Component/IComponent.hpp"

namespace Engine {
    constexpr int CAMERA_HEIGHT = 1000;

    struct Camera2D : public IComponent {
        // window parameters
        float ar = float{}, fov = float{};

        bool isActive = true;

        Camera2D() = default;
        Camera2D(Entity ID, float fieldOfView, float ratio, bool active) :
            IComponent{ ID },//num{ ID },
            fov{ fieldOfView }, ar{ ratio }, isActive{ active } {}
        Camera2D(const Camera2D&) = default;
        Camera2D& operator=(const Camera2D&) = default;
    };
}

#endif
