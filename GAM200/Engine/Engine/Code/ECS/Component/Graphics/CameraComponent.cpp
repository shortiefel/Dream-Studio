/* Start Header**********************************************************************************/
/*
@file    CameraComponent.cpp
@author  Chia Yi Da		chiayida98@gmail.com
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

namespace Engine 
{
    CameraComponent::CameraComponent(Entity_id _ID, int _height, float _fov, float _ar, bool _active) :
        IComponent{ _ID }, height{ _height }, fov{ _fov }, ar{ _ar }, isActive{ _active } {}

    CameraComponent& CameraComponent::Deserialize(const DSerializer& _serializer) 
    {
        height = _serializer.GetValue<int>("Height");
        fov = _serializer.GetValue<float>("FOV");
        ar = _serializer.GetValue<float>("AR");
        isActive = _serializer.GetValue<bool>("IsActive");
        return *this;
    }

    void CameraComponent::Serialize(const SSerializer& _serializer) 
    {
        _serializer.SetValue("Height", height);
        _serializer.SetValue("FOV", fov);
        _serializer.SetValue("AR", ar);
        _serializer.SetValue("IsActive", isActive);
    }
}