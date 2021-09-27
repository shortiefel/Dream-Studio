/* Start Header**********************************************************************************/
/*
@file    CameraSystem.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
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

//#include "Engine/Header/Window.hpp" //To get GLFWwindow
#include "Engine/Header/Management/Settings.hpp" //To get game window size

#include "Engine/Header/ECS/Component/Graphics/CameraComponent.hpp"
#include "Engine/Header/ECS/Component/Graphics/TransformComponent.hpp"

#include "Engine/Header/ECS/DreamECS.hpp"

namespace Engine {
    //extern Coordinator gCoordinator;
#ifndef NEW_ECS
    std::shared_ptr<CameraSystem> CameraSystem::CS;
#endif
    //Math::mat3 CameraSystem::world_to_ndc_xform;
    //GLFWwindow* CameraSystem::pwindow;

    //Update function to change the world to NDC transform that will be used
    //to create the graphics
    void CameraSystem::Update(float dt) {
#if NEW_ECS
        auto& camArray = DreamECS::GetInstance().GetComponentArrayData<CameraComponent>();
        for (auto& cam : camArray) {
            if (Entity_Check(cam.GetEntityId())) break;
            if (!cam.isActive) continue;

            TransformComponent* transform = DreamECS::GetInstance().GetComponentTest<TransformComponent>(cam.GetEntityId());
            if (!transform || !transform->isActive) continue;


            //GLsizei fb_width, fb_height;
            //glfwGetFramebufferSize(pwindow, &fb_width, &fb_height);
            cam.ar = Settings::gameAR;


            // compute world-to-NDC transformation matrix
            world_to_ndc_xform =
                Math::mat3(
                    2.f / (cam.ar * CAMERA_HEIGHT * cam.fov), 0.f, 0.f,
                    0.f, 2.f / CAMERA_HEIGHT * cam.fov, 0.f,
                    0.f, 0.f, 1.f)
                *
                Math::mat3(
                    1.f, 0.f, 0.f,
                    0.f, 1.f, 0.f,
                    -transform->position.x, -transform->position.y, 1.f);
            break; //Just need one transform
        }
#else
        for (auto const& entity : CS->mEntities) {
            auto cam = DreamECS::GetComponent<Camera2D>(entity);

            if (cam.isActive == false) continue;
            const auto& transform = DreamECS::GetComponent<Transform>(entity);

            GLsizei fb_width, fb_height;
            glfwGetFramebufferSize(pwindow, &fb_width, &fb_height);
            cam.ar = static_cast<GLfloat>(fb_width) / fb_height;

            // compute world-to-NDC transformation matrix
            world_to_ndc_xform =
                Math::mat3(
                    2.f / (cam.ar * CAMERA_HEIGHT * cam.fov), 0.f, 0.f,
                    0.f, 2.f / CAMERA_HEIGHT * cam.fov, 0.f,
                    0.f, 0.f, 1.f)
                *
                Math::mat3(
                    1.f, 0.f, 0.f,
                    0.f, 1.f, 0.f,
                    -transform.position.x, -transform.position.y, 1.f);
            break; //Just need one transform
        }
#endif
    }

    Math::mat3 CameraSystem::GetTransform() {
        return world_to_ndc_xform;
    }

    //bool CameraSystem::Create(const std::shared_ptr<CameraSystem>& cameraSystem) {
    bool CameraSystem::Create() {
#ifndef NEW_ECS
        CS = cameraSystem;
#endif
        //pwindow = Window::GetGLFWwindow();

        //world_to_ndc_xform = { 1.f,0.f,0.f,  0.f,1.f,0.f,  0.f,0.f,1.f };

        LOG_INSTANCE("Camera System created");
        return true;
    }

    void CameraSystem::Destroy() {
        LOG_INSTANCE("Camera System destroyed");
    }
}