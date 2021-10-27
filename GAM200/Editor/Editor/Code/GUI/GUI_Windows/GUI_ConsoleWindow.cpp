/* Start Header**********************************************************************************/
/*
@file    GUI_ConsoleWindow.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    18/08/2021
\brief
This file contain the Console window definition


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Editor/Header/GUI/GUI_Windows/GUI_ConsoleWindow.hpp"
#include "Engine/Header/Script/ScriptInternalCall.hpp"

namespace Editor {
    namespace GUI_Windows {
        GUI_ConsoleWindow gui_ConsoleWindow;

        const char* StrDuplicate(const char* s) {
            size_t len = strlen(s) + 1;
            if (len <= 0) return "";
            char* buf = new char[len];

            return (const char*)memcpy(buf, s, len);
        }

        ConsoleString::ConsoleString(ConsoleString&& _rhs) noexcept :
            consoleText{ _rhs.consoleText } {
            _rhs.consoleText = nullptr;
        }

        /*ConsoleString::ConsoleString(const char* _consoleText) :
            consoleText{ StrDuplicate(_consoleText) }, stringType{ _stringType } { }*/
        ConsoleString::ConsoleString(const char* _consoleText) :
            consoleText{ StrDuplicate(_consoleText) } { }

        //ConsoleString::~ConsoleString() { 
        //    printf(" deleting stuff \n"); 
        //    //delete[] consoleText;
        //}

        void GUI_ConsoleWindow::GUI_Console(bool* console_bool, ImGuiWindowFlags window_flags) {
            if (*console_bool) {
                ImGui::Begin("Console", console_bool, window_flags);

                if (ImGui::SmallButton("Clear")) { ClearLog(); }

                ImGui::Separator();

                //loop through list of strings to display
                const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
                ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar);


                for (auto& item : Items) {
                    //ImGui::Dummy(ImVec2(0.0f, 5.f)); //Add Space
                    ImGui::TextUnformatted(item.consoleText);
                    //ImGui::Dummy(ImVec2(0.0f, 15.f)); //Add Space
                    ImGui::Separator();
                }

                if (ScrollToBottom)
                    ImGui::SetScrollHereY(1.0f);
                ScrollToBottom = false;

                ImGui::EndChild();

                ImGui::End();
            }

        }

        void GUI_ConsoleWindow::Add_To_Console(ConsoleString&& _consoleString) {
            ScrollToBottom = true;
            Items.push_back(std::move(_consoleString));
        }

        void GUI_ConsoleWindow::Create() {
            Engine::SetConsoleWriteFunc(
                [](std::string message) {
                    GUI_Console_Add(ConsoleString{ message.c_str() });
                }
                );
        }

        void GUI_ConsoleWindow::ClearLog() {
            for (auto& item : Items)
                delete[] item.consoleText;
            Items.clear();
        }

        GUI_ConsoleWindow::~GUI_ConsoleWindow() {
            ClearLog();
        }

        //Functionality to access Console
        void GUI_Console_Add(ConsoleString&& text) {
            gui_ConsoleWindow.Add_To_Console(std::move(text));
        }

        void GUI_Console_Clear() {
            gui_ConsoleWindow.ClearLog();
        }

        void GUI_Console(bool* console_bool, ImGuiWindowFlags window_flags) {
            gui_ConsoleWindow.GUI_Console(console_bool, window_flags);
        }

        void GUI_Console_Create() {
            gui_ConsoleWindow.Create();
        }

    }
}