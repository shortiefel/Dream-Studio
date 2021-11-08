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

#include "Engine/Header/Management/GameState.hpp"

#include "Engine/Header/Serialize/DSerializer.hpp"
#include "Engine/Header/Serialize/SSerializer.hpp"

namespace Engine {
	ScriptComponent::ScriptComponent(Entity_id _ID, const char* _className) :
		IComponent{ _ID } {
		if (_className) {
			CSScriptInstance csScriptInstance{ _className };
			Scripting::InitCSClass(csScriptInstance, _ID);
			Scripting::InitVariable(csScriptInstance);

			klassInstance.emplace(_className, std::move(csScriptInstance));

		}
		//CSScriptInstance csScriptInstance{ _className };
		//klassInstance.emplace(csScriptInstance.csClass.className, std::move(csScriptInstance));
	}

	ScriptComponent::ScriptComponent(ScriptComponent&& rhs) noexcept {
		klassInstance = std::move(rhs.klassInstance);
		SetEntityId(rhs.GetEntityId());
		rhs.SetEntityId(DEFAULT_ENTITY_ID);
	}

	ScriptComponent& ScriptComponent::operator=(ScriptComponent&& rhs) noexcept {
		klassInstance = std::move(rhs.klassInstance);
		SetEntityId(rhs.GetEntityId());
		rhs.SetEntityId(DEFAULT_ENTITY_ID);
		return *this;
	}

	//void ScriptComponent::CopyComponentAsInstance(const ScriptComponent& target) {
	//	for (const auto& [className, csScriptInstance] : target.klassInstance) {
	//		if (klassInstance.find(className) != klassInstance.end()) continue;
	//		CSScriptInstance newScriptInstance{ className };
	//		for (const auto& [variableName, variableInstance] : csScriptInstance.csVariableMap) {
	//			
	//			CSPublicVariable csPublicvariable{ variableName, variableInstance.variableType };
	//			switch (variableInstance.variableType) {
	//			case CSType::CHAR:
	//				variableInstance.GetVariableData<char>();
	//				break;
	//			case CSType::BOOL:
	//				variableInstance.GetVariableData<bool>();
	//				break;
	//			case CSType::FLOAT:
	//				variableInstance.GetVariableData<float>();
	//				break;
	//			case CSType::INT:
	//				variableInstance.GetVariableData<int>();
	//				break;
	//			case CSType::UINT:
	//				variableInstance.GetVariableData<unsigned int>();
	//				break;
	//			case CSType::VEC2:
	//				variableInstance.GetVariableData<Math::vec2>();
	//				break;
	//			}
	//			//auto data = variableMap.GetVariableData<>();
	//			//csPublicvariable.SetVariableData(data);

	//			//newScriptInstance.csVariableMap
	//		}
	//	}
	//}

	bool ScriptComponent::AddScript(ScriptComponent& comp) {
		bool same = true;
		for (auto& [className, csScriptInstance] : comp.klassInstance) {
			
			if (klassInstance.find(className) == klassInstance.end()) {
				Scripting::InitScript(GetEntityId(), csScriptInstance);
				klassInstance.emplace(className, std::move(csScriptInstance));
			}

			else {
				same = false;
			}
		}

		return same;
	}

	bool ScriptComponent::RemoveScript(const char* _className) {
		klassInstance.erase(_className);

		if (klassInstance.size()) return false;
		return true;
	}

	ScriptComponent& ScriptComponent::Deserialize(const DSerializer& _serializer) {
		for (auto& classJSon : _serializer.GetArray()) {
			const auto& fullName = classJSon["Class"].GetString();

			CSScriptInstance csScriptInstance{
				fullName,
				classJSon["IsActive"].GetBool() };

			rapidjson::Value::ConstMemberIterator variableItr = classJSon.FindMember("Variable");
			if (!Scripting::InitCSClass(csScriptInstance, GetEntityId())) { continue; }
			if (variableItr != classJSon.MemberEnd()) {
				for (auto& variableData : variableItr->value.GetArray()) {
					const auto& variableName = variableData["Name"].GetString();
					const auto& variableType = CSType{ variableData["Type"].GetInt() };


					CSPublicVariable csPublicvariable{ variableName, variableType };

					if (variableType == CSType::CHAR) {
						char charData = static_cast<char>(variableData["Data"].GetInt());
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
					/*else if (variableType == CSType::GAMEOBJECT) {
						const char* tem = variableData["Data"].GetString();
						csPublicvariable.SetVariableData(const_cast<char*>(tem));
					}*/

					csScriptInstance.csVariableMap.emplace(variableName, std::move(csPublicvariable));
				}

			}
			//klassInstance[csScriptInstance.csClass.className] = std::move(csScriptInstance);
			//Scripting::InitVariable(csScriptInstance);
			//Scripting::InitScript(GetEntityId(), csScriptInstance);
			klassInstance.emplace(csScriptInstance.csClass.className, std::move(csScriptInstance));
		}

		return *this;
	}

	void ScriptComponent::Serialize(const SSerializer& _serializer) {
		for (const auto& [className, scriptInstance] : klassInstance) {
			rapidjson::Value classObj(rapidjson::kObjectType);
			SSerializer cserializer(_serializer, classObj);

			cserializer.SetValue("Class", scriptInstance.csClass.fullName);
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
					/*case CSType::GAMEOBJECT:
						vserializer.SetValue("Data", variableInstance.GetVariableData<char*>());
						break;*/
					}

					serializer.SetValueJSonArray(variableObject);
				}

				cserializer.SetValueJSon("Variable", variableArray);
			}

			_serializer.SetValueJSonArray(classObj);
		}
	}
}