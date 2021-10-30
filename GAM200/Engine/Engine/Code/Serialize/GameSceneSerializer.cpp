/* Start Header**********************************************************************************/
/*
@file    GameSceneSerializer.cpp
@authors	Goh See Yong Denise		g.seeyongdenise@digipen.edu
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
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>

#include "Engine/Header/ECS/Entity/EntityManager.hpp"
#include "Engine/Header/ECS/DreamECS.hpp"
#include "Engine/Header/ECS/Component/ComponentList.hpp"
#include "Engine/Header/Script/ScriptClassVariable.hpp"

#include <fstream>

#define DESERIALIZE_ENTITY std::string entityName = DEFAULT_ENTITY_NAME;\
							Entity_id parent = DEFAULT_ENTITY_ID;\
							std::unordered_set<Entity_id> child{};\
							\
							itr = obj.FindMember("Entity");\
							if (itr != obj.MemberEnd()) {\
								DSerializer serializer{ itr };\
								entityName = serializer.GetValue<std::string>("Name");\
								parent = serializer.GetValue<unsigned int>("Parent");\
								\
							}\
							Entity entity = DreamECS::GetInstance().CreateEntity(entityName.c_str(), child, parent);

//child = serializer.GetUSet<unsigned int>("Child");\

//Type and Store named must be same to use this
#define DESERIALIZE(type) \
itr = obj.FindMember(#type);\
if (itr != obj.MemberEnd()) {\
	DSerializer serializer{ itr }; \
		DreamECS::GetInstance().AddComponent(\
			type{ entity.id }.Deserialize(serializer)\
		);\
}

//#define SERIALIZE(target)\
//	rapidjson::Value objType(rapidjson::kObjectType);\
//	SSerializer serializer(doc, objType);\
//	target->Serialize(serializer);

#define SERIALIZE(type) { type* tem = DreamECS::GetInstance().GetComponentPTR<type>(entity.id); \
						  if (tem != nullptr) {\
						  	  LOG_ASSERT(tem); \
						  	  rapidjson::Value objType##type(rapidjson::kObjectType); \
						  	  SSerializer serializer##type(doc, objType##type); \
						  	  tem->Serialize(serializer##type); \
						  	  entityObject.AddMember(#type, objType##type, doc.GetAllocator()); \
						  }\
						  }

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
		
		//const std::vector<Entity>& entList = DreamECS::GetInstance().GetUsedEntitySet();
		auto& entityMap = DreamECS::GetInstance().GetUsedConstEntityMap();
		
		for (const auto& [entityId, entity] : entityMap) {
			rapidjson::Value entityObject(rapidjson::kObjectType);

			rapidjson::Value objTypeEntity(rapidjson::kObjectType);
			SSerializer serializerEntity(doc, objTypeEntity);
			serializerEntity.SetValue("Name", entity.name);
			
			serializerEntity.SetValue("Parent", entity.parent);
			serializerEntity.SetValueUSet("Child", entity.child);
			entityObject.AddMember("Entity", objTypeEntity, doc.GetAllocator());

			SERIALIZE(TransformComponent);
			SERIALIZE(ColliderComponent);
			SERIALIZE(RigidBodyComponent);
			SERIALIZE(CameraComponent);
			SERIALIZE(TextureComponent);
			SERIALIZE(UIComponent);

			ScriptComponent* csScript = DreamECS::GetInstance().GetComponentPTR<ScriptComponent>(entityId);
			if (csScript != nullptr) {
				LOG_ASSERT(csScript);
				rapidjson::Value objTypeScriptComponent(rapidjson::kArrayType);
				SSerializer serializerScriptComponent(doc, objTypeScriptComponent);
				csScript->Serialize(serializerScriptComponent);
				entityObject.AddMember("ScriptComponent", objTypeScriptComponent, doc.GetAllocator());
			}

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
			rapidjson::Value::ConstMemberIterator itr;

			DESERIALIZE_ENTITY;

			DESERIALIZE(TransformComponent);
			DESERIALIZE(ColliderComponent);
			DESERIALIZE(RigidBodyComponent);
			DESERIALIZE(CameraComponent);
			DESERIALIZE(TextureComponent);
			DESERIALIZE(UIComponent);

			itr = obj.FindMember("ScriptComponent");
			if (itr != obj.MemberEnd()) {
#if 1
				DSerializer serializer{ itr };
				DreamECS::GetInstance().AddComponent(
					std::move(ScriptComponent{ entity.id }.Deserialize(serializer))
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
			rapidjson::Value::ConstMemberIterator itr;

			DESERIALIZE_ENTITY;

			//ADD_COMPONENT_WTIH_CHECK(Transform);

			itr = obj.FindMember("TransformComponent");
			if (itr != obj.MemberEnd()) {
					DSerializer serializer{ itr }; 
					const auto& transform = TransformComponent{ entity.id }.Deserialize(serializer);
					DreamECS::GetInstance().AddComponent(
						 TransformComponent{ entity.id, transform.position + position, transform.scale, transform.angle + angle }
					); 
			}

			DESERIALIZE(ColliderComponent);
			DESERIALIZE(RigidBodyComponent);
			DESERIALIZE(CameraComponent);
			DESERIALIZE(TextureComponent);
			DESERIALIZE(UIComponent);

			itr = obj.FindMember("ScriptComponent");
			if (itr != obj.MemberEnd()) {
				DSerializer serializer{ itr };
				DreamECS::GetInstance().AddComponent(
					std::move(ScriptComponent{ entity.id }.Deserialize(serializer))
				);
			}
		}
	}
}