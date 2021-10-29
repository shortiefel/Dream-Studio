/* Start Header**********************************************************************************/
/*
@file    Scene.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
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

#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Engine/Header/Scene/Scene.hpp"

#include "Engine/Header/Window.hpp"
#include "Engine/Header/Event/EventDispatcher.hpp"
#include "Engine/Header/Layer/LayerStack.hpp"

#include "Engine/Header/Time/DeltaTime.hpp"
//#include "Engine/Header/Management/GameState.hpp"

#include "Engine/Header/Serialize/GameSceneSerializer.hpp"

#include "Engine/Header/ECS/Factory.hpp"
#include "Engine/Header/ECS/DreamECS.hpp"

//#include "Engine/Header/Debug Tools/Profiler.hpp"

//Components
#include "Engine/Header/ECS/Component/ComponentList.hpp"
//Systems
#include "Engine/Header/ECS/System/SystemList.hpp"

namespace Engine {
    Scene::Scene(std::string _sceneName) : sceneName{ _sceneName } {
        GameSceneSerializer::DeserializeScene(sceneName);
        ScriptSystem::GetInstance().UpdateMapData();
    }

    //When user click play to run their game
    bool Scene::Play() {
         if (!ScriptSystem::GetInstance().CompileCS()) {
            return false;
        }

        ScriptSystem::GetInstance().UpdateMapData();
        ScriptSystem::GetInstance().PlayInit();
        GameSceneSerializer::SerializeScene("temporary");

        return true;
    }

    void Scene::Stop() {
        CollisionSystem::GetInstance().Stop();
        DreamECS::GetInstance().ResetECS();
        GameSceneSerializer::DeserializeScene("temporary");
    }

    void Scene::Save() {
        ScriptSystem::GetInstance().CompileCS();
        ScriptSystem::GetInstance().UpdateMapData();
        GameSceneSerializer::SerializeScene(sceneName);
    }

    void Scene::Update(float dt, bool playing) {
        if (playing) {
            ScriptSystem::GetInstance().PlayRunTime();
            TransformCalculationSystem::GetInstance().ChildUpdate();
            CollisionSystem::GetInstance().Update(dt);
            PhysicsSystem::GetInstance().Update(DeltaTime::GetInstance().GetFixedDeltaTime());

            TransformCalculationSystem::GetInstance().Release();
        }

        CameraSystem::GetInstance().Update(dt);
       
        GraphicSystem::GetInstance().Render();
        UISystem::GetInstance().Render();

        DreamECS::GetInstance().ClearDestroyQueue();

        //LayerStack::Update();
        //LayerStack::Draw();
    }

    unsigned int Scene::EntityCount() {
        return DreamECS::GetInstance().GetUsedEntitySize();
    }

    std::string Scene::GetName() {
        return sceneName;
    }
}