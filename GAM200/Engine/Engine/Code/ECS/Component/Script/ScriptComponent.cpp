/* Start Header**********************************************************************************/
/*
@file    ScriptComponent.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    26/06/2021
\brief
This file contain the Script component definition


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/ECS/Component/Script/ScriptComponent.hpp"
#include "Engine/Header/Script/Scripting.hpp"

namespace Engine {
	CSScript::CSScript(Entity _ID, const char* _className) :
		IComponent{ _ID } {
		if (_className) {
			CSScriptInstance csScriptInstance{ _className };
			klassInstance.emplace(_className, std::move(csScriptInstance));
		}
	}

	CSScript::CSScript(CSScript&& rhs) noexcept {
		klassInstance = std::move(rhs.klassInstance);
		SetEntityId(rhs.GetEntityId());
		rhs.SetEntityId(DEFAULT_ENTITY);
	}

	CSScript& CSScript::operator=(CSScript&& rhs) noexcept {
		klassInstance = std::move(rhs.klassInstance);
		SetEntityId(rhs.GetEntityId());
		rhs.SetEntityId(DEFAULT_ENTITY);
		return *this;
	}

	void CSScript::AddScript(CSScript& comp) {
		for (auto& [className, csScriptInstance] : comp.klassInstance) {
			if (klassInstance.find(className) == klassInstance.end()) {
				Scripting::InitVariable(csScriptInstance);
				Scripting::InitCSClass(csScriptInstance);
				klassInstance.emplace(className, std::move(csScriptInstance));
			}

			else {
				std::cout << "found class at " << klassInstance.at(className).csClass.className << "\n";
			}
		}
	}

	void CSScript::AddSpecial() {

	}

	bool CSScript::RemoveScript(const char* _className) {
		klassInstance.erase(_className);

		if (klassInstance.size()) return false;
		return true;
	}

	void CSScript::SetActive(const char* _className, bool _boolean) {
		klassInstance.find(_className)->second.isActive = _boolean;
	}

	/*void CSScript::InitVariable(const char* className) {
		auto& csScriptInstance = klassInstance.at(className);
		Scripting::InitVariable(csScriptInstance);
	}*/

	CSScript& CSScript::Deserialize(const DSerializer& _serializer) {
		for (auto& classJSon : _serializer.GetArray()) {
			const auto& className = classJSon["Class"].GetString();

			CSScriptInstance csScriptInstance{
				className,
				classJSon["IsActive"].GetBool() };

			/*rapidjson::Value::ConstMemberIterator variableItr = classJSon.FindMember("Variable");
			if (variableItr != classJSon.MemberEnd()) {
				for (auto& variableData : variableItr->value.GetArray()) {
					const auto& variableName = variableData["Name"].GetString();
					const auto& variableType = CSType{ variableData["Type"].GetInt() };


					CSPublicVariable csPublicvariable{ variableName, variableType };


					if (variableType == CSType::CHAR) {
						char charData = variableData["Data"].GetInt();
						csPublicvariable.SetVariableData(&charData);
					}

					else if (variableType == CSType::BOOL) {
						bool boolData = variableData["Data"].GetBool();
						csPublicvariable.SetVariableData(&boolData);
					}

					else if (variableType == CSType::FLOAT) {
						float floatData = variableData["Data"].GetFloat();
						csPublicvariable.SetVariableData(&floatData);
					}
					else if (variableType == CSType::INT) {
						int intData = variableData["Data"].GetInt();
						csPublicvariable.SetVariableData(&intData);
					}
					else if (variableType == CSType::UINT) {
						unsigned int uinData = variableData["Data"].GetUint();
						csPublicvariable.SetVariableData(&uinData);
					}

					else if (variableType == CSType::VEC2) {
						Math::vec2 vec2Data{ variableData["Data"].GetArray()[0].GetFloat(),
											variableData["Data"].GetArray()[1].GetFloat() };
						csPublicvariable.SetVariableData(&vec2Data);
					}

					csScriptInstance.csVariableMap.emplace(variableName, std::move(csPublicvariable));
				}
			}*/
			klassInstance.emplace(className, std::move(csScriptInstance));
		}
		return *this;
	}

	void CSScript::Serialize(const SSerializer& _serializer) {
		for (const auto& [className, scriptInstance] : klassInstance) {
			rapidjson::Value classObj(rapidjson::kObjectType);
			SSerializer cserializer(_serializer, classObj);

			cserializer.SetValue("Class", className);
			cserializer.SetValue("IsActive", scriptInstance.isActive);

			if (scriptInstance.csVariableMap.size()) {
				rapidjson::Value variableArray(rapidjson::kArrayType);

				SSerializer serializer(cserializer, variableArray);
				for (const auto& [variableName, variableInstance] : scriptInstance.csVariableMap) {
					rapidjson::Value variableObject(rapidjson::kObjectType);
					SSerializer vserializer(serializer, variableObject);

					vserializer.SetValue("Name", variableName);
					vserializer.SetValue("Type", (int)variableInstance.variableType);

					switch (variableInstance.variableType) {
					case CSType::CHAR:
						vserializer.SetValue("Data", variableInstance.GetVariableData<char>());
						break;
					case CSType::BOOL:
						vserializer.SetValue("Data", variableInstance.GetVariableData<bool>());
						break;
					case CSType::FLOAT:
						vserializer.SetValue("Data", variableInstance.GetVariableData<float>());
						break;
					case CSType::INT:
						vserializer.SetValue("Data", variableInstance.GetVariableData<int>());
						break;
					case CSType::UINT:
						vserializer.SetValue("Data", variableInstance.GetVariableData<unsigned int>());
						break;
					case CSType::VEC2:
						vserializer.SetValue("Data", variableInstance.GetVariableData<Math::vec2>());
						break;
					}

					serializer.SetValueJSonArray(variableObject);
				}

				cserializer.SetValueJSon("Variable", variableArray);
			}

			_serializer.SetValueJSonArray(classObj);
		}
	}
}