/* Start Header**********************************************************************************/
/*
@file    Scene.cpp
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

#include "Engine/Header/Scene/Scene.hpp"
#include "Engine/Header/Debug Tools/Logging.hpp"

#include "Engine/Header/Window.hpp"
#include "Engine/Header/Event/EventDispatcher.hpp"
#include "Engine/Header/Layer/LayerStack.hpp"
//#include "Layer/GUILayer.hpp"

#include "Engine/Header/Script/ScriptEngine.hpp"
#include "Engine/Header/Management/GameSceneSerializer.hpp"

#include "Engine/Header/ECS/Factory.hpp"
#include "Engine/Header/ECS/ECSWrapper.hpp"

//Components
#include "Engine/Header/ECS/Component/ComponentList.hpp"
//Systems
#include "Engine/Header/ECS/System/SystemList.hpp"

namespace Engine {
    //extern Coordinator gCoordinator;

    bool Scene::playing = false;
    std::string Scene::fullPathName = std::string{};

    
    //Save Scene
    //Return false if fail (fail to compile)
    bool SceneSave();
    //Shortcut key for scene
    //E.g: Ctrl p (play / stop), Ctrl s (save)
    bool SceneHotKey(const KeyPressedEvent& e);

    //Entity temcam, temcam2, temcam3; int num = 1;//Temporary

    void Scene::Create(std::string scenename) {
        //Serialization
        //Read from text file all information

        //Reset all system

        //Test code--------------------------------------------
        //W A S D, I J K L and arrow keys to move
        //V to switch camera

        /*Entity ent2 = gCoordinator.createEntity();
        gCoordinator.AddComponent(
            ent2,
            Transform{ MathD::Vec2{50.f,0.f}, MathD::Vec2{200.f,200.f}, "Circle" });
        gCoordinator.AddComponent(ent2,
            Texture{ "Assets/Textures/test2.png" });*/

        //gCoordinator.AddComponent(ent,
        //        Collider{ ColliderType::SQUARE, true });
        ///*gCoordinator.AddComponent(ent,
        //    Custom_Script{ std::make_shared<PlayerController>() });*/



        //Entity ent1 = gCoordinator.createEntity();
        //gCoordinator.AddComponent(
        //    ent1,
        //    Transform{ MathD::Vec2{-100.f,0.f}, MathD::Vec2{100.f,100.f}, "Square" });
        //gCoordinator.AddComponent(ent1,
        //    Collider{ ColliderType::SQUARE, true });
        ///*gCoordinator.AddComponent(ent1,
        //    Custom_Script{ std::make_shared<AnotherController>() });*/
        //gCoordinator.AddComponent(ent1,
        //    Texture{ "Assets/Textures/test2.png" });



        //temcam = gCoordinator.createEntity();
        //gCoordinator.AddComponent(
        //    temcam,
        //    Transform{ MathD::Vec2{0.f,0.f}, MathD::Vec2{0.f,0.f} });

        //gCoordinator.AddComponent(
        //    temcam,
        //    Camera2D{ true });
        ///*gCoordinator.AddComponent(temcam,
        //    Custom_Script{ std::make_shared<CameraController>() });*/

        //temcam2 = gCoordinator.createEntity();
        //gCoordinator.AddComponent(
        //    temcam2,
        //    Transform{ MathD::Vec2{240.f,100.f}, MathD::Vec2{0.f,0.f} });
        //gCoordinator.AddComponent(
        //    temcam2,
        //    Camera2D{ false });
        ///*gCoordinator.AddComponent(temcam2,
        //    Custom_Script{ std::make_shared<CameraController>() });*/


        //temcam3 = gCoordinator.createEntity();
        //gCoordinator.AddComponent(
        //    temcam3,
        //    Transform{ MathD::Vec2{-40.f,-240.f}, MathD::Vec2{0.f,0.f} });
        //gCoordinator.AddComponent(
        //    temcam3,
        //    Camera2D{ false });
        ///*gCoordinator.AddComponent(temcam3,
        //    Custom_Script{ std::make_shared<CameraController>() });*/

            //--------------------------------------------------

            /*Factory::InstantiateCircle();
            Factory::InstantiateSquare();*/

        fullPathName = "Assets/Scene/" + scenename + ".json";
        GameSceneSerializer::Deserialize(fullPathName);
        

        ScriptEngine::UpdateMapData();
    }

    //When user click play to run their game
    void Scene::Play() {
        //Compile the script
        //Serialize everything
        //Restart Mono
        //Init game
        std::cout << "Playing \n";
        if (!SceneSave()) return;
        ScriptEngine::PlayInit();
    }

    //When user click stop to run their game
    void Scene::Stop() {
        //Deserialize everything
        ScriptEngine::Stop();
        CollisionSystem::Stop();
        DreamECS::DestroyAllEntity();

        GameSceneSerializer::Deserialize(fullPathName);
        std::cout << "Stopping \n";
    }

    /*
    dt - delta time
    defaultRender - whether to use default rendering or not
    */
    void Scene::Update(float dt, bool defaultRender) {
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
        if (playing) {
            ScriptEngine::PlayRunTime();
            CollisionSystem::Update(dt);
        }

        CameraSystem::Update(dt);

        if (defaultRender) {
            //GraphicSystem::Update(dt);
            GraphicSystem::Render();
        }

        

        LayerStack::Update();
        LayerStack::Draw();
    }

    void Scene::Destroy() {
        if (playing) Scene::Stop(); 
        //Destroy in reverse order
        //Remove all entity
    }

    std::string& Scene::GetFullPath() {
        return fullPathName;
    }

    bool SceneHotKey(const KeyPressedEvent& e) {
        if (Input::IsKeyPressed(Input_KeyCode::Control)) {
            //Play / Stop
            if (e.GetKeyCode() == Input_KeyCode::P) {
                Scene::InvertPlaying();
                return true;
            }

            //Save
            else if (e.GetKeyCode() == Input_KeyCode::S) {
                if (Scene::GetPlaying() != true) {
                    std::cout << "Saving... \n";
                    SceneSave();
                    return true;
                }

                std::cout << "Scene is Playing. unable to Save... \n";
                return false;
            }
        }

        return true;
    }

    KeyPressedFP Scene::GetSceneHotKey() {
        return SceneHotKey;
    }

    bool SceneSave() {
        if (!ScriptEngine::CompileCS()) {
            std::cout << "Fail to compile \n";
            Scene::SetPlaying(false);
            return false;
        }

        ScriptEngine::UpdateMapData();
        //Change to sceneName (might be fullName(path + name) instead)
        GameSceneSerializer::Serialize(Scene::GetFullPath());

        return true;
    }

    void Scene::InvertPlaying() {
        playing = !playing;

        if (playing) Play();
        else Stop();
    }

    void Scene::SetPlaying(bool state) {
        playing = state;

        if (playing) Play();
        else Stop();
    }

    bool Scene::GetPlaying() {
        return playing;
    }
}