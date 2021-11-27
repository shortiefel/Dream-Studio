/* Start Header**********************************************************************************/
/*
@file    CameraSystem.cpp
@author  Chia Yi Da		c.yida@digipen.edu
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

#include "Engine/Header/ECS/DreamECS.hpp"
#include "Engine/Header/Debug Tools/Profiler.hpp"
#include "Engine/Header/Management/Settings.hpp"

#include "Engine/Header/ECS/System/CameraSystem.hpp"

#include "Engine/Header/ECS/Component/Graphics/CameraComponent.hpp"
#include "Engine/Header/ECS/Component/Graphics/TransformComponent.hpp"


//#define FIXED_UI_HEIGHT 1000.f
#define FIXED_UI_HEIGHT 100.f

namespace Engine
{
    // Update function to change the world to NDC transform that will be used to create the graphics
    void CameraSystem::Update(float)
    {
        camFov = 0.f;
        camHeight = 0;

        // Loop through component array for camera
        auto& camArray = dreamECSGame->GetComponentArrayData<CameraComponent>();
        for (auto& cam : camArray)
        {
            const Entity_id& entity_id = cam.GetEntityId();
            if (EntityId_Check(entity_id)) break;
            if (!cam.isActive) continue;

            TransformComponent* transform = dreamECSGame->GetComponentPTR<TransformComponent>(entity_id);
            if (!transform || !transform->isActive) continue;

            cam.ar = Settings::gameAR;

            // compute world-to-NDC transformation matrix
            camPosition = transform->position;
            camFov = cam.fov;
            camHeight = cam.height;

            break; //Just need one transform
        }
    }

    // Function that gets the transform matrix for camera
    Math::mat3 CameraSystem::GetTransform(unsigned int* id)
    {
        if (id == nullptr)
        {
            return
                Math::mat3(2.f / (Settings::gameAR * camHeight * camFov), 0.f, 0.f,
                    0.f, 2.f / (camHeight * camFov), 0.f,
                    0.f, 0.f, 1.f)
                *
                Math::mat3(1.f, 0.f, 0.f,
                    0.f, 1.f, 0.f,
                    -camPosition.x, -camPosition.y, 1.f);
        }

        const auto& cam = dreamECSGame->GetComponent<CameraComponent>(*id);
        const auto& trans = dreamECSGame->GetComponent<TransformComponent>(*id);

        return
            Math::mat3(2.f / (Settings::gameAR * cam.height * cam.fov), 0.f, 0.f,
                0.f, 2.f / (cam.height * cam.fov), 0.f,
                0.f, 0.f, 1.f)
            *
            Math::mat3(1.f, 0.f, 0.f,
                0.f, 1.f, 0.f,
                -trans.position.x, -trans.position.y, 1.f);
    }

    Math::mat4 CameraSystem::GetTransformMat4(unsigned int* id)
    {
        if (id == nullptr)
        {
            return
                Math::mat4(2.f / (Settings::gameAR * camHeight * camFov), 0.f, 0.f, 0.f,
                    0.f, 2.f / (camHeight * camFov), 0.f, 0.f,
                    0.f, 0.f, 1.f, 0.f,
                    0.f, 0.f, 0.f, 1.f)
                *
                Math::mat4(1.f, 0.f, 0.f, 0.f,
                    0.f, 1.f, 0.f, 0.f,
                    0.f, 0.f, 1.f, 0.f,
                    -camPosition.x, -camPosition.y, 0.f,  1.f);
        }

        const auto& cam = dreamECSGame->GetComponent<CameraComponent>(*id);
        const auto& trans = dreamECSGame->GetComponent<TransformComponent>(*id);

        return
            Math::mat4(2.f / (Settings::gameAR * cam.height * cam.fov), 0.f, 0.f, 0.f,
                0.f, 2.f / (cam.height * cam.fov), 0.f, 0.f,
                0.f, 0.f, 1.f, 0.f,
                0.f, 0.f, 0.f, 1.f)
            *
            Math::mat4(1.f, 0.f, 0.f, 0.f,
                0.f, 1.f, 0.f, 0.f,
                0.f, 0.f, 1.f, 0.f,
                -trans.position.x, -trans.position.y, 0.f, 1.f);
    }

    // Function that gets the inverse transform matrix for camera
    Math::mat3 CameraSystem::GetInverseTransform(unsigned int* id)
    {
        if (id == nullptr)
        {
            return
                Math::mat3(1.f, 0.f, 0.f,
                    0.f, 1.f, 0.f,
                    camPosition.x, camPosition.y, 1.f)
                *
                Math::mat3((Settings::gameAR * camHeight * camFov) / 2.f, 0.f, 0.f,
                    0.f, (camHeight * camFov) / 2.f, 0.f,
                    0.f, 0.f, 1.f);
        }

        const auto& cam = dreamECSGame->GetComponent<CameraComponent>(*id);
        const auto& trans = dreamECSGame->GetComponent<TransformComponent>(*id);

        return
            Math::mat3(1.f, 0.f, 0.f,
                0.f, 1.f, 0.f,
                trans.position.x, trans.position.y, 1.f)
            *
            Math::mat3((Settings::gameAR * cam.height * cam.fov) / 2.f, 0.f, 0.f,
                0.f, (cam.height * cam.fov) / 2.f, 0.f,
                0.f, 0.f, 1.f);
    }

    // Function that gets the transform matrix for camera UI
    Math::mat3 CameraSystem::GetTransformUI()
    {
        return
            Math::mat3(2.f / (Settings::gameAR * FIXED_UI_HEIGHT * camFov), 0.f, 0.f,
                0.f, 2.f / (FIXED_UI_HEIGHT * camFov), 0.f,
                0.f, 0.f, 1.f);
            //*

            //Math::mat3(1.f, 0.f, 0.f,
            //    0.f, 1.f, 0.f,
            //    -camPosition.x, -camPosition.y, 1.f);
    }

    Math::mat4 CameraSystem::GetTransformUIMat4(){
         return
            Math::mat4(2.f / (Settings::gameAR * FIXED_UI_HEIGHT * camFov), 0.f, 0.f, 0.f,
                0.f, 2.f / (FIXED_UI_HEIGHT * camFov), 0.f, 0.f,
                0.f, 0.f, 1.f, 0.f,
                0.f, 0.f, 0.f, 1.f)
            *

            Math::mat4(1.f, 0.f, 0.f, 0.f,
                0.f, 1.f, 0.f, 0.f,
                0.f, 0.f, 1.f, 0.f,
                -camPosition.x, -camPosition.y, 0.f, 1.f);
    }

    // Function that gets the position for camera
    Math::vec2 CameraSystem::GetPosition()
    {
        return camPosition;
    }

    // Function that gets the aspect ratio
    float CameraSystem::GetAR() const
    {
        return Settings::gameAR;
    }

    // Create function for CameraSystem
    bool CameraSystem::Create()
    {
        LOG_INSTANCE("Camera System created");
        return true;
    }

    // Destroy function for CameraSystem
    void CameraSystem::Destroy()
    {
        LOG_INSTANCE("Camera System destroyed");
    }
}

// Code that might be used for the future

/*
//GLsizei fb_width, fb_height;
//glfwGetFramebufferSize(pwindow, &fb_width, &fb_height);

world_to_ndc_xform =
    Math::mat3(2.f / (cam.ar * CAMERA_HEIGHT * cam.fov), 0.f, 0.f,
               0.f, 2.f / CAMERA_HEIGHT * cam.fov, 0.f,
               0.f, 0.f, 1.f)
    *
    Math::mat3(1.f, 0.f, 0.f,
               0.f, 1.f, 0.f,
              -transform->position.x, -transform->position.y, 1.f);
*/