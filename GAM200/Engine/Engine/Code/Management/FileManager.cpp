/* Start Header**********************************************************************************/
/*
@file    FileManager.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    26/09/2021
\brief
This file contain the FileManager definition


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug tools/Logging.hpp"

#include "Engine/Header/Management/FileManager.hpp"

#include <iostream>
#include <stdio.h>

namespace Engine {
	FILE* FileManager::Open_File(std::string _fullPathFileName) {

		FILE* fp = nullptr;
		//std::cout << "name file " << _fullPathFileName << "\n";
		if (fileMap.find(_fullPathFileName) != fileMap.end()) {
			fp = fileMap[_fullPathFileName];
			fseek(fp, 0, SEEK_SET);
			printf("found same \n");
			return fp;
		}

		fopen_s(&fp, _fullPathFileName.c_str(), "r+");
		/*if (!fp) {
			LOG_WARNING("File is not found");
			return fp; 
		}*/
		printf("create new \n");
		fileMap.emplace(_fullPathFileName, fp);
		if (fileMap.find(_fullPathFileName) != fileMap.end()) {
			std::cout << "found \n";
		}

		return fp;
	}

	void FileManager::Destroy() {
		std::cout << "destroy\n";

		for (auto& [name, filePtr] : fileMap) {
			fclose(filePtr);
		}
	}
}