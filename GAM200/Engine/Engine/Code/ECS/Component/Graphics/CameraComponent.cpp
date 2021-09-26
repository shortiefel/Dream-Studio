/* Start Header**********************************************************************************/
/*
@file    CameraComponent.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
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

#include "Engine/Header/Serialize/DSerializer.hpp"
#include "Engine/Header/Serialize/SSerializer.hpp"

namespace Engine {
    Camera2D::Camera2D(Entity _ID, float _fov, float _ar, bool _active) :
        IComponent{ _ID },//num{ ID },
        fov{ _fov }, ar{ _ar }, isActive{ _active } {}

    Camera2D& Camera2D::Deserialize(const DSerializer& _serializer) {
        fov = _serializer.GetValue<float>("FOV");
        ar = _serializer.GetValue<float>("AR");
        isActive = _serializer.GetValue<bool>("IsActive");
        return *this;
    }

    void Camera2D::Serialize(const SSerializer& _serializer) {
        _serializer.SetValue("FOV", fov);
        _serializer.SetValue("AR", ar);
        _serializer.SetValue("IsActive", isActive);

        //_serializer.EndSerialize("Camera2D");
    }
}