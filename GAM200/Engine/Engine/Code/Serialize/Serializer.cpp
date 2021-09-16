/* Start Header**********************************************************************************/
/*
@file    Serializer.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    16/09/2021
\brief
This file has the function definition of Serializer


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Serialize/Serializer.hpp"

#include <rapidjson/document.h>

#include <rapidjson/writer.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>

namespace Engine {
	Serializer::Serializer(const JsonIter& i) : itr{ i } {}

}