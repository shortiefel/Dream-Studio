/* Start Header**********************************************************************************/
/*
@file    FileWindowDialog.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu			100%
@date    27/10/2021
\brief
This contain the definition of FileWindowDialog


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include <Windows.h>
#include "Engine/Header/pch.hpp"
#include <GLFW/glfw3.h>
#include <commdlg.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include "Engine/Header/Management/FileWindowDialog.hpp"

#include "Engine/Header/Window.hpp"



namespace Engine {
	std::string GetNameFromType(File_Dialog_Type ft) {
		switch (ft) {
		case File_Dialog_Type::None:
			return std::string{};
		case File_Dialog_Type::Audio:
			return "Audio";
		case File_Dialog_Type::Fonts:
			return "Fonts";
		case File_Dialog_Type::Prefab:
			return "Prefab";
		case File_Dialog_Type::Scenes:
			return "Scenes";
		case File_Dialog_Type::Scripts:
			return "Scripts";
		case File_Dialog_Type::Shaders:
			return "Shaders";
		case File_Dialog_Type::Textures:
			return "Textures";
		}
		return std::string{};
	}

	std::string FileWindowDialog::OpenFile(const char* filter, File_Dialog_Type ft) {
		OPENFILENAMEA ofna;
		CHAR _file[260] = { 0 };
		ZeroMemory(&ofna, sizeof(OPENFILENAME));
		ofna.lStructSize = sizeof(OPENFILENAME);
		ofna.hwndOwner = glfwGetWin32Window(Window::GetInstance().GetGLFWwindow());
		ofna.lpstrFile = _file;
		ofna.nMaxFile = sizeof(_file);
		ofna.lpstrFilter = filter;
		ofna.nFilterIndex = 1;
		ofna.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
		std::string initDir { ".\\Assets" + GetNameFromType(ft) };
		ofna.lpstrInitialDir = initDir.c_str();

		if (GetOpenFileNameA(&ofna) == TRUE) {
			return ofna.lpstrFile;
		}

		return std::string();
	}

	std::string FileWindowDialog::SaveFile(const char* filter, File_Dialog_Type ft) {
		OPENFILENAMEA ofna;
		CHAR _file[260] = { 0 };
		ZeroMemory(&ofna, sizeof(OPENFILENAME));
		ofna.lStructSize = sizeof(OPENFILENAME);
		ofna.hwndOwner = glfwGetWin32Window(Window::GetInstance().GetGLFWwindow());
		ofna.lpstrFile = _file;
		ofna.nMaxFile = sizeof(_file);
		ofna.lpstrFilter = filter;
		ofna.nFilterIndex = 1;
		ofna.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
		std::string initDir{ ".\\Assets" + GetNameFromType(ft) };
		ofna.lpstrInitialDir = initDir.c_str();

		if (GetSaveFileNameA(&ofna) == TRUE) {
			return ofna.lpstrFile;
		}

		return std::string();
	}
}