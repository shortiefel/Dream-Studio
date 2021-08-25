/* Start Header**********************************************************************************/
/*
@file    EditorSceneCamera.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    22/07/2021
\brief
This file contain the EditorSceneCamera definition
Display scene view
EditorSceneCamera allow user to move the camera to edit the scene
NOTE: Not to be confused with Entity with camera component which display in game view


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug tools/Logging.hpp"
#include "Engine/Header/pch.hpp"
#include "Engine/Header/Window.hpp"

#include "Editor/Header/Graphic/EditorSceneCamera.hpp"

#define SCENE_CAMERA_HEIGHT 500

namespace Editor {
    glm::vec2 EditorSceneCamera::position;
    float EditorSceneCamera::ar;
    //glm::mat3 EditorSceneCamera::world_to_ndc_xform;

    /*void EditorSceneCamera::Update(float dt) {
        return;
    }*/

    glm::mat3 EditorSceneCamera::GetTransform() {
        return 
            // compute world-to-NDC transformation matrix
            glm::mat3(
                2.f / (ar * SCENE_CAMERA_HEIGHT), 0.f, 0.f,
                0.f, 2.f / SCENE_CAMERA_HEIGHT, 0.f,
                0.f, 0.f, 1.f)
            *
            glm::mat3(
                1.f, 0.f, 0.f,
                0.f, 1.f, 0.f,
                -position.x, -position.y, 1.f);
    }

    void EditorSceneCamera::Create(glm::vec2 pos) {
        position = pos;

        GLsizei fb_width, fb_height;
        glfwGetFramebufferSize(Engine::Window::GetGLFWwindow(), &fb_width, &fb_height);
        ar = static_cast<GLfloat>(fb_width) / fb_height;

        LOG_INSTANCE("Scene Camera created");
    }

    void EditorSceneCamera::Destroy() {
        LOG_INSTANCE("Scene Camera destroyed");
    }


}