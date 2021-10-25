/* Start Header**********************************************************************************/
/*
@file    CameraComponent.hpp
@author  Chia Yi Da		chiayida98@gmail.com
@date    26/06/2021
@brief
This file contains the Camera component


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
    class DSerializer;
    class SSerializer;

    constexpr int CAMERA_HEIGHT = 1000;

    struct CameraComponent : public IComponent 
    {
        // window parameters
        float ar = float{}, fov = float{};
        bool isActive = true;

        CameraComponent& Deserialize(const DSerializer& _serializer);
        void Serialize(const SSerializer& _serializer);

        CameraComponent(Entity_id _ID = DEFAULT_ENTITY_ID, float _fov = 1.f, float _ar = 0.f, bool _active = false);
        CameraComponent(const CameraComponent&) = default;
        CameraComponent& operator=(const CameraComponent&) = default;
    };
}

#endif
