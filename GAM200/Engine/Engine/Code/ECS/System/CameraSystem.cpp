/* Start Header**********************************************************************************/
/*
@file    CameraSystem.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
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

#include "Engine/Header/Window.hpp" //To get GLFWwindow

#include "Engine/Header/ECS/Component/Graphics/CameraComponent.hpp"
#include "Engine/Header/ECS/Component/Graphics/TransformComponent.hpp"

#include "Engine/Header/ECS/ECSWrapper.hpp"

namespace Engine {
    //extern Coordinator gCoordinator;
    std::shared_ptr<CameraSystem> CameraSystem::CS;
    glm::mat3 CameraSystem::world_to_ndc_xform;
    GLFWwindow* CameraSystem::pwindow;

    //Update function to change the world to NDC transform that will be used
    //to create the graphics
    void CameraSystem::Update(float dt) {
        for (auto const& entity : CS->mEntities) {
            auto& cam = DreamECS::GetComponent<Camera2D>(entity);
            if (cam.isActive == false) continue;
            const auto& transform = DreamECS::GetComponent<Transform>(entity);

            GLsizei fb_width, fb_height;
            glfwGetFramebufferSize(pwindow, &fb_width, &fb_height);
            cam.ar = static_cast<GLfloat>(fb_width) / fb_height;

            // compute world-to-NDC transformation matrix
            world_to_ndc_xform =
                glm::mat3(
                    2.f / (cam.ar * CAMERA_HEIGHT * cam.fov), 0.f, 0.f,
                    0.f, 2.f / CAMERA_HEIGHT * cam.fov, 0.f,
                    0.f, 0.f, 1.f)
                *
                glm::mat3(
                    1.f, 0.f, 0.f,
                    0.f, 1.f, 0.f,
                    -transform.position.x, -transform.position.y, 1.f);
            break; //Just need one transform
        }
    }

    glm::mat3 CameraSystem::GetTransform() {
        return world_to_ndc_xform;
    }

    bool CameraSystem::Create(const std::shared_ptr<CameraSystem>& cameraSystem) {
        CS = cameraSystem;
        pwindow = Window::GetGLFWwindow();

        //world_to_ndc_xform = { 1.f,0.f,0.f,  0.f,1.f,0.f,  0.f,0.f,1.f };

        LOG_INSTANCE("Camera System created");
        return true;
    }

    void CameraSystem::Destroy() {
        LOG_INSTANCE("Camera System destroyed");
    }

    CameraSystem::~CameraSystem() { Destroy(); }

}