/* Start Header**********************************************************************************/
/*
@file    FileWindowDialog.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    27/10/2021
\brief
This contain the declaration of FileWindowDialog


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef FILE_DIALOG_HPP
#define FILE_DIALOG_HPP

#include <string>

#define REMOVE_FROM_FILEPATH size_t pos = filePath.find_last_of("\\");\
							 filePath = filePath.substr(pos + 1);\
							 pos = filePath.find_last_of(".");\
							 filePath = filePath.substr(0, pos);

namespace Engine {
	class FileWindowDialog {
	public:
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter);
	};
}

#endif