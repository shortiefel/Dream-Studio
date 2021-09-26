/* Start Header**********************************************************************************/
/*
@file    ScriptComponent.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
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

#include "Engine/Header/Serialize/DSerializer.hpp"
#include "Engine/Header/Serialize/SSerializer.hpp"

namespace Engine {
	CSScript::CSScript(Entity _ID, const char* _className) :
		IComponent{ _ID } {
		/*if (_className) {
			CSScriptInstance csScriptInstance{ _className };
			klassInstance.emplace(_className, std::move(csScriptInstance));
		}*/
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

	void CSScript::CopyComponentAsInstance(const CSScript& target) {
		for (const auto& [className, csScriptInstance] : target.klassInstance) {
			if (klassInstance.find(className) != klassInstance.end()) continue;
			CSScriptInstance newScriptInstance{ className };
			for (const auto& [variableName, variableInstance] : csScriptInstance.csVariableMap) {
				
				CSPublicVariable csPublicvariable{ variableName, variableInstance.variableType };
				switch (variableInstance.variableType) {
				case CSType::CHAR:
					variableInstance.GetVariableData<char>();
					break;
				case CSType::BOOL:
					variableInstance.GetVariableData<bool>();
					break;
				case CSType::FLOAT:
					variableInstance.GetVariableData<float>();
					break;
				case CSType::INT:
					variableInstance.GetVariableData<int>();
					break;
				case CSType::UINT:
					variableInstance.GetVariableData<unsigned int>();
					break;
				case CSType::VEC2:
					variableInstance.GetVariableData<Math::vec2>();
					break;
				}
				//auto data = variableMap.GetVariableData<>();
				//csPublicvariable.SetVariableData(data);

				//newScriptInstance.csVariableMap
			}
		}
	}

	void CSScript::AddScript(CSScript& comp) {
		for (auto& [className, csScriptInstance] : comp.klassInstance) {
			//std::cout << "class in AddScript " << className << "\n";
			if (klassInstance.find(className) == klassInstance.end()) {
				
				klassInstance.emplace(className, std::move(csScriptInstance));
				//CSScriptInstance& tem = klassInstance.find(className)->second;

				//Scripting::InitVariable(tem);
				//Scripting::InitCSClass(tem);
			}

			else {
				std::cout << "found class at " << klassInstance.at(className).csClass.className << "\n";
			}
		}

		std::cout << "Add Script  " << GetEntityId() << "\n";
	}

	bool CSScript::RemoveScript(const char* _className) {
		klassInstance.erase(_className);

		if (klassInstance.size()) return false;
		return true;
	}

	void CSScript::SetActive(const char* _className, bool _boolean) {
		klassInstance.find(_className)->second.isActive = _boolean;
	}

	CSScript& CSScript::Deserialize(const DSerializer& _serializer) {
		for (auto& classJSon : _serializer.GetArray()) {
			const auto& className = classJSon["Class"].GetString();

			CSScriptInstance csScriptInstance{
				className,
				classJSon["IsActive"].GetBool() };

			rapidjson::Value::ConstMemberIterator variableItr = classJSon.FindMember("Variable");
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

			}
			Scripting::InitCSClass(csScriptInstance);
			klassInstance.emplace(className, std::move(csScriptInstance));
		}

		std::cout << "Deserializing -------------------------------------------------------------------\n";
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