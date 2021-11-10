/* Start Header**********************************************************************************/
/*
@file    Factory.cpp
@author  Chia Yi Da		chiayida98@gmail.com
@date    23/06/2021
\brief
This file allow user to create shapes easily with function: CreateSquare and CreateCircle
It also setup all the components and system when a factory is created


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/ECS/Factory.hpp"
#include "Engine/Header/ECS/DreamECS.hpp"

//Components
#include "Engine/Header/ECS/Component/ComponentList.hpp"

//Systems
#include "Engine/Header/ECS/System/SystemList.hpp"

#define CREATE_REGISTER(type) type->Create();\
                              type->RegisterComponent<CameraComponent>();\
                              type->RegisterComponent<TransformComponent>();\
                              type->RegisterComponent<ColliderComponent>();\
                              type->RegisterComponent<TextureComponent>();\
                              type->RegisterComponent<RigidBodyComponent>();\
                              type->RegisterComponent<ScriptComponent>();\
                              type->RegisterComponent<UIComponent>();\
                              type->RegisterComponent<FontComponent>();

namespace Engine 
{
    //Coordinator gCoordinator;=

    void Factory::Create() 
    {
       CREATE_REGISTER(dreamECSGame);

        CameraSystem::GetInstance().Create();
        CollisionSystem::GetInstance().Create();
        PhysicsSystem::GetInstance().Create();
        ScriptSystem::GetInstance().Create();
        UISystem::GetInstance().Create();
        TransformCalculationSystem::GetInstance().Create();
        GraphicSystem::GetInstance().Create();
        FontSystem::GetInstance().Create();

    }

    void Factory::Destroy() 
    {
        GraphicSystem::GetInstance().Destroy();
        TransformCalculationSystem::GetInstance().Destroy();
        UISystem::GetInstance().Destroy();
        ScriptSystem::GetInstance().Destroy();
        PhysicsSystem::GetInstance().Destroy();
        CollisionSystem::GetInstance().Destroy();
        CameraSystem::GetInstance().Destroy();
        FontSystem::GetInstance().Destroy();
    }

    //Create blank transform

    //Function will be called when GUI inspector request a Square entity
    void Factory::InstantiateSquare(Math::vec2 pos, Math::vec2 scale) 
    {
        Entity entity = dreamECSGame->CreateEntity();
        dreamECSGame->AddComponent(
            TransformComponent{ entity.id, pos, scale, 0 });
        dreamECSGame->AddComponent(
            ColliderComponent{ entity.id, ColliderType::SQUARE });
        /*dreamECSGame->AddComponent(
            TextureComponent{ entity.id, "Assets\\Textures\\Default_Square.png" });*/
    }

    //Function will be called when GUI inspector request a Circle entity
    void Factory::InstantiateCircle(Math::vec2 pos, Math::vec2 scale) 
    {
        Entity entity = dreamECSGame->CreateEntity();
        dreamECSGame->AddComponent(
            TransformComponent{ entity.id, pos, scale, 0 });
        dreamECSGame->AddComponent(
            ColliderComponent{ entity.id, ColliderType::CIRCLE });
        /*dreamECSGame->AddComponent(
            TextureComponent{ entity.id, "Assets\\Textures\\Default_Circle.png" });*/
    }
}