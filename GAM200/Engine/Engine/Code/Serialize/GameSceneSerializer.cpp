/* Start Header**********************************************************************************/
/*
@file    GameSceneSerializer.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    15/07/2021
\brief
This file contain the GameSceneSerializer definition
Serialize and Deserialize the game scene (Entities that are in the game)
NOTE: Not to be confused with EditorSceneSerializer which serialize editor related things
E.g Scene camera (would not appear inside a game)

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug tools/Logging.hpp"

#include "Engine/Header/Serialize/GameSceneSerializer.hpp"
#include "Engine/Header/Serialize/DSerializer.hpp"
#include "Engine/Header/Serialize/SSerializer.hpp"
#include "Engine/Header/Management/Settings.hpp"

#include "Engine/Header/Scene/SceneManager.hpp"

//External Resources
#include <sstream>

#include <rapidjson/document.h>

#include <rapidjson/writer.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>

#include "Engine/Header/ECS/Entity/EntityManager.hpp"
#include "Engine/Header/ECS/ECSWrapper.hpp"
#include "Engine/Header/ECS/Component/ComponentList.hpp"
#include "Engine/Header/Script/ScriptClassVariable.hpp"

//Type and Store named must be same to use this
#define ADD_COMPONENT_WTIH_CHECK(type) \
itr = obj.FindMember(#type);\
if (itr != obj.MemberEnd()) {\
	DSerializer serializer{ itr }; \
		DreamECS::AddComponent(\
			std::move(type{ ent }.Deserialize(serializer))\
		);\
}

#define SERIALIZE(target)\
	rapidjson::Value objType(rapidjson::kObjectType);\
	SSerializer serializer(doc, objType);\
	target->Serialize(serializer);

#define FILE_CREATION(path, type)\
FILE* fp;\
fopen_s(&fp, path, type);\
if (!fp) {\
	LOG_WARNING("File is not found");\
	return;\
}

#define READ_BUFFER \
char readBuffer[1000];\
rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));\
rapidjson::Document doc;\
doc.ParseStream(is);\
fclose(fp);


namespace Engine {
	void GameSceneSerializer::SerializeSetting() {
		FILE_CREATION("Data/Config.json", "wb");

		rapidjson::Document doc(rapidjson::kObjectType);

		//doc.PushBack(entityObject, doc.GetAllocator());

		char writeBuffer[1000];
		rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
		rapidjson::Writer<rapidjson::FileWriteStream> writer(os);
		doc.Accept(writer);

		fclose(fp);
	}

	void GameSceneSerializer::DeserializeSetting() {
		FILE_CREATION("Data/Config.json", "rb");
		READ_BUFFER;

		rapidjson::Value::ConstMemberIterator itr = doc.FindMember("Window");
		if (itr != doc.MemberEnd()) {
			Settings::windowWidth = itr->value["Width"].GetInt();
			Settings::windowHeight = itr->value["Height"].GetInt();
		}

		itr = doc.FindMember("Game");
		if (itr != doc.MemberEnd()) {
			Settings::gameWidth = itr->value["Width"].GetInt();
			Settings::gameHeight = itr->value["Height"].GetInt();

			Settings::gameAR = static_cast<GLfloat>(Settings::gameWidth) / Settings::gameHeight;
		}

		SceneManager::SetDefaultScene("test3");
	}

	void GameSceneSerializer::SerializeScene(std::string filename) {
		FILE_CREATION(filename.c_str(), "wb");

		rapidjson::Document doc(rapidjson::kArrayType);

		const std::unordered_set<Entity>& entList = DreamECS::GetUsedEntitySet();
		//size_t num = entList.size();
		for (const auto& ent : entList) {
			rapidjson::Value entityObject(rapidjson::kObjectType);

			Transform* trans = DreamECS::GetComponentTest<Transform>(ent);
			if (trans != nullptr) {
				LOG_ASSERT(trans);
				SERIALIZE(trans);
				entityObject.AddMember("Transform", objType, doc.GetAllocator());
			}

			Collider* col = DreamECS::GetComponentTest<Collider>(ent);
			if (col != nullptr) {
				LOG_ASSERT(col);
				SERIALIZE(col);
				entityObject.AddMember("Collider", objType, doc.GetAllocator());
			}

			RigidBody* rb = DreamECS::GetComponentTest<RigidBody>(ent);
			if (rb != nullptr) {
				LOG_ASSERT(rb);
				SERIALIZE(rb);
				entityObject.AddMember("RigidBody", objType, doc.GetAllocator());
			}

			Camera2D* cam = DreamECS::GetComponentTest<Camera2D>(ent);
			if (cam != nullptr) {
				LOG_ASSERT(cam);
				SERIALIZE(cam);
				entityObject.AddMember("Camera2D", objType, doc.GetAllocator());
			}

			Texture* tex = DreamECS::GetComponentTest<Texture>(ent);
			if (tex != nullptr) {
				LOG_ASSERT(tex);
				SERIALIZE(tex);
				entityObject.AddMember("Texture", objType, doc.GetAllocator());
			}
#if 1

			CSScript* csScript = DreamECS::GetComponentTest<CSScript>(ent);
			if (csScript != nullptr) {
				LOG_ASSERT(csScript);
				rapidjson::Value objType(rapidjson::kArrayType);
				SSerializer serializer(doc, objType); 
				csScript->Serialize(serializer);
				entityObject.AddMember("CSScript", objType, doc.GetAllocator());
			}



#else
			if (ScriptSystem::csEntityClassInstance.find(ent) != ScriptSystem::csEntityClassInstance.end()) {
#if 1
				const CSClassInstance& entityclassInstance = ScriptSystem::csEntityClassInstance.find(ent)->second;
				rapidjson::Value classArray(rapidjson::kArrayType);

				SSerializer serializer(doc, classArray);
				ScriptSystem::SerializeClass(serializer, entityclassInstance);
				{
					//const CSClassInstance& entityclassInstance = ScriptSystem::csEntityClassInstance.find(ent)->second;
					//rapidjson::Value classArray(rapidjson::kArrayType);

					//for (const auto& [className, scriptInstance] : entityclassInstance) {

					//	rapidjson::Value classObj(rapidjson::kObjectType);
					//	SSerializer cserializer(doc, classObj);

					//	rapidjson::Value classNameFP;
					//	char buffer[200];
					//	int len = sprintf_s(buffer, "%s", className.c_str());
					//	classNameFP.SetString(buffer, len, doc.GetAllocator());

					//	//classObj.AddMember("Class", classNameFP, doc.GetAllocator());

					//	//classObj.AddMember("IsActive", scriptInstance.isActive, doc.GetAllocator());
					//	cserializer.SetValue("Class", className);
					//	cserializer.SetValue("IsActive", scriptInstance.isActive);

					//	if (scriptInstance.csVariableMap.size()) {
					//		rapidjson::Value variableArray(rapidjson::kArrayType);

					//		SSerializer serializer(doc, variableArray);
					//		ScriptSystem::SerializeVariable(serializer, scriptInstance);

					//		//classObj.AddMember("Variable", variableArray, doc.GetAllocator());
					//		cserializer.SetValueJSon("Variable", variableArray);
					//	}

					//	classArray.PushBack(classObj, doc.GetAllocator());
					//}
				}
#else
				const CSClassInstance& entityclassInstance = ScriptSystem::csEntityClassInstance.find(ent)->second;
				rapidjson::Value classArray(rapidjson::kArrayType);

				for (const auto& [className, scriptInstance] : entityclassInstance) {

					rapidjson::Value classObj(rapidjson::kObjectType);

					rapidjson::Value classNameFP;
					char buffer[200];
					int len = sprintf_s(buffer, "%s", className.c_str());
					classNameFP.SetString(buffer, len, doc.GetAllocator());

					classObj.AddMember("Class", classNameFP, doc.GetAllocator());

					classObj.AddMember("IsActive", scriptInstance.isActive, doc.GetAllocator());

					if (scriptInstance.csVariableMap.size()) {
						rapidjson::Value variableArray(rapidjson::kArrayType);

						for (const auto& [variableName, variableInstance] : scriptInstance.csVariableMap) {
							rapidjson::Value variableObject(rapidjson::kObjectType);

							rapidjson::Value variableFP;
							len = sprintf_s(buffer, "%s", variableName.c_str());
							variableFP.SetString(buffer, len, doc.GetAllocator());
							variableObject.AddMember("Name", variableFP, doc.GetAllocator());
							variableObject.AddMember("Type", (int)variableInstance.variableType, doc.GetAllocator());

							switch (variableInstance.variableType) {
							case CSType::CHAR:
								variableObject.AddMember("Data", variableInstance.GetVariableData<char>(), doc.GetAllocator());
								break;
							case CSType::BOOL:
								variableObject.AddMember("Data", variableInstance.GetVariableData<bool>(), doc.GetAllocator());
								break;
							case CSType::FLOAT:
								variableObject.AddMember("Data", variableInstance.GetVariableData<float>(), doc.GetAllocator());
								break;
							case CSType::INT:
								variableObject.AddMember("Data", variableInstance.GetVariableData<int>(), doc.GetAllocator());
								break;
							case CSType::UINT:
								variableObject.AddMember("Data", variableInstance.GetVariableData<unsigned int>(), doc.GetAllocator());
								break;
							case CSType::VEC2:
								Math::vec2 tem = variableInstance.GetVariableData<Math::vec2>();
								rapidjson::Value dataVec2(rapidjson::kArrayType);
								dataVec2.PushBack(tem.x, doc.GetAllocator());
								dataVec2.PushBack(tem.y, doc.GetAllocator());
								variableObject.AddMember("Data", dataVec2, doc.GetAllocator());
								break;
							}

							variableArray.PushBack(variableObject, doc.GetAllocator());
						}
						classObj.AddMember("Variable", variableArray, doc.GetAllocator());
					}

					classArray.PushBack(classObj, doc.GetAllocator());
				}
#endif

				entityObject.AddMember("CSScript", classArray, doc.GetAllocator());
			}
#endif

			doc.PushBack(entityObject, doc.GetAllocator());
		}
		char writeBuffer[1000];
		rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
		rapidjson::Writer<rapidjson::FileWriteStream> writer(os);
		doc.Accept(writer);

		fclose(fp);
	}

	void GameSceneSerializer::DeserializeScene(std::string filename) {
		FILE_CREATION(filename.c_str(), "rb");
		READ_BUFFER;

		for (auto& obj : doc.GetArray()) {
			Entity ent = DreamECS::CreateEntity();
			rapidjson::Value::ConstMemberIterator itr;

			ADD_COMPONENT_WTIH_CHECK(Transform);
			ADD_COMPONENT_WTIH_CHECK(Collider);
			ADD_COMPONENT_WTIH_CHECK(RigidBody);
			ADD_COMPONENT_WTIH_CHECK(Camera2D);
			ADD_COMPONENT_WTIH_CHECK(Texture);

			itr = obj.FindMember("CSScript");
			if (itr != obj.MemberEnd()) {
#if 1 
				
				DSerializer serializer{ itr };
				DreamECS::AddComponent(
					std::move(CSScript{ ent }.Deserialize(serializer))
			);
#else
				DSerializer serializer(itr);
				CSClassInstance classInstance;


				ScriptSystem::Deserialize(serializer, classInstance);
				/*for (auto& classJSon : itr->value.GetArray()) {
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
					classInstance.emplace(className, std::move(csScriptInstance));
				}*/

				ScriptSystem::csEntityClassInstance.emplace(ent, std::move(classInstance));
#endif
			}
		}
	}
}