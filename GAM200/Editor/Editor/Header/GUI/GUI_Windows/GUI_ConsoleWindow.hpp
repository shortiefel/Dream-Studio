/* Start Header**********************************************************************************/
/*
@file    GUI_ConsoleWindow.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    18/08/2021
\brief
This file contain the Console window declaration


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef CONSOLE_WINDOW_HPP
#define CONSOLE_WINDOW_HPP

#include <memory>
#include <Imgui/imgui.h>
#include <ctype.h> //toupper
#include <string>

namespace Editor {
    namespace GUI_Windows {

        const char* StrDuplicate(const char* s);

        /*enum class ConsoleStringType {
            DEFAULT_STRING = 0,
            ERROR_STRING
        };*/

        struct ConsoleString {
            const char* consoleText;
            //ConsoleStringType stringType;

            ConsoleString(ConsoleString&& _rhs) noexcept;
            //ConsoleString(const char* _consoleText, ConsoleStringType _stringType = ConsoleStringType::DEFAULT_STRING);
            ConsoleString(const char* _consoleText);
            //~ConsoleString();
        };

        class GUI_ConsoleWindow {
        public:
            void ClearLog();
            void GUI_Console(bool* console_bool);
            void Add_To_Console(ConsoleString&& text);
            void Create();

            GUI_ConsoleWindow() = default;
            ~GUI_ConsoleWindow();
        private:
            bool ScrollToBottom;
            ImVector<ConsoleString> Items;
            ImGuiTextFilter filter;
        };

        //Access to the GUI_ConsoleWindow
        void GUI_Console_Add(ConsoleString&& text);
        void GUI_Console_Clear();
        void GUI_Console(bool* console_bool);
        void GUI_Console_Create();

#if 0
        //-----------------------------------------------------------------------------
        // [SECTION] Example App: Debug Console / ShowExampleAppConsole()
        //-----------------------------------------------------------------------------

        // Demonstrate creating a simple console window, with scrolling, filtering, completion and history.
        // For the console example, we are using a more C++ like approach of declaring a class to hold both data and functions.
        struct ExampleAppConsole
        {
            char                  InputBuf[256];
            ImVector<char*>       Items;
            ImVector<const char*> Commands;
            ImVector<char*>       History;
            int                   HistoryPos;    // -1: new line, 0..History.Size-1 browsing history.
            ImGuiTextFilter       Filter;
            bool                  AutoScroll;
            bool                  ScrollToBottom;

            ExampleAppConsole();
            ~ExampleAppConsole();

            // Portable helpers
            static int   Stricmp(const char* s1, const char* s2);
            static int   Strnicmp(const char* s1, const char* s2, int n);
            static char* Strdup(const char* s);
            static void  Strtrim(char* s);

            void    ClearLog();
            void    AddLog(const char* fmt, ...) IM_FMTARGS(2);
            void    Draw(const char* title, bool* p_open);
            void    ExecCommand(const char* command_line);

            // In C++11 you'd be better off using lambdas for this sort of forwarding callbacks
            static int TextEditCallbackStub(ImGuiInputTextCallbackData* data);
            int     TextEditCallback(ImGuiInputTextCallbackData* data);
        };

        void ShowExampleAppConsole(bool* p_open);
#endif

    }
}

#endif