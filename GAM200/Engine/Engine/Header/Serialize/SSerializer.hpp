/* Start Header**********************************************************************************/
/*
@file    SSerializer.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    16/09/2021
\brief
This file has the function declaration of SSerializer
SSerializer = Serialize Serializer

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef SSERIALIZER_HPP
#define SSERIALIZER_HPP

#include "Engine/Header/Math/MathLib.hpp"

#include <string>
#include <rapidjson/document.h>

#define ADD_MEMBER(name, data)\
rapidjson::Value vName(name, doc.GetAllocator());\
objType.AddMember(vName, data, doc.GetAllocator());

namespace Engine {
	class SSerializer {
	public:
		SSerializer(rapidjson::Document& _doc, rapidjson::Value& _objType, rapidjson::Value& _entityObject);

		/*--------------------------------------------------------------------------------
		* SetValue (name, T)
		--------------------------------------------------------------------------------*/
		template <typename T>
		void SetValue(const char* _name, T _val) const {
			printf("Error Cant find\n");
		}
		template <>
		void SetValue(const char* _name, bool _val) const {
			ADD_MEMBER(_name, _val);
		}

		template <>
		void SetValue(const char* _name, unsigned int _val) const {
			ADD_MEMBER(_name, _val);
		}

		template <>
		void SetValue(const char* _name, int _val) const {
			ADD_MEMBER(_name, _val);
		}

		template <>
		void SetValue(const char* _name, float _val) const {
			ADD_MEMBER(_name, _val);
		}

		template <>
		void SetValue(const char* _name, std::string _val) const {
			rapidjson::Value fp;
			char buffer[200];
			int len = sprintf_s(buffer, "%s", _val.c_str());
			fp.SetString(buffer, len, doc.GetAllocator());

			ADD_MEMBER(_name, fp);
		}

		template <>
		void SetValue(const char* _name, Math::vec2 _val) const {
			rapidjson::Value pos(rapidjson::kArrayType);
			pos.PushBack(_val.x, doc.GetAllocator());
			pos.PushBack(_val.y, doc.GetAllocator());

			ADD_MEMBER(_name, pos);
		}

		void EndSerialize(const char* _name) const;

	private:
		rapidjson::Document& doc;
		rapidjson::Value& objType;
		rapidjson::Value& entityObject;
	};
}

#endif

