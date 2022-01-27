/* Start Header**********************************************************************************/
/*
@file    DSerializer.hpp
@authors	Goh See Yong Denise		g.seeyongdenise@digipen.edu	100%
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

#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Engine/Header/Math/MathLib.hpp"

#include <unordered_set>

#include <string>
#include <rapidjson/document.h>

using JsonIter = rapidjson::Value::ConstMemberIterator;
#define VARIABLE_CHECK if (!itr->value.HasMember(name)) { printf("variable: %s \n", name); throw "Variable doesn't exist"; }

namespace Engine {
	class DSerializer {
	public:
		DSerializer(const JsonIter& i = JsonIter{});
		void SetIterator(const JsonIter& i);

		/*--------------------------------------------------------------------------------
		* T GetValue (name)
		--------------------------------------------------------------------------------*/
		template <typename T>
		T GetValueInternal(const char* name) const {
			VARIABLE_CHECK;
			LOG_WARNING("DSerializer: Unknown type");
		}
		template <>
		bool GetValueInternal(const char* name) const {
			VARIABLE_CHECK;
			return itr->value[name].GetBool();
		}

		template <>
		unsigned int GetValueInternal(const char* name) const {
			VARIABLE_CHECK;
			return itr->value[name].GetUint();
		}
		
		template <>
		int GetValueInternal(const char* name) const {
			VARIABLE_CHECK;
			return itr->value[name].GetInt();
		}

		template <>
		float GetValueInternal(const char* name) const {
			VARIABLE_CHECK;
			return itr->value[name].GetFloat();
		}

		template <>
		std::string GetValueInternal(const char* name) const {
			VARIABLE_CHECK;
			return itr->value[name].GetString();
		}

		template <>
		Math::vec2 GetValueInternal(const char* name) const {
			VARIABLE_CHECK;
			return Math::vec2{
				itr->value[name].GetArray()[0].GetFloat(),
				itr->value[name].GetArray()[1].GetFloat() };
		}

		template <>
		Math::vec3 GetValueInternal(const char* name) const {
			VARIABLE_CHECK;
			return Math::vec3{
				itr->value[name].GetArray()[0].GetFloat(),
				itr->value[name].GetArray()[1].GetFloat(),
				itr->value[name].GetArray()[2].GetFloat() };
		}

		template <>
		Math::vec4 GetValueInternal(const char* name) const {
			VARIABLE_CHECK;
			return Math::vec4{
				itr->value[name].GetArray()[0].GetFloat(),
				itr->value[name].GetArray()[1].GetFloat(),
				itr->value[name].GetArray()[2].GetFloat(),
				itr->value[name].GetArray()[3].GetFloat() };
		}

		template <>
		std::unordered_set<uint32_t> GetValueInternal(const char* name) const {
			VARIABLE_CHECK;
			std::unordered_set<uint32_t> child{};
			auto sz = itr->value[name].GetArray().Size();
			auto data = itr->value[name].GetArray();
			for (unsigned int i = 0; i < sz; i++) {
				child.insert(data[i].GetUint());
			}


			return child;
		}

		/*rapidjson::Value& GetArray() const {
			return  itr->value["ma,e"].GetString();
		}*/

		const rapidjson::GenericArray<true, rapidjson::Value> GetArray() const {
			return (itr->value.GetArray());
		}

		/*
		If it is a newly added variable it would be missing from the serialized file
		This adds a default value
		*/
		template <typename T>
		T GetValue(const char* name) const {
			try{
				return GetValueInternal<T>(name);
			}
			catch (const char* msg) {
				std::cout << msg << "\n";
				LOG_WARNING("DSerializer: ", msg);
				return T{};
			}
		}

		auto GetValueArray(const char* name) const {
			return itr->value[name].GetArray();
		}
		
		//If the number of element is unknown, use this
		template <typename T>
		std::unordered_set<T> GetUSet(const char* name) const {
			printf("trying this\n");
			VARIABLE_CHECK;
			std::unordered_set<T> holder;
			const auto& src = itr->value[name].GetArray();
			unsigned int sz = src.Size();
			for (unsigned int i = 0; i < sz; i++) {
				holder.emplace(src[i].GetUint());
			}
			return holder;
		}

		


	private:
		JsonIter itr;
	};
}

#endif