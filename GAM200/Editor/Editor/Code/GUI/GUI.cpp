/* Start Header**********************************************************************************/
/*
@file    GUI.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    16/06/2021
\brief
This file contain the GUI definition


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Editor/Header/GUI/GUI.hpp"
#include "Editor/Header/GUI/GUIWindow.hpp"

#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Engine/Header/Graphic/Graphic.hpp"
#include "Engine/Header/Window.hpp"
#include "Engine/Header/Management/Settings.hpp"

//External Resources
#include <Imgui/imgui.h>
#include <Imgui/imgui_internal.h>
#include <Imgui/imgui_impl_glfw.h>
#include <Imgui/imgui_impl_opengl3.h>



namespace Editor {
    GUI* GUI::m_instance;
    unsigned int GUI::gameWinFBO, GUI::gameWinTex,
        GUI::sceneWinFBO, GUI::sceneWinTex;


    void GUI::Update() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        /*bool show_demo_window = true;
        ImGui::ShowDemoWindow(&show_demo_window);*/

        GUI_Window::GUI_DockSpace();

        GUI_Window::GUI_GameWindow(gameWinTex);
        GUI_Window::GUI_SceneWindow(sceneWinTex);
        GUI_Window::GUI_Hierarchy();
        GUI_Window::GUI_Inspector();
    }

    void GUI::Draw() {
        //Render 
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        //Allow drawing menu outside of window-----------------------------------
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
        //-----------------------------------
    }

    bool GUI::Create(GLFWwindow* window, const char* glsl_version) {
        if (m_instance) LOG_WARNING("An instance of GUI already exist!");
        m_instance = new GUI;
        LOG_INSTANCE("GUI created");

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        //Allow drawing menu outside of window-----------------------------------
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows


        ImGui::StyleColorsDark();

        if (!ImGui_ImplGlfw_InitForOpenGL(window, true)) {
            LOG_ERROR("Error: Imgui not initialised");
            return false;
        }
        ImGui_ImplOpenGL3_Init(glsl_version);

        GUI_Window::GUI_Settings_Setup();

        Engine::GraphicImplementation::CreateFramebuffer(Engine::Settings::gameWidth, Engine::Settings::gameHeight, &gameWinFBO, &gameWinTex);
        Engine::GraphicImplementation::CreateFramebuffer(Engine::Settings::windowWidth, Engine::Settings::windowHeight, &sceneWinFBO, &sceneWinTex);

        return true;
    }

    void GUI::Destroy() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        delete m_instance;
        LOG_INSTANCE("GUI destroyed");
    }

    void GUI::SetGameFBO() {
        Engine::GraphicImplementation::SetFramebuffer(gameWinFBO);
    }

    void GUI::SetSceneFBO() {
        Engine::GraphicImplementation::SetFramebuffer(sceneWinFBO);
    }
}
