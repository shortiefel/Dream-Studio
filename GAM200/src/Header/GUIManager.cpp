#include "Debug Tools/Logging.hpp"
#include "GUIManager.hpp"
#include "../../External Resources/Imgui/imgui.h"
#include "../../External Resources/Imgui/imgui_impl_glfw.h"
#include "../../External Resources/Imgui/imgui_impl_opengl3.h"

void GUIManager::Create(GLFWwindow* window, const char* glsl_version) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiBackendFlags_HasMouseCursors;

    ImGui::StyleColorsDark();

    if (ImGui_ImplGlfw_InitForOpenGL(window, true)) LOG_ERROR("Error: Imgui not initialised");
    ImGui_ImplOpenGL3_Init(glsl_version);
}