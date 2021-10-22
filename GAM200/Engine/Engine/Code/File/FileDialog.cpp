/* Start Header**********************************************************************************/
/*
@file    FileDialog.cpp
@author  Goh See Yong, Denise  	g.seeyongdenise@digipen.edu
@date    21/10/2021
\brief
This file has the function definition for FileDialog.


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

// This file is only built on windows systems
#ifdef _WIN32
#include "Engine/Header/File/FileDialog.hpp"
#include "Engine/Header/Application.hpp"
#include "Engine/Header/Window.hpp"
#include "Engine/Header/Debug Tools/Logging.hpp"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
#include <commdlg.h>
#include <shobjidl_core.h>
#include <shlobj.h>
#include <knownfolders.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>


namespace Engine
{
	namespace FileDialog
	{
		static char ResultBuffer[MAX_PATH];

		bool OpenFileName(
			const std::string& initialPath,
			FileDialogResult& fileResult,
			std::vector<std::pair<std::string, std::string>> extensionFilters)

		{
			////For logging purposes
			//w_data.title = ttitle;
			//w_data.width = twidth;
			//w_data.height = theight;

			//aspectRatio = (float)w_data.height / (float)w_data.width;

			//HWND wnd = glfwCreateWindow((int)w_data.width, (int)w_data.height, w_data.title.c_str(), nullptr, nullptr);

			std::string filters = "";
			for (auto pair : extensionFilters)
			{
				filters += pair.first + '\0';
				filters += pair.second + '\0';
			}
			filters += '\0';

			OPENFILENAMEA dialogStruct;
			dialogStruct.lStructSize = sizeof(OPENFILENAMEA);
			//dialogStruct.hwndOwner = wnd;
			dialogStruct.hInstance = NULL;
			dialogStruct.lpstrFilter = filters.c_str();
			dialogStruct.lpstrCustomFilter = NULL;
			dialogStruct.nMaxCustFilter = 0;
			dialogStruct.nFilterIndex = 0;
			dialogStruct.lpstrFile = ResultBuffer; // Output filename
			dialogStruct.lpstrFile[0] = NULL;
			dialogStruct.nMaxFile = MAX_PATH;
			dialogStruct.lpstrFileTitle = NULL;// (LPSTR)initialPath.c_str();
			dialogStruct.nMaxFileTitle = 0; // initialPath.length();
			dialogStruct.lpstrInitialDir = NULL; // initialPath.c_str();
			dialogStruct.lpstrTitle = "My Custom Title";
			dialogStruct.Flags = 0; // TODO: Consider adding flags to this function
			dialogStruct.nFileOffset = 0;
			dialogStruct.nFileExtension = 0;
			dialogStruct.lpstrDefExt = NULL;

			bool result = GetOpenFileNameA(&dialogStruct);
			if (result)
			{
				fileResult.filepath = std::string(dialogStruct.lpstrFile);
				fileResult.filename = fileResult.filepath.c_str() + dialogStruct.nFileOffset;
				fileResult.extension = fileResult.filepath.c_str() + dialogStruct.nFileExtension;
			}

			return result;
		}
	}
}
#endif