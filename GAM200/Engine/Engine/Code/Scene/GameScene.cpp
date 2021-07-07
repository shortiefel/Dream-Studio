/* Start Header**********************************************************************************/
/*
@file    GameScene.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    23/06/2021
\brief
An application of the dream engine can have multiple game scene to be used
When created and deleted, it should rebuild the systems and get the correct information from textfiles


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Scene/GameScene.hpp"
#include "Debug Tools/Logging.hpp"

#include "Window.hpp"
#include "Event/EventDispatcher.hpp"
#include "Layer/LayerStack.hpp"
//#include "Layer/GUILayer.hpp"

#include "ECS/Factory.hpp"

#include "ECS/Coordinator.hpp"

//Components
#include "ECS/Component/ComponentList.hpp"
//Systems
#include "ECS/System/SystemList.hpp"


//#include "PlayerController.hpp" //Temporary for Native Scripting test

extern Coordinator gCoordinator;

//Entity temcam, temcam2, temcam3; int num = 1;//Temporary

void GameScene::Create() {
    //Serialization
    //Read from text file all information

    //Reset all system
  
    //Test code--------------------------------------------
    //W A S D, I J K L and arrow keys to move
    //V to switch camera

    /*Entity ent = gCoordinator.createEntity();
    gCoordinator.AddComponent(
        ent,
        Transform{ MathD::Vec2{0.f,0.f}, MathD::Vec2{20.f,20.f}, 0.f, "Square" });
    gCoordinator.AddComponent(ent,
            Collider{ ColliderType::SQUARE, true });
    gCoordinator.AddComponent(ent,
        Custom_Script{ std::make_shared<PlayerController>() });
    gCoordinator.AddComponent(ent,
        Texture{ "Assets/Textures/test1.png" });


    Entity ent1 = gCoordinator.createEntity();
    gCoordinator.AddComponent(
        ent1,
        Transform{ MathD::Vec2{-100.f,0.f}, MathD::Vec2{100.f,100.f}, 0.f, "Square" });
    gCoordinator.AddComponent(ent1,
        Collider{ ColliderType::SQUARE, true });
    gCoordinator.AddComponent(ent1,
        Custom_Script{ std::make_shared<AnotherController>() });
    gCoordinator.AddComponent(ent1,
        Texture{ "Assets/Textures/test2.png" });






    temcam = gCoordinator.createEntity();
    gCoordinator.AddComponent(
        temcam,
        Transform{ MathD::Vec2{0.f,0.f}, MathD::Vec2{0.f,0.f}, 0.f });

    gCoordinator.AddComponent(
        temcam,
        Camera2D{ true });
    gCoordinator.AddComponent(temcam,
        Custom_Script{ std::make_shared<CameraController>() });

    temcam2 = gCoordinator.createEntity();
    gCoordinator.AddComponent(
        temcam2,
        Transform{ MathD::Vec2{240.f,100.f}, MathD::Vec2{0.f,0.f}, 0.f });
    gCoordinator.AddComponent(
        temcam2,
        Camera2D{ false });
    gCoordinator.AddComponent(temcam2,
        Custom_Script{ std::make_shared<CameraController>() });


    temcam3 = gCoordinator.createEntity();
    gCoordinator.AddComponent(
        temcam3,
        Transform{ MathD::Vec2{-40.f,-240.f}, MathD::Vec2{0.f,0.f}, 0.f });
    gCoordinator.AddComponent(
        temcam3,
        Camera2D{ false });
    gCoordinator.AddComponent(temcam3,
        Custom_Script{ std::make_shared<CameraController>() });*/

    //--------------------------------------------------

    /*Factory::InstantiateCircle();
    Factory::InstantiateSquare();*/
}

//When user click play to run their game
void GameScene::Play() {
    //Compile the script
    //Save position of entity temporary (to be changed back after stopping)

    ScriptSystem::Play();
}

//When user click stop to run their game
void GameScene::Stop() {
    //Set position of entity back to before play
    ScriptSystem::Stop();
}

void GameScene::Update(float dt) {
    //testing code------------------------------
    /*static bool state = false;
    if (!state && glfwGetKey(Window::GetGLFWwindow(), GLFW_KEY_V) == GLFW_PRESS) {
        num = num < 3 ? num + 1 : 1;
        state = true;
    }

    else if (state && glfwGetKey(Window::GetGLFWwindow(), GLFW_KEY_V) == GLFW_RELEASE) {
        state = false;
    }
    auto& cam = gCoordinator.GetCom<Camera2D>(temcam);
    cam.isActive = false;
    auto& cam1 = gCoordinator.GetCom<Camera2D>(temcam2);
    cam1.isActive = false;
    auto& cam2 = gCoordinator.GetCom<Camera2D>(temcam3);
    cam2.isActive = false;

    if (num == 1) {
        auto& cam = gCoordinator.GetCom<Camera2D>(temcam);
        cam.isActive = true;
    }
    else if (num == 2) {
        auto& cam = gCoordinator.GetCom<Camera2D>(temcam2);
        cam.isActive = true;
    }
    else if (num == 3) {
        auto& cam = gCoordinator.GetCom<Camera2D>(temcam3);
        cam.isActive = true;
    }*/
    
    //------------------------------------
    ScriptSystem::Update(dt);
    PhysicSystem::Update(dt);

    CameraSystem::Update(dt);
    GraphicSystem::Update(dt);
    GraphicSystem::Render();

    LayerStack::Update();
    LayerStack::Draw();
}

void GameScene::Destroy() {
    //Destroy in reverse order
    //Rebuild the layers for a difference game scene
    //Remove all entity
}