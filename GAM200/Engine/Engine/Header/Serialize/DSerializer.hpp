/* Start Header**********************************************************************************/
/*
@file    DSerializer.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    16/09/2021
\brief
This file has the function declaration of DSerializer
DSerializer = Deserialize Serializer

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef DSERIALIZER_HPP
#define DSERIALIZER_HPP

#include "Engine/Header/Math/MathLib.hpp"

#include <string>
#include <rapidjson/document.h>

using JsonIter = rapidjson::Value::ConstMemberIterator;

namespace Engine {
	class DSerializer {
	public:
		DSerializer(const JsonIter& i);

		/*--------------------------------------------------------------------------------
		* T GetValue (name)
		--------------------------------------------------------------------------------*/
		template <typename T>
		T GetValue(const char* name) const {
			printf("Error Cant find\n");
		}
		template <>
		bool GetValue(const char* name) const {
			return itr->value[name].GetBool();
		}

		template <>
		unsigned int GetValue(const char* name) const {
			return itr->value[name].GetUint();
		}
		
		template <>
		int GetValue(const char* name) const {
			return itr->value[name].GetInt();
		}

		template <>
		float GetValue(const char* name) const {
			return itr->value[name].GetFloat();
		}

		template <>
		std::string GetValue(const char* name) const {
			return itr->value[name].GetString();
		}

		template <>
		Math::vec2 GetValue(const char* name) const {
			return Math::vec2{
				itr->value[name].GetArray()[0].GetFloat(),
				itr->value[name].GetArray()[1].GetFloat() };
		}

		/*rapidjson::Value& GetArray() const {
			return  itr->value["ma,e"].GetString();
		}*/

		const rapidjson::GenericArray<true, rapidjson::Value> GetArray() const {
			return (itr->value.GetArray());
		}



	private:
		JsonIter itr;
	};
}

#endif