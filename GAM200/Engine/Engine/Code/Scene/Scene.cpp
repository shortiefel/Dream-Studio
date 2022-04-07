/* Start Header**********************************************************************************/
/*
@file    Scene.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu   	100%
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
#include "Engine/Header/Event/FixedUpdateEvent.hpp"

//#include "Engine/Header/Layer/LayerStack.hpp"

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

#include "Engine/Header/Management/GameState.hpp"

#include "Engine/Header/Graphic/Picking2D.hpp"

#include "Engine/Header/ECS/System/SoundSystem.hpp"
#include "Engine/Header/Management/SoundManager.hpp"
#include "Engine/Header/ECS/Component/Sound/SoundComponent.hpp"

#include <thread>
#include <chrono>

namespace Engine {

    bool previousFocusState = true;

    std::string toLoad;
    bool loadFinish = true;
    std::future_status status;

    bool AsyncSceneLoading() {
        GameSceneSerializer::DeserializeScene(toLoad, dreamECSLoader, true);

        return true;
    }

    Scene::Scene(std::string _sceneName, bool _deserializeState) : sceneName{ _sceneName } {
        if (_deserializeState) {
            //if (sceneName != "Intro") 
            //if (!ignore) 
            if (_sceneName == "TutorialNew" || _sceneName == "NewGame")
            {
                loadFinish = false;
                toLoad = sceneName;
                GameSceneSerializer::DeserializeScene("Loading");
                asyncSceneThread = std::async(std::launch::async, AsyncSceneLoading);
            }
            else 
            {
                GameSceneSerializer::DeserializeScene(sceneName);
            }
        }
        else {
            GameSceneSerializer::DeserializeScene("temporary");
        }
        dreamECSGame->EndOfLoopUpdate();

        DeltaTime::GetInstance().SetTimeScale(1.f);
        CameraSystem::GetInstance().Update(0.f);

        ScriptSystem::GetInstance().UpdateMapData();
        if (GameState::GetInstance().GetPlaying()) {
            ScriptSystem::GetInstance().PlayInit();
        }
        //AI::AISystem::GetInstance().CreateGrid(Math::ivec2{ 20, 10 }, Math::ivec2{ 15, 15 });
        //AI::AISystem::GetInstance().SetRender();

        //if (gameBuild) Play();

        FontSystem::GetInstance().SetFadeToClear();
    }

    Scene::~Scene() {
        ScriptSystem::GetInstance().SaveCSData();

        ScriptSystem::GetInstance().DestroyChildDomain();

        Game::Grid::GetInstance().DestroyGrid();
    }

    //When user click play to run their game
    bool Scene::Play() {
        if (!ScriptSystem::GetInstance().CompileCS()) {
            return false;
        }
        GameState::GetInstance().SetPlaying(true);

        GameSceneSerializer::SerializeScene("temporary");
        ScriptSystem::GetInstance().UpdateMapData();
        ScriptSystem::GetInstance().PlayInit();


        DeltaTime::GetInstance().SetTimeScale(1.f);

        return true;
    }

    void Scene::Stop(bool deserialize) {
        GameSceneSerializer::ClearDeserializePool();

        ScriptSystem::GetInstance().SaveCSData();

        ScriptSystem::GetInstance().DestroyChildDomain();
        DeltaTime::GetInstance().SetTimeScale(1.f);

        SoundSystem::GetInstance().SoundStopAllSound();


        CollisionSystem::GetInstance().Stop();
        
        dreamECSGame->ResetECS();
        Game::Grid::GetInstance().DestroyGrid();

        if (deserialize) {
            GameState::GetInstance().SetPlaying(false);
            GameState::GetInstance().SetShouldDraw(false);
            //GameSceneSerializer::DeserializeScene("temporary");
        }

    }

    void Scene::Save() {
        ScriptSystem::GetInstance().CompileCS();
        ScriptSystem::GetInstance().UpdateMapData();

        GameSceneSerializer::SerializeScene(sceneName);
    }

#ifdef _GAME_BUILD
    void Scene::Update(float dt, bool playing, Math::vec2 game_viewportSize) {
#else
    void Scene::Update(float dt, bool playing, Math::vec2) {
#endif
        if (!loadFinish) {
            status = asyncSceneThread.wait_for(std::chrono::milliseconds(1));

            if (status == std::future_status::ready) {
                loadFinish = true;
                std::cout << "------------------Load finish-------------------------------\n";

                *dreamECSGame = std::move(*dreamECSLoader);

                {
                    auto& tem = dreamECSGame->GetComponentArrayData<TextureComponent>();
                    for (auto& i : tem) {
                        if (EntityId_Check(i.GetEntityId())) break;
                        ResourceManager::GetInstance().TextureGlfwCreate(i);
                    }
                }
                {
                    auto& tem = dreamECSGame->GetComponentArrayData<UIComponent>();
                    for (auto& i : tem) {
                        if (EntityId_Check(i.GetEntityId())) break;
                        ResourceManager::GetInstance().TextureGlfwCreate(i);
                    }
                }
                {
                    auto& tem = dreamECSGame->GetComponentArrayData<FontComponent>();
                    for (auto& i : tem) {
                        if (EntityId_Check(i.GetEntityId())) break;
                        GraphicImplementation::SetFont(&i, i.filepath);
                    }
                }

                if (GameState::GetInstance().GetPlaying()) {
                    ScriptSystem::GetInstance().UpdateMapData();
                    ScriptSystem::GetInstance().PlayInit();


                    DeltaTime::GetInstance().SetTimeScale(1.f);
                }

                dreamECSLoader->RestoreComponent<CameraComponent>();
                dreamECSLoader->RestoreComponent<TransformComponent>();
                dreamECSLoader->RestoreComponent<ColliderComponent>();
                dreamECSLoader->RestoreComponent<TextureComponent>();
                dreamECSLoader->RestoreComponent<RigidBodyComponent>();
                dreamECSLoader->RestoreComponent<ScriptComponent>();
                dreamECSLoader->RestoreComponent<UIComponent>();
                dreamECSLoader->RestoreComponent<FontComponent>();
                dreamECSLoader->RestoreComponent<SoundComponent>();
                dreamECSLoader->RestoreComponent<ParticleComponent>();
                dreamECSLoader->RestoreComponent<WaypointComponent>();
                dreamECSLoader->RestoreComponent<LightComponent>();
            }
        }

        bool focusState = Window::GetInstance().GetFocusStatus();
        if (!focusState) {
#ifdef _GAME_BUILD
            //Render game when not in focus
            GraphicSystem::GetInstance().Render(dt);
            UISystem::GetInstance().Render();
            FontSystem::GetInstance().Render(dt);
#endif
            if (focusState != previousFocusState) {
                SoundSystem::GetInstance().SoundSetPauseAllSound(true);
                previousFocusState = focusState;
            }
            return;
        }
        if (focusState != previousFocusState) {
            SoundSystem::GetInstance().SoundSetPauseAllSound(false);
            previousFocusState = focusState;
        }

        if (playing) {
            //float timeScale = DeltaTime::GetInstance().GetTimeScale();
            //if (timeScale > 0.f && !Math::EpsilonCheck(timeScale)) {
                ScriptSystem::GetInstance().PlayRunTime();
                //TransformCalculationSystem::GetInstance().ChildUpdate();
                int totalStep = DeltaTime::GetInstance().GetNumberOfSteps();
                for (int step = 0; step < totalStep; step++) {
                    CollisionSystem::GetInstance().Update(dt);
                    PhysicsSystem::GetInstance().Update(DeltaTime::GetInstance().GetFixedDeltaTime());

                    FixedUpdateEvent event;
                    EventDispatcher::SendEvent(event);
                }
            //}
                //auto tem = dreamECSGame->GetUsedConstEntityMap();
                //for (auto [id, ent] : tem) {
                //    std::cout << id << " with parent " << ent.parent << " with child count " << ent.child.size() << "\n";
                //}
                //std::cout << "end\n";
        }


        CameraSystem::GetInstance().Update(dt);


        //GraphicImplementation::FadeScene(3.f, dt, camMatrix);

        
        if (Input::IsKeyPressed(Input_KeyCode::F)) {
            std::cout << "List of all entities \n";
            for (auto& [id, ent] : dreamECSGame->GetUsedEntityMap()) {
                std::cout << id << " " << ent.name << "\n";
            }
            std::cout << " \n\n\n";

            std::cout << "List of all entities \n";
            for (auto& [id, ent] : dreamECSLoader->GetUsedEntityMap()) {
                std::cout << id << " " << ent.name << "\n";
            }
            std::cout << " \n\n\n";
        }

        //if (Input::IsKeyPressed(Input_KeyCode::E)) {
        //    //Deserialize will be async and once done do the rest below
        //    GameSceneSerializer::DeserializeScene("NewGame", dreamECSLoader, true);
        //    //GameSceneSerializer::DeserializeScene("NewGame", dreamECSLoader, true);
        //
        //    *dreamECSGame = std::move(*dreamECSLoader);
        //
        //    {
        //        auto& tem = dreamECSGame->GetComponentArrayData<TextureComponent>();
        //        for (auto& i : tem) {
        //            if (EntityId_Check(i.GetEntityId())) break;
        //            ResourceManager::GetInstance().TextureGlfwCreate(i);
        //        }
        //    }
        //    {
        //        auto& tem = dreamECSGame->GetComponentArrayData<UIComponent>();
        //        for (auto& i : tem) {
        //            if (EntityId_Check(i.GetEntityId())) break;
        //            ResourceManager::GetInstance().TextureGlfwCreate(i);
        //        }
        //    }
        //
        //    if (GameState::GetInstance().GetPlaying()) {
        //        ScriptSystem::GetInstance().UpdateMapData();
        //        ScriptSystem::GetInstance().PlayInit();
        //
        //
        //        DeltaTime::GetInstance().SetTimeScale(1.f);
        //    }
        //
        //    dreamECSLoader->RegisterComponent<CameraComponent>();
        //    dreamECSLoader->RegisterComponent<TransformComponent>();
        //    dreamECSLoader->RegisterComponent<ColliderComponent>();
        //    dreamECSLoader->RegisterComponent<TextureComponent>();
        //    dreamECSLoader->RegisterComponent<RigidBodyComponent>();
        //    dreamECSLoader->RegisterComponent<ScriptComponent>();
        //    dreamECSLoader->RegisterComponent<UIComponent>();
        //    dreamECSLoader->RegisterComponent<FontComponent>();
        //    dreamECSLoader->RegisterComponent<SoundComponent>();
        //    dreamECSLoader->RegisterComponent<ParticleComponent>();
        //    dreamECSLoader->RegisterComponent<WaypointComponent>();
        //    dreamECSLoader->RegisterComponent<LightComponent>();
        //}
        
#ifdef _GAME_BUILD
        //Default 2d picking
        Math::vec2 pos = Input::GetMousePosition();
        pos.y = Window::GetInstance().GetWindowSize().y - pos.y;

        Math::mat3 inverseCamMatrix = Math::Inverse(Engine::CameraSystem::GetInstance().GetTransform());

        Engine::Graphic::PickingCheckCollider(Math::vec3{ pos.x, pos.y, 1.f }, game_viewportSize, inverseCamMatrix,
            [&](const Engine::Entity& entity) { Engine::Graphic::RecordMouseOverlap(entity.id, true);  },
            [&](const Engine::Entity& entity) { Engine::Graphic::RecordMouseOverlap(entity.id, false); },
            Math::Inverse(Engine::CameraSystem::GetInstance().GetTransformUI()));

        GraphicSystem::GetInstance().Render(dt);
        UISystem::GetInstance().Render();
        FontSystem::GetInstance().Render(dt);
#else
        //if (Input::IsKeyPressed(Input_KeyCode::F)) {
        //    Window::GetInstance().ToggleFullscreen(); 
        //}
#endif

       
        //SoundSystem::GetInstance().SoundUpdate();


        dreamECSGame->EndOfLoopUpdate();

    }

    unsigned int Scene::EntityCount() {
        return dreamECSGame->GetUsedEntitySize();
    }

    std::string Scene::GetName() {
        return sceneName;
    }
}