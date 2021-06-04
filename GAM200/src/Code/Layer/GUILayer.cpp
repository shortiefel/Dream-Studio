#include "../../Header/Debug Tools/Logging.hpp"
#include "../../Header/Layer/GUILayer.hpp"
#include "../../Header/pch.hpp"

#include "../../../External Resources/Imgui/imgui.h"
#include "../../../External Resources/Imgui/imgui_impl_glfw.h"
#include "../../../External Resources/Imgui/imgui_impl_opengl3.h"

//Static ----------------------------------------------------------------------------------------
GUILayer* GUILayer::m_instance;

bool GUILayer::Create(GLFWwindow* window, const char* glsl_version) {
    if (m_instance) LOG_WARNING("An instance of GUILayer already exist!");
    m_instance = new GUILayer;
    LOG_INSTANCE("GUILayer created");

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

    return true;
}


void GUILayer::Destroy() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    delete m_instance;
    LOG_INSTANCE("GUILayer destroyed");
}
//-----------------------------------------------------------------------------------------------------------------------------------

void GUILayer::Draw() {
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

void GUILayer::Update() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();



    bool show_demo_window = true;
    ImGui::ShowDemoWindow(&show_demo_window);
    //ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
    //ImGui::DockSpaceOverViewport();

    ImGui::Begin("Hello, world!");
    ImGui::Text("Hello from another window!");
    ImGui::End();
}

bool GUILayer::OnEvent(Event& e) {
    return false;
}