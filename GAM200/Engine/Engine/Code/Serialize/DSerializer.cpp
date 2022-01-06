/* Start Header**********************************************************************************/
/*
@file    Serializer.cpp
@authors	Goh See Yong Denise		g.seeyongdenise@digipen.edu		100%
@date    16/09/2021
\brief
This file has the function definition of DSerializer


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Serialize/DSerializer.hpp"

#include <rapidjson/document.h>

#include <rapidjson/writer.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>

namespace Engine {
	DSerializer::DSerializer(const JsonIter& i) : itr{ i } {}
	void DSerializer::SetIterator(const JsonIter& i) { itr = i; }

}