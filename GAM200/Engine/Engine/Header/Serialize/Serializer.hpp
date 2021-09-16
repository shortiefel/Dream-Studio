/* Start Header**********************************************************************************/
/*
@file    Serializer.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    16/09/2021
\brief
This file has the function declaration of Serializer


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include "Engine/Header/Math/MathLib.hpp"

#include <string>
#include <rapidjson/document.h>

using JsonIter = rapidjson::Value::ConstMemberIterator;

namespace Engine {
	class Serializer {
	public:
		Serializer(const JsonIter& i);

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

	private:
		JsonIter itr;
	};
}

#endif