/* Start Header**********************************************************************************/
/*
@file    Factory.cpp
@author  Chia Yi Da		c.yida@digipen.edu
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

#include "Engine/Header/ECS/DreamECS.hpp"
#include "Engine/Header/ECS/Factory.hpp"
#include "Engine/Header/Management/Settings.hpp"

//Components
#include "Engine/Header/ECS/Component/ComponentList.hpp"

//Systems
#include "Engine/Header/ECS/System/SystemList.hpp"

namespace Engine
{
    // Init function for Factory
    void Factory::Create()
    {
        dreamECSGame->Create();
        dreamECSGame->RegisterComponent<CameraComponent>();
        dreamECSGame->RegisterComponent<TransformComponent>();
        dreamECSGame->RegisterComponent<ColliderComponent>();
        dreamECSGame->RegisterComponent<TextureComponent>();
        dreamECSGame->RegisterComponent<RigidBodyComponent>();
        dreamECSGame->RegisterComponent<ScriptComponent>();
        dreamECSGame->RegisterComponent<UIComponent>();
        dreamECSGame->RegisterComponent<FontComponent>();

        CameraSystem::GetInstance().Create();
        CollisionSystem::GetInstance().Create();
        PhysicsSystem::GetInstance().Create();
        ScriptSystem::GetInstance().Create();
        TransformCalculationSystem::GetInstance().Create();

        GraphicSystem::GetInstance().Create();
        UISystem::GetInstance().Create();
        FontSystem::GetInstance().Create();
    }

    // Destroy function for Factory 
    void Factory::Destroy()
    {
        GraphicSystem::GetInstance().Destroy();
        FontSystem::GetInstance().Destroy();
        UISystem::GetInstance().Destroy();
        TransformCalculationSystem::GetInstance().Destroy();
        ScriptSystem::GetInstance().Destroy();
        PhysicsSystem::GetInstance().Destroy();
        CollisionSystem::GetInstance().Destroy();
        CameraSystem::GetInstance().Destroy();
    }

    // Function will be called when GUI inspector request a Square entity
    void Factory::InstantiateSquare(Math::vec2 pos, Math::vec2 scale)
    {
        Entity entity = dreamECSGame->CreateEntity();
        dreamECSGame->AddComponent(
            TransformComponent{ entity.id, pos, scale, 0 });
        /*dreamECSGame->AddComponent(
            ColliderComponent{ entity.id, ColliderType::Square });*/
        dreamECSGame->AddComponent(
            TextureComponent{ entity.id, Settings::defaultSquare });
    }

    // Function will be called when GUI inspector request a Circle entity
    void Factory::InstantiateCircle(Math::vec2 pos, Math::vec2 scale)
    {
        Entity entity = dreamECSGame->CreateEntity();
        dreamECSGame->AddComponent(
            TransformComponent{ entity.id, pos, scale, 0 });
        /*dreamECSGame->AddComponent(
            ColliderComponent{ entity.id, ColliderType::Circle });*/
        dreamECSGame->AddComponent(
            TextureComponent{ entity.id, Settings::defaultCircle });
    }
}