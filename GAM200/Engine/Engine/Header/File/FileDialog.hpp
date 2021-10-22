/* Start Header**********************************************************************************/
/*
@file    FileDialog.hpp
@author  Goh See Yong, Denise  	g.seeyongdenise@digipen.edu
@date    21/10/2021
\brief
This file contain the File Dialog declaration

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef FILE_DIALOG_HPP
#define FILE_DIALOG_HPP

#include "Engine/Header/pch.hpp"
#include <filesystem>

namespace Engine
{
	struct FileDialogResult
	{
		std::string filepath;
		const char* filename;
		const char* extension;
	};

	namespace FileDialog
	{
		bool OpenFileName(const std::string& initialPath,
			FileDialogResult& result,
			std::vector<std::pair<std::string, std::string>> extensionFilters = { {"All Files", "*.*"} });

		bool OpenFolderName(const std::string initialPath, FileDialogResult& result);

		bool SaveFileName(
			const std::string& initialPath,
			FileDialogResult& result,
			std::vector<std::pair<std::string, std::string>> extensionFilters = { {"All Files", "*.*"} },
			std::string extToAppend = "");
	}
}
#endif