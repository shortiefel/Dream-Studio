/* Start Header**********************************************************************************/
/*
@file    FileWindowDialog.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu		100%
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

#define REMOVE_FROM_FILEPATH filePath = filePath.substr(filePath.find_last_of("\\") + 1);\
							 filePath = filePath.substr(0, filePath.find_last_of("."));

namespace Engine {
	class FileWindowDialog {
	public:
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter);
	};
}

#endif