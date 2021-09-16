/* Start Header**********************************************************************************/
/*
@file    CameraComponent.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    16/09/2021
\brief
This file contain the Camera component definition


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/


#include "Engine/Header/ECS/Component/Graphics/CameraComponent.hpp"

namespace Engine {
    Camera2D::Camera2D(Entity ID, float fieldOfView, float arRatio, bool active) :
        IComponent{ ID },//num{ ID },
        fov{ fieldOfView }, ar{ arRatio }, isActive{ active } {}

    Camera2D Camera2D::Deserialize(const Serializer& serializer) {
        fov = serializer.GetValue<float>("FOV");
        ar = serializer.GetValue<float>("AR");
        isActive = serializer.GetValue<bool>("IsActive");
        return *this;
    }

    void Camera2D::Serialize(const Serializer& serializer) {

    }
}