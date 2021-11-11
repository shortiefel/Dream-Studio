/* Start Header**********************************************************************************/
/*
@file    EditorSceneCamera.cpp
@author  Chia Yi Da		c.yida@digipen.edu
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

#define MIN_SCENE_CAMERA_HEIGHT 5
#define MAX_SCENE_CAMERA_HEIGHT 100

#define FIXED_UI_MULTIPLIER 0.4f

namespace Editor 
{
    float SCENE_CAMERA_HEIGHT = 20.f;
    Math::vec2 EditorSceneCamera::position;
    float EditorSceneCamera::ar;

    // Function that gets the height for EditorSceneCamera
    float EditorSceneCamera::GetHeight() 
    {
        return SCENE_CAMERA_HEIGHT;
    }

    // Function that gets the aspect ratio for EditorSceneCamera
    float EditorSceneCamera::GetAR() 
    {
        return ar;
    }

    // Function that gets the transformation matrix for EditorSceneCamera
    Math::mat3 EditorSceneCamera::GetTransform() 
    {
        return
            // compute world-to-NDC transformation matrix
            Math::mat3(2.f / (ar * SCENE_CAMERA_HEIGHT), 0.f, 0.f,
                       0.f, 2.f / SCENE_CAMERA_HEIGHT, 0.f,
                       0.f, 0.f, 1.f)
            *
            Math::mat3(1.f, 0.f, 0.f,
                       0.f, 1.f, 0.f,
                      -position.x, -position.y, 1.f);
    }
    
    // Function that gets the inverse transformation matrix for EditorSceneCamera
    Math::mat3 EditorSceneCamera::GetInverseTransform()
    {
        return
            Math::mat3(1.f, 0.f, 0.f,
                0.f, 1.f, 0.f,
                position.x, position.y, 1.f)
            *
            Math::mat3((ar * SCENE_CAMERA_HEIGHT) / 2.f, 0.f, 0.f,
                0.f, SCENE_CAMERA_HEIGHT / 2.f, 0.f,
                0.f, 0.f, 1.f);
            
    }

    // Function that gets the UI transformation matrix for EditorSceneCamera
    Math::mat3 EditorSceneCamera::GetTransformUI()
    {
        return
            // compute world-to-NDC transformation matrix
            Math::mat3(2.f / (ar * SCENE_CAMERA_HEIGHT * FIXED_UI_MULTIPLIER), 0.f, 0.f,
                0.f, 2.f / (SCENE_CAMERA_HEIGHT * FIXED_UI_MULTIPLIER), 0.f,
                0.f, 0.f, 1.f)
            *
            Math::mat3(1.f, 0.f, 0.f,
                0.f, 1.f, 0.f,
                -position.x, -position.y, 1.f);
    }

    // Function that changes the height for EditorSceneCamera
    void EditorSceneCamera::changeHeight(float val) {
        SCENE_CAMERA_HEIGHT += val;
        if (SCENE_CAMERA_HEIGHT < MIN_SCENE_CAMERA_HEIGHT) SCENE_CAMERA_HEIGHT = MIN_SCENE_CAMERA_HEIGHT;
        else if (SCENE_CAMERA_HEIGHT > MAX_SCENE_CAMERA_HEIGHT) SCENE_CAMERA_HEIGHT = MAX_SCENE_CAMERA_HEIGHT;
    }

    // Function that changes the position for EditorSceneCamera
    void EditorSceneCamera::changePosition(Math::vec2 val) {
        position += val;
    }
    
    // Create function for EditorSceneCamera
    void EditorSceneCamera::Create(Math::vec2 pos) 
    {
        position = pos;

        GLsizei fb_width, fb_height;
        glfwGetFramebufferSize(Engine::Window::GetInstance().GetGLFWwindow(), &fb_width, &fb_height);
        ar = static_cast<GLfloat>(fb_width) / fb_height;

        LOG_INSTANCE("Scene Camera created");
    }

    // Destroy function for EditorSceneCamera
    void EditorSceneCamera::Destroy() 
    {
        LOG_INSTANCE("Scene Camera destroyed");
    }
}