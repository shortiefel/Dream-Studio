/* Start Header**********************************************************************************/
/*
@file    SSerializer.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    16/09/2021
\brief
This file has the function definition of SSerializer

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Serialize/SSerializer.hpp"

#include <rapidjson/document.h>

#include <rapidjson/writer.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>

namespace Engine {
	SSerializer::SSerializer(rapidjson::Document& _doc, rapidjson::Value& _objType) :
		doc{ _doc }, objType{ _objType } {}

	SSerializer::SSerializer(const SSerializer& _serializer, rapidjson::Value& _objType) : 
		doc{ _serializer.doc }, objType{ _objType } {}

	/*void SSerializer::EndSerialize(const char* _name, rapidjson::Value& _entityObject) const {
		rapidjson::Value vName(_name, doc.GetAllocator());
		entityObject.AddMember(vName, objType, doc.GetAllocator());
	}*/
}