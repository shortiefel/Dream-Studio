/* Start Header**********************************************************************************/
/*
@file    GUIWindow.hpp
@author  Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
         Goh See Yong, Denise   g.seeyongdenise@digipen.edu
        
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
#include "Engine/Header/Graphic/FrameBuffer.hpp"

namespace Editor {
    namespace GUI_Windows {
        //void    All_Windows(const ImTextureID& gameWinTex, const ImTextureID& sceneWinTex);
        void    All_Windows(const Engine::Graphic::FrameBuffer& gameWinFBO, const Engine::Graphic::FrameBuffer& sceneWinFBO);
        /*int     GetSceneSizeX();
        int     GetSceneSizeY();*/

        //Set up all variable for GUI_Window
        void    GUI_Settings_Setup();
        //Note: This function should be called first
        //Create a docking space for future windows to be docked into it
        void	GUI_DockSpace();

        static std::filesystem::path _currentDirectory = "Assets";
    }
}

#endif