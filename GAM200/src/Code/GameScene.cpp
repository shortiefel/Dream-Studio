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

#include "GameScene.hpp"
#include "Debug Tools/Logging.hpp"

#include "Window.hpp"
#include "Event/EventDispatcher.hpp"
#include "Layer/LayerStack.hpp"
#include "Layer/GUILayer.hpp"

#include "Factory/Factory.hpp"

#include "Coordinator/Coordinator.hpp"
#include "Component/Graphics/TransformComponent.hpp"
#include "Component/Physics/ColliderComponent.hpp"
#include "Component/Graphics/RendererComponent.hpp"
#include "Component/Script/ScriptComponent.hpp"

#include "Graphic/Camera.hpp"

#include "System/GraphicSystem.hpp"
#include "System/PhysicSystem.hpp"
#include "System/ScriptSystem.hpp"

#include "PlayerController.hpp" //Temporary for Native Scripting test

extern Coordinator gCoordinator;
Entity camera;

//Entity player;

bool up = false, down = false, left = false, right = false;

void GameScene::Create() {
    //Serialization
    //Read from text file all information

    //Reset all system
  
    //--------------------------------------------------
    Entity ent = gCoordinator.createEntity();
    gCoordinator.AddComponent(
        ent,
        Transform{ MathD::Vec2{0.f,0.f}, MathD::Vec2{20.f,20.f}, 0.f });
    gCoordinator.AddComponent(ent,
        Renderer2D{ GraphicImplementation::models.find("Square"),  GraphicImplementation::shdrpgms.find("Default") });
    gCoordinator.AddComponent(ent,
            Collider{ ColliderType::SQUARE, true });
    gCoordinator.AddComponent(ent,
        Custom_Script{ std::make_shared<PlayerController>() });


    Entity ent1 = gCoordinator.createEntity();
    gCoordinator.AddComponent(
        ent1,
        Transform{ MathD::Vec2{-100.f,0.f}, MathD::Vec2{20.f,40.f}, 0.f });
    gCoordinator.AddComponent(ent1,
        Renderer2D{ GraphicImplementation::models.find("Square"),  GraphicImplementation::shdrpgms.find("Default") });
    gCoordinator.AddComponent(ent1,
        Collider{ ColliderType::SQUARE, true });
    gCoordinator.AddComponent(ent1,
        Custom_Script{ std::make_shared<AnotherController>() });


    //--------------------------------------------------

    camera = gCoordinator.createEntity();
    gCoordinator.AddComponent(
        camera,
        Transform{ MathD::Vec2 {0.f, 0.f}, MathD::Vec2 {0.f, 0.f}, 0.f });

    GraphicImplementation::camera2d.init(Window::GetGLFWwindow(), &gCoordinator.GetCom<Transform>(camera));

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
    ScriptSystem::Update(dt);
    PhysicSystem::Update(dt);

    GraphicImplementation::camera2d.update(Window::GetGLFWwindow());
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