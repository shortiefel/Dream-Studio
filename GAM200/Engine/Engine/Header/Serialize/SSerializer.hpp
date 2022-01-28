/* Start Header**********************************************************************************/
/*
@file    SSerializer.hpp
@authors	Goh See Yong Denise		g.seeyongdenise@digipen.edu	100%
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

#include <set>
#include <list>

#define ADD_MEMBER(name, data)\
rapidjson::Value vName(name, doc.GetAllocator());\
objType.AddMember(vName, data, doc.GetAllocator());

#define ADD_MEMBER_ARRAY(name, data)\
objType.PushBack(data, doc.GetAllocator());

namespace Engine {
	class SSerializer {
	public:
		SSerializer(rapidjson::Document& _doc, rapidjson::Value& _objType);
		SSerializer(const SSerializer& _serializer, rapidjson::Value& _objType);

		/*--------------------------------------------------------------------------------
		* SetValue (name, T)
		--------------------------------------------------------------------------------*/
		template <typename T>
		void SetValue(const char*, const T&) const {
			//ADD_MEMBER(_name, _val);
			printf("Error Cant find\n");
		}

		template <>
		void SetValue(const char* _name, const bool& _val) const {
			ADD_MEMBER(_name, _val);
		}

		template <>
		void SetValue(const char* _name, const unsigned int& _val) const {
			ADD_MEMBER(_name, _val);
		}

		template <>
		void SetValue(const char* _name, const int& _val) const {
			ADD_MEMBER(_name, _val);
		}

		template <>
		void SetValue(const char* _name, const float& _val) const {
			ADD_MEMBER(_name, _val);
		}

		template <>
		void SetValue(const char* _name, const std::string& _val) const {
			rapidjson::Value fp;
			char buffer[200];
			int len = sprintf_s(buffer, "%s", _val.c_str());
			fp.SetString(buffer, len, doc.GetAllocator());

			ADD_MEMBER(_name, fp);
		}

		template <>
		void SetValue(const char* _name, const Math::vec2& _val) const {
			rapidjson::Value pos(rapidjson::kArrayType);
			pos.PushBack(_val.x, doc.GetAllocator());
			pos.PushBack(_val.y, doc.GetAllocator());

			ADD_MEMBER(_name, pos);
		}

		template <>
		void SetValue(const char* _name, const Math::vec3& _val) const {
			rapidjson::Value pos(rapidjson::kArrayType);
			pos.PushBack(_val.x, doc.GetAllocator());
			pos.PushBack(_val.y, doc.GetAllocator());
			pos.PushBack(_val.z, doc.GetAllocator());

			ADD_MEMBER(_name, pos);
		}

		template <>
		void SetValue(const char* _name, const Math::vec4& _val) const {
			rapidjson::Value pos(rapidjson::kArrayType);
			pos.PushBack(_val.x, doc.GetAllocator());
			pos.PushBack(_val.y, doc.GetAllocator());
			pos.PushBack(_val.z, doc.GetAllocator());
			pos.PushBack(_val.w, doc.GetAllocator());

			ADD_MEMBER(_name, pos);
		}

		template <>
		void SetValue(const char* _name, const std::list<unsigned int>& _val) const {
			rapidjson::Value _store(rapidjson::kArrayType);
			for (auto i : _val) {
				_store.PushBack(i, doc.GetAllocator());
			}

			ADD_MEMBER(_name, _store);
		}

		template <>
		void SetValue(const char* _name, const std::list<Math::vec2>& _val) const {
			rapidjson::Value _store(rapidjson::kArrayType);
			for (auto i : _val) {
				_store.PushBack(i.x, doc.GetAllocator());
				_store.PushBack(i.y, doc.GetAllocator());
			}

			ADD_MEMBER(_name, _store);
		}

		template <typename T>
		void SetValueSet(const char* _name, const std::set<T>& _val) const {
			rapidjson::Value pos(rapidjson::kArrayType);

			for (const auto& id : _val) {
				pos.PushBack(id, doc.GetAllocator());
			}
			
			//pos.PushBack(_val.y, doc.GetAllocator());

			ADD_MEMBER(_name, pos);
		}

		void SetValueJSon(const char* _name, rapidjson::Value& _val) const {
			ADD_MEMBER(_name, _val);
		}

		void SetValueJSonArray(rapidjson::Value& target) const {
			objType.PushBack(target, doc.GetAllocator());
		}

		/*
		* Put parameter 2 (objType) into parameter 1 (arrayType)
		*/
		void SetValueJSonArray(rapidjson::Value& arrayObj, rapidjson::Value& target) const {
			arrayObj.PushBack(target, doc.GetAllocator());
		}

		void SetValueJSonArray(const char* _name, rapidjson::Value& target) const {
			rapidjson::Value vName(_name, doc.GetAllocator());
			objType.AddMember(vName, target, doc.GetAllocator());
			//ADD_MEMBER(_name, target);
		}

		//void EndSerialize(const char* _name, rapidjson::Value& _entityObject) const;

		///*--------------------------------------------------------------------------------
		//* SetValueArray (name, T)
		//--------------------------------------------------------------------------------*/
		//template <typename T>
		//void SetValueArray(const char* _name, T _val) const {
		//	printf("Error Cant find\n");
		//}
		//template <>
		//void SetValueArray(const char* _name, bool _val) const {
		//	ADD_MEMBER(_name, _val);
		//}

		//template <>
		//void SetValueArray(const char* _name, unsigned int _val) const {
		//	ADD_MEMBER(_name, _val);
		//}

		//template <>
		//void SetValueArray(const char* _name, int _val) const {
		//	ADD_MEMBER(_name, _val);
		//}

		//template <>
		//void SetValueArray(const char* _name, float _val) const {
		//	ADD_MEMBER(_name, _val);
		//}

		//template <>
		//void SetValueArray(const char* _name, std::string _val) const {
		//	rapidjson::Value fp;
		//	char buffer[200];
		//	int len = sprintf_s(buffer, "%s", _val.c_str());
		//	fp.SetString(buffer, len, doc.GetAllocator());

		//	ADD_MEMBER(_name, fp);
		//}

		//template <>
		//void SetValueArray(const char* _name, Math::vec2 _val) const {
		//	rapidjson::Value pos(rapidjson::kArrayType);
		//	pos.PushBack(_val.x, doc.GetAllocator());
		//	pos.PushBack(_val.y, doc.GetAllocator());

		//	ADD_MEMBER(_name, pos);
		//}
	private:
		rapidjson::Document& doc;
		rapidjson::Value& objType;
		//rapidjson::Value& entityObject;
	};
}

#endif

