/* Start Header**********************************************************************************/
/*
@file    FileWindowDialog.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    27/10/2021
\brief
This contain the definition of FileWindowDialog


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Management/FileWindowDialog.hpp"

#include "Engine/Header/Window.hpp"

#include <GLFW/glfw3.h>
#include <Windows.h>
#include <commdlg.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>


namespace Engine {
	std::string FileWindowDialog::OpenFile(const char* filter) {
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
		if (GetOpenFileNameA(&ofna) == TRUE) {
			return ofna.lpstrFile;
		}

		return std::string();
	}

	std::string FileWindowDialog::SaveFile(const char* filter) {
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
		if (GetSaveFileNameA(&ofna) == TRUE) {
			return ofna.lpstrFile;
		}

		return std::string();
	}
}