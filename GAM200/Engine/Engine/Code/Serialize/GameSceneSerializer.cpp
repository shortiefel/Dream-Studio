/* Start Header**********************************************************************************/
/*
@file    GameSceneSerializer.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
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

#include "Engine/Header/Management/FileManager.hpp"
//FILE* fp = FileManager::GetInstance().Open_File("Data/Config.json");

//External Resources
#include <sstream>

#include <rapidjson/document.h>

#include <rapidjson/writer.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>

#include "Engine/Header/ECS/Entity/EntityManager.hpp"
#include "Engine/Header/ECS/DreamECS.hpp"
#include "Engine/Header/ECS/Component/ComponentList.hpp"
#include "Engine/Header/Script/ScriptClassVariable.hpp"

#include <fstream>

//Type and Store named must be same to use this
#define ADD_COMPONENT_WTIH_CHECK(type) \
itr = obj.FindMember(#type);\
if (itr != obj.MemberEnd()) {\
	DSerializer serializer{ itr }; \
		DreamECS::GetInstance().AddComponent(\
			type{ ent }.Deserialize(serializer)\
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

#define TO_FULL_SCENE(name) ("Assets/Scenes/" + name + ".scene")
#define TO_FULL_PREFAB(name) ("Assets/Prefab/" + name + ".prefab")

#define READ_BUFFER \
char readBuffer[1000];\
rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));\
rapidjson::Document doc;\
doc.ParseStream(is);
//fclose(fp);


namespace Engine {
	void GameSceneSerializer::SerializeSetting() {
		rapidjson::Document doc(rapidjson::kObjectType);


		//doc.PushBack(entityObject, doc.GetAllocator());

		/*char writeBuffer[1000];
		rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
		rapidjson::Writer<rapidjson::FileWriteStream> writer(os);
		doc.Accept(writer);*/

		//FILE_CREATION("Data/Config.json", "wb");
		//FILE* fp = FileManager::GetInstance().Open_File("Data/Config.json");

		std::ofstream fileStream("Data/Config.json");
		rapidjson::OStreamWrapper osw(fileStream);

		rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
		doc.Accept(writer);

		fileStream.close();
		//fclose(fp);
	}

	void GameSceneSerializer::DeserializeSetting() {
		//FILE_CREATION("Data/Config.json", "rb");
		//FILE* fp = FileManager::GetInstance().Open_File("Data/Config.json");
		//READ_BUFFER;
		std::ifstream fileStream;
		rapidjson::Document doc;

		fileStream.open("Data/Config.json");
		rapidjson::IStreamWrapper isw(fileStream);

		doc.ParseStream(isw);

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

		SceneManager::GetInstance().SetDefaultScene("test3");

		fileStream.close();
	}

	void GameSceneSerializer::SerializeScene(std::string filename) {
		filename = TO_FULL_SCENE(filename);
	
		rapidjson::Document doc(rapidjson::kArrayType);
		
		const std::unordered_set<Entity>& entList = DreamECS::GetInstance().GetUsedEntitySet();
		//size_t num = entList.size();
		for (const auto& ent : entList) {
			rapidjson::Value entityObject(rapidjson::kObjectType);

			Transform* trans = DreamECS::GetInstance().GetComponentTest<Transform>(ent);
			if (trans != nullptr) {
				LOG_ASSERT(trans);
				SERIALIZE(trans);
				entityObject.AddMember("Transform", objType, doc.GetAllocator());
			}

			Collider* col = DreamECS::GetInstance().GetComponentTest<Collider>(ent);
			if (col != nullptr) {
				LOG_ASSERT(col);
				SERIALIZE(col);
				entityObject.AddMember("Collider", objType, doc.GetAllocator());
			}

			RigidBody* rb = DreamECS::GetInstance().GetComponentTest<RigidBody>(ent);
			if (rb != nullptr) {
				LOG_ASSERT(rb);
				SERIALIZE(rb);
				entityObject.AddMember("RigidBody", objType, doc.GetAllocator());
			}

			Camera2D* cam = DreamECS::GetInstance().GetComponentTest<Camera2D>(ent);
			if (cam != nullptr) {
				LOG_ASSERT(cam);
				SERIALIZE(cam);
				entityObject.AddMember("Camera2D", objType, doc.GetAllocator());
			}

			Texture* tex = DreamECS::GetInstance().GetComponentTest<Texture>(ent);
			if (tex != nullptr) {
				LOG_ASSERT(tex);
				SERIALIZE(tex);
				entityObject.AddMember("Texture", objType, doc.GetAllocator());
			}
#if 1

			CSScript* csScript = DreamECS::GetInstance().GetComponentTest<CSScript>(ent);
			if (csScript != nullptr) {
				LOG_ASSERT(csScript);
				rapidjson::Value objType(rapidjson::kArrayType);
				SSerializer serializer(doc, objType); 
				csScript->Serialize(serializer);
				entityObject.AddMember("CSScript", objType, doc.GetAllocator());
			}

#else
			if (ScriptSystem::csEntityClassInstance.find(ent) != ScriptSystem::csEntityClassInstance.end()) {

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

				entityObject.AddMember("CSScript", classArray, doc.GetAllocator());
			}
#endif

			doc.PushBack(entityObject, doc.GetAllocator());
		}
		/*char writeBuffer[1000];
		rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
		rapidjson::Writer<rapidjson::FileWriteStream> writer(os);
		doc.Accept(writer);*/


		//FILE_CREATION(filename.c_str(), "wb");
		//FILE* fp = FileManager::GetInstance().Open_File(filename);

		std::ofstream fileStream(filename);
		rapidjson::OStreamWrapper osw(fileStream);

		rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
		doc.Accept(writer);

		//fileStream.unsetf(std::ofstream::out | std::ofstream::trunc);
		fileStream.close();
		
		//fclose(fp);
	}

	void GameSceneSerializer::DeserializeScene(std::string filename) {
		filename = TO_FULL_SCENE(filename);

		//FILE_CREATION(filename.c_str(), "rb");
		//FILE* fp = FileManager::GetInstance().Open_File(filename);
		std::ifstream fileStream;
		rapidjson::Document doc;

		fileStream.open(filename);
		rapidjson::IStreamWrapper isw(fileStream);

		doc.ParseStream(isw);

		for (auto& obj : doc.GetArray()) {
			Entity ent = DreamECS::GetInstance().CreateEntity();

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
				DreamECS::GetInstance().AddComponent(
					std::move(CSScript{ ent }.Deserialize(serializer))
			);
#else
				DSerializer serializer(itr);
				CSClassInstance classInstance;


				ScriptSystem::Deserialize(serializer, classInstance);

				ScriptSystem::csEntityClassInstance.emplace(ent, std::move(classInstance));
#endif
			}
		}
		fileStream.close();
	}

	void GameSceneSerializer::DeserializePrefab(std::string filename, Math::vec2 position, float angle) {
		filename = TO_FULL_PREFAB(filename);

		//FILE* fp = FileManager::GetInstance().Open_File(filename);

		//READ_BUFFER;
		
		std::ifstream fileStream;
		rapidjson::Document doc;

		fileStream.open(filename);
		rapidjson::IStreamWrapper isw(fileStream);

		doc.ParseStream(isw);

		for (auto& obj : doc.GetArray()) {
			Entity ent = DreamECS::GetInstance().CreateEntity();
			rapidjson::Value::ConstMemberIterator itr;

			//ADD_COMPONENT_WTIH_CHECK(Transform);

			itr = obj.FindMember("Transform");
			if (itr != obj.MemberEnd()) {
					DSerializer serializer{ itr }; 
					DreamECS::GetInstance().AddComponent(
						Transform{ ent }.Deserialize(serializer) += Transform{ ent, position, Math::vec2{1,1}, angle }
					); 
			}

			ADD_COMPONENT_WTIH_CHECK(Collider);
			ADD_COMPONENT_WTIH_CHECK(RigidBody);
			ADD_COMPONENT_WTIH_CHECK(Camera2D);
			ADD_COMPONENT_WTIH_CHECK(Texture);

			itr = obj.FindMember("CSScript");
			if (itr != obj.MemberEnd()) {
				DSerializer serializer{ itr };
				DreamECS::GetInstance().AddComponent(
					std::move(CSScript{ ent }.Deserialize(serializer))
				);
			}
		}
	}
}