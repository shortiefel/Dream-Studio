/* Start Header**********************************************************************************/
/*
@file    CameraSystem.cpp
@author  Chia Yi Da		chiayida98@gmail.com
@date    26/06/2021
\brief
This file contain the CameraSystem definition
There should only be one entity with CameraComponent active
should there be more than one active, unexpected behavior might occur


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Engine/Header/ECS/System/CameraSystem.hpp"

#include "Engine/Header/Management/Settings.hpp" //To get game window size

#include "Engine/Header/ECS/Component/Graphics/CameraComponent.hpp"
#include "Engine/Header/ECS/Component/Graphics/TransformComponent.hpp"

#include "Engine/Header/ECS/DreamECS.hpp"

#include "Engine/Header/Debug Tools/Profiler.hpp"

#define FIXED_UI_HEIGHT 1000.f

namespace Engine 
{
    //Update function to change the world to NDC transform that will be used
    //to create the graphics
    void CameraSystem::Update(float) {
        camFov = 0.f;
        camHeight = 0;

        auto& camArray = DreamECS::GetInstance().GetComponentArrayData<CameraComponent>();
        for (auto& cam : camArray) {
            const Entity_id& entity_id = cam.GetEntityId();
            if (EntityId_Check(entity_id)) break;
            if (!cam.isActive) continue;

            TransformComponent* transform = DreamECS::GetInstance().GetComponentPTR<TransformComponent>(entity_id);
            if (!transform || !transform->isActive) continue;

            //GLsizei fb_width, fb_height;
            //glfwGetFramebufferSize(pwindow, &fb_width, &fb_height);
            cam.ar = Settings::gameAR;

            // compute world-to-NDC transformation matrix
            camPosition = transform->position;
            camFov = cam.fov;
            camHeight = cam.height;
            /*world_to_ndc_xform =
                Math::mat3(2.f / (cam.ar * CAMERA_HEIGHT * cam.fov), 0.f, 0.f,
                           0.f, 2.f / CAMERA_HEIGHT * cam.fov, 0.f,
                           0.f, 0.f, 1.f)
                *
                Math::mat3(1.f, 0.f, 0.f,
                           0.f, 1.f, 0.f,
                          -transform->position.x, -transform->position.y, 1.f);*/
            break; //Just need one transform
        }
    }

    Math::mat3 CameraSystem::GetTransform() {
        return 
            Math::mat3(2.f / (Settings::gameAR * camHeight * camFov), 0.f, 0.f,
                0.f, 2.f / (camHeight * camFov), 0.f,
                0.f, 0.f, 1.f)
            *
            Math::mat3(1.f, 0.f, 0.f,
                0.f, 1.f, 0.f,
                -camPosition.x, -camPosition.y, 1.f);
    }

    Math::mat3 CameraSystem::GetTransformUI()
    {
        return
            Math::mat3(2.f / (Settings::gameAR * FIXED_UI_HEIGHT * camFov), 0.f, 0.f,
                0.f, 2.f / (FIXED_UI_HEIGHT * camFov), 0.f,
                0.f, 0.f, 1.f)
            *
            Math::mat3(1.f, 0.f, 0.f,
                0.f, 1.f, 0.f,
                -camPosition.x, -camPosition.y, 1.f);

    }

    Math::vec2 CameraSystem::GetPosition() {
        return camPosition;
    }

    float CameraSystem::GetAR() const {
        return Settings::gameAR;
    }

    bool CameraSystem::Create() {
        LOG_INSTANCE("Camera System created");
        return true;
    }

    void CameraSystem::Destroy() {
        LOG_INSTANCE("Camera System destroyed");
    }
}