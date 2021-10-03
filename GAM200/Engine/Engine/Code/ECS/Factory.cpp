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

namespace Engine {
    //Coordinator gCoordinator;

    void Factory::Create() {
        DreamECS::GetInstance().Create();
        DreamECS::GetInstance().RegisterComponent<CameraComponent>();
        DreamECS::GetInstance().RegisterComponent<TransformComponent>();
        DreamECS::GetInstance().RegisterComponent<ColliderComponent>();
        DreamECS::GetInstance().RegisterComponent<TextureComponent>();
        DreamECS::GetInstance().RegisterComponent<RigidBodyComponent>();
        DreamECS::GetInstance().RegisterComponent<ScriptComponent>();

        CameraSystem::GetInstance().Create();
        GraphicSystem::GetInstance().Create();
        CollisionSystem::GetInstance().Create();
        PhysicsSystem::GetInstance().Create();
        ScriptSystem::GetInstance().Create();

    }

    void Factory::Destroy() {
        ScriptSystem::GetInstance().Destroy();
        PhysicsSystem::GetInstance().Destroy();
        CollisionSystem::GetInstance().Destroy();
        GraphicSystem::GetInstance().Destroy();
        CameraSystem::GetInstance().Destroy();
    }

    //Create blank transform

    //Function will be called when GUI inspector request a Square entity
    void Factory::InstantiateSquare(Math::vec2 pos, Math::vec2 scale, bool isMoveable) {
        Entity ent = DreamECS::GetInstance().CreateEntity();
        DreamECS::GetInstance().AddComponent(
            TransformComponent{ ent, pos, scale, 0 });
        DreamECS::GetInstance().AddComponent(
            ColliderComponent{ ent, ColliderType::SQUARE });
    }

    //Function will be called when GUI inspector request a Circle entity
    void Factory::InstantiateCircle(Math::vec2 pos, Math::vec2 scale, bool isMoveable) {
        Entity ent = DreamECS::GetInstance().CreateEntity();
        DreamECS::GetInstance().AddComponent(
            TransformComponent{ ent, pos, scale, 0 });
        DreamECS::GetInstance().AddComponent(
            ColliderComponent{ ent, ColliderType::CIRCLE });
    }
    //------------------------------------------------------------------------------

}