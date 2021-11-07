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
#include "Engine/Header/Scene/Prefab.hpp"

#include "Engine/Header/Window.hpp"
#include "Engine/Header/Event/EventDispatcher.hpp"
#include "Engine/Header/Layer/LayerStack.hpp"

#include "Engine/Header/Time/DeltaTime.hpp"

#include "Engine/Header/Grid/Grid.hpp"

#include "Engine/Header/Serialize/GameSceneSerializer.hpp"

#include "Engine/Header/ECS/Factory.hpp"
#include "Engine/Header/ECS/DreamECS.hpp"

//#include "Engine/Header/Debug Tools/Profiler.hpp"

//Components
#include "Engine/Header/ECS/Component/ComponentList.hpp"
//Systems
#include "Engine/Header/ECS/System/SystemList.hpp"


#include "Engine/Header/AI/AISystem.hpp"

namespace Engine {
    Scene::Scene(std::string _sceneName, bool tem) : sceneName{ _sceneName } {
        if (!tem)
            GameSceneSerializer::DeserializeScene(sceneName);
        else
            GameSceneSerializer::DeserializeScene("temporary");

        ScriptSystem::GetInstance().UpdateMapData();
        //AI::AISystem::GetInstance().CreateGrid(Math::ivec2{ 20, 10 }, Math::ivec2{ 15, 15 });
        //AI::AISystem::GetInstance().SetRender();
    }

    Scene::~Scene() {
        Game::Grid::GetInstance().DestroyGrid();
    }

    //When user click play to run their game
    bool Scene::Play() {
        if (!ScriptSystem::GetInstance().CompileCS(true)) {
            return false;
        }

        GameSceneSerializer::SerializeScene("temporary");
        ScriptSystem::GetInstance().UpdateMapData();
        ScriptSystem::GetInstance().PlayInit();

        return true;
    }

    void Scene::Stop(bool deserialize) {
        CollisionSystem::GetInstance().Stop();
        dreamECSGame->ResetECS();
        Game::Grid::GetInstance().DestroyGrid();

        if (deserialize) {
            //std::cout << "deserialize\n";
            GameSceneSerializer::DeserializeScene("temporary");
        }
        
    }

    void Scene::Save() {
        ScriptSystem::GetInstance().CompileCS(false);
        ScriptSystem::GetInstance().UpdateMapData();

        GameSceneSerializer::SerializeScene(sceneName);
    }

    void Scene::Update(float dt, bool playing) {
        if (playing) {
            ScriptSystem::GetInstance().PlayRunTime();
            //TransformCalculationSystem::GetInstance().ChildUpdate();
            CollisionSystem::GetInstance().Update(dt);
            PhysicsSystem::GetInstance().Update(DeltaTime::GetInstance().GetFixedDeltaTime());
        }

        CameraSystem::GetInstance().Update(dt);
       
        GraphicSystem::GetInstance().Render();
        //TransformCalculationSystem::GetInstance().Release();
        FontSystem::GetInstance().Render();
        UISystem::GetInstance().Render();

        dreamECSGame->ClearDestroyQueue();

        //LayerStack::Update();
        //LayerStack::Draw();
    }

    unsigned int Scene::EntityCount() {
        return dreamECSGame->GetUsedEntitySize();
    }

    std::string Scene::GetName() {
        return sceneName;
    }
}