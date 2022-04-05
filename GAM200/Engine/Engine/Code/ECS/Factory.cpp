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

#include "Engine/Header/ECS/Factory.hpp"
#include "Engine/Header/Management/Settings.hpp"

//Components
#include "Engine/Header/ECS/Component/ComponentList.hpp"

//Systems
#include "Engine/Header/ECS/System/SystemList.hpp"

//Random Class
#include "Engine/Header/Random/Random.hpp"


namespace Engine
{
    // Init function for Factory
    void Factory::Create()
    {
        //dreamECSGame->Create();
        dreamECSGame->RegisterComponent<CameraComponent>();
        dreamECSGame->RegisterComponent<TransformComponent>();
        dreamECSGame->RegisterComponent<ColliderComponent>();
        dreamECSGame->RegisterComponent<TextureComponent>();
        dreamECSGame->RegisterComponent<RigidBodyComponent>();
        dreamECSGame->RegisterComponent<ScriptComponent>();
        dreamECSGame->RegisterComponent<UIComponent>();
        dreamECSGame->RegisterComponent<FontComponent>();
        dreamECSGame->RegisterComponent<SoundComponent>();
        dreamECSGame->RegisterComponent<ParticleComponent>();
        dreamECSGame->RegisterComponent<WaypointComponent>();
        dreamECSGame->RegisterComponent<LightComponent>();

        dreamECSLoader->Create();
        dreamECSLoader->RegisterComponent<CameraComponent>();
        dreamECSLoader->RegisterComponent<TransformComponent>();
        dreamECSLoader->RegisterComponent<ColliderComponent>();
        dreamECSLoader->RegisterComponent<TextureComponent>();
        dreamECSLoader->RegisterComponent<RigidBodyComponent>();
        dreamECSLoader->RegisterComponent<ScriptComponent>();
        dreamECSLoader->RegisterComponent<UIComponent>();
        dreamECSLoader->RegisterComponent<FontComponent>();
        dreamECSLoader->RegisterComponent<SoundComponent>();
        dreamECSLoader->RegisterComponent<ParticleComponent>();
        dreamECSLoader->RegisterComponent<WaypointComponent>();
        dreamECSLoader->RegisterComponent<LightComponent>();

        CameraSystem::GetInstance().Create();
        CollisionSystem::GetInstance().Create();
        PhysicsSystem::GetInstance().Create();
        ScriptSystem::GetInstance().Create();

        GraphicSystem::GetInstance().Create();
        UISystem::GetInstance().Create();
        FontSystem::GetInstance().Create();
        SoundSystem::GetInstance().SoundCreate();

        Random::Create();
    }

    // Destroy function for Factory 
    void Factory::Destroy()
    {
        SoundSystem::GetInstance().SoundDestroy();
        FontSystem::GetInstance().Destroy();
        UISystem::GetInstance().Destroy();
        GraphicSystem::GetInstance().Destroy();

        ScriptSystem::GetInstance().Destroy();
        PhysicsSystem::GetInstance().Destroy();
        CollisionSystem::GetInstance().Destroy();
        CameraSystem::GetInstance().Destroy();

        delete dreamECSLoader;
        delete dreamECSGame;
    }

    // Function will be called when GUI inspector request a Square entity
    void Factory::InstantiateSquare(Math::vec2 pos, Math::vec2 scale, DreamECS* dreamECS)
    {
        Entity entity = dreamECS->CreateEntity();
        dreamECS->AddComponent(
            TransformComponent{ entity.id, pos, scale, 0 });
        /*dreamECSGame->AddComponent(
            ColliderComponent{ entity.id, ColliderType::Square });*/
        dreamECS->AddComponent(
            TextureComponent{ entity.id, Settings::defaultSquare });
    }

    // Function will be called when GUI inspector request a Circle entity
    void Factory::InstantiateCircle(Math::vec2 pos, Math::vec2 scale, DreamECS* dreamECS)
    {
        Entity entity = dreamECS->CreateEntity();
        dreamECS->AddComponent(
            TransformComponent{ entity.id, pos, scale, 0 });
        /*dreamECSGame->AddComponent(
            ColliderComponent{ entity.id, ColliderType::Circle });*/
        dreamECS->AddComponent(
            TextureComponent{ entity.id, Settings::defaultCircle });
    }
}