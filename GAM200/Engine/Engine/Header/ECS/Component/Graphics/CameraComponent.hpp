/* Start Header**********************************************************************************/
/*
@file    CameraComponent.hpp
@author  Chia Yi Da		c.yida@digipen.edu      100%
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

    struct CameraComponent : public IComponent
    {
        // Window parameters
        float ar{}, fov{};
        float height{};

        bool isActive = true;


        CameraComponent(Entity_id _ID = DEFAULT_ENTITY_ID, float _height = 15, float _fov = 1.f, float _ar = 0.f, bool _active = false);


        //CameraComponent& Deserialize(const DSerializer& _serializer);
        //void Serialize(const SSerializer& _serializer);

        CameraComponent(Entity_id entId, const CameraComponent& rhs);
        CameraComponent(const CameraComponent&) = default;
        CameraComponent& operator=(const CameraComponent&) = default;
    };
}

#endif