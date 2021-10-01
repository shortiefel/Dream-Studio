/* Start Header**********************************************************************************/
/*
@file    GUIWindow.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
         Goh See Yong, Denise   g.seeyongdenise@digipen.edu
         Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
@date    26/07/2021
\brief
This file contain the GUIWindow declaration


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef GUI_WINDOW_HPP
#define GUI_WINDOW_HPP

#include <Imgui/imgui.h>
#include <filesystem>

namespace Editor {
    namespace GUI_Window {
        //bool for dockspace (will always be true)
        static bool dockspace_bool = true;
        //Flags for the background window for windows to dock to
        static ImGuiWindowFlags dockspace_window_flags = 0;
        static ImGuiDockNodeFlags dockspace_dock_flags = 0;

        static ImGuiWindowFlags window_flags = 0;

        static bool hierarchy_bool = true;
        static bool inspector_bool = true;
        static bool gameWin_bool = true;
        static bool sceneWin_bool = true;
        static bool asset_bool = true;
        static bool playStop_bool = true;

        /*-------------------------------------------------------------------------------------------------
        Windows creation: Hierarchy, Inspector, Game window, Scene window
        -------------------------------------------------------------------------------------------------*/
        //Set up all variable for GUI_Window
        void    GUI_Settings_Setup();
        //Note: This function should be called first
        //Create a docking space for future windows to be docked into it
        void	GUI_DockSpace();
        void    GUI_HeaderPanel();
        void	GUI_Hierarchy();
        void	GUI_Inspector();
        void	GUI_GameWindow(ImTextureID& gameWinTex);
        void	GUI_SceneWindow(ImTextureID& sceneWinTex);
        void    GUI_ContentBrowserPanel();

        static std::filesystem::path _currentDirectory = "Assets";
    }
}

#endif