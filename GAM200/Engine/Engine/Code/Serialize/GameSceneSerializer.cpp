/* Start Header**********************************************************************************/
/*
@file    GameSceneSerializer.cpp
@authors	Goh See Yong Denise		g.seeyongdenise@digipen.edu		100%
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

#include "Engine/Header/Scene/Prefab.hpp"
#include "Engine/Header/Scene/SceneManager.hpp"

//External Resources
#include <sstream>
#include <fstream>

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

#define SERIALIZE_ENTITY SSerializer serializerEntity(doc, objTypeEntity);\
						 serializerEntity.SetValue("Name", entity.name);\
						 serializerEntity.SetValue("Parent", entity.parent);\
						 serializerEntity.SetValueSet("Child", entity.child);

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
							Entity entity = dreamECSGame->CreateEntity(entityName.c_str(), child, parent);


//Type and Store named must be same to use this
#define DESERIALIZE_INTERNAL(type, dreamECS) \
itr = obj.FindMember(#type);\
if (itr != obj.MemberEnd()) {\
	DSerializer serializer{ itr }; \
		dreamECSGame->AddComponent(\
			type{ entity.id }.Deserialize(serializer)\
		);\
}

#define DESERIALIZE(type) DESERIALIZE_INTERNAL(type, dreamECSGame)

#define REFRESH_PREFAB(type) itr = obj.FindMember(#type);\
							 type* component##type = dreamECSGame->GetComponentPTR<type>(id);\
							 if (itr != obj.MemberEnd()) {\
							 	DSerializer serializer{ itr };\
							 	 if (component##type != nullptr)\
							 		 *component##type = type{ id }.Deserialize(serializer);\
							 	 else\
							 		 dreamECSGame->AddComponent(type{ id }.Deserialize(serializer));\
							 }\
							 else if (component##type != nullptr) {\
							 	 dreamECSGame->RemoveComponent<type>(id);\
							 }

//#define SERIALIZE(target)\
//	rapidjson::Value objType(rapidjson::kObjectType);\
//	SSerializer serializer(doc, objType);\
//	target->Serialize(serializer);

#define SERIALIZE_INTERNAL(type, dreamECS) { type* tem = dreamECS->GetComponentPTR<type>(entity.id); \
						  if (tem != nullptr) {\
						  	  LOG_ASSERT(tem); \
						  	  rapidjson::Value objType##type(rapidjson::kObjectType); \
						  	  SSerializer serializer##type(doc, objType##type); \
						  	  tem->Serialize(serializer##type); \
						  	  entityObject.AddMember(#type, objType##type, doc.GetAllocator()); \
						  }\
						  }

#define SERIALIZE(type) SERIALIZE_INTERNAL(type, dreamECSGame)


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

		fileStream.open("Data/Settings.json");
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

			Settings::defaultCircle = itr->value["DefaultCircle"].GetString();
			Settings::defaultSquare = itr->value["DefaultSquare"].GetString();
		}

		itr = doc.FindMember("Scene");
		if (itr != doc.MemberEnd()) {
			SceneManager::GetInstance().SetDefaultScene(itr->value["DefaultScene"].GetString());
		}

		fileStream.close();
	}

	void GameSceneSerializer::SerializeScene(std::string filename) {
		filename = TO_FULL_SCENE(filename);
	
		rapidjson::Document doc(rapidjson::kArrayType);
		
		//const std::vector<Entity>& entList = DreamECS::GetInstance().GetUsedEntitySet();
		auto& entityMap = dreamECSGame->GetUsedConstEntityMap();
		
		for (const auto& [entityId, entity] : entityMap) {
			rapidjson::Value entityObject(rapidjson::kObjectType);

			rapidjson::Value objTypeEntity(rapidjson::kObjectType);
			SERIALIZE_ENTITY;
			entityObject.AddMember("Entity", objTypeEntity, doc.GetAllocator());

			SERIALIZE(TransformComponent);
			SERIALIZE(ColliderComponent);
			SERIALIZE(RigidBodyComponent);
			SERIALIZE(CameraComponent);
			SERIALIZE(TextureComponent);
			SERIALIZE(UIComponent);
			SERIALIZE(FontComponent);

			ScriptComponent* csScript = dreamECSGame->GetComponentPTR<ScriptComponent>(entityId);
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
			DESERIALIZE(FontComponent);

			itr = obj.FindMember("ScriptComponent");
			if (itr != obj.MemberEnd()) {
				DSerializer serializer{ itr };
				dreamECSGame->AddComponent(
					std::move(ScriptComponent{ entity.id }.Deserialize(serializer))
			);

			}
		}
		fileStream.close();
	}

	void GameSceneSerializer::SerializePrefab(std::string _filename, Entity_id entity_id) {
		std::string filename = TO_FULL_PREFAB(_filename);

		auto& entityMap = dreamECSGame->GetUsedConstEntityMap();
		const auto& [entityId, entity] = *entityMap.find(entity_id);

		rapidjson::Document doc(rapidjson::kArrayType);
		rapidjson::Value entityObject(rapidjson::kObjectType);

		rapidjson::Value objTypeEntity(rapidjson::kObjectType);
		SSerializer serializerEntity(doc, objTypeEntity); 
		serializerEntity.SetValue("Name", _filename);
		serializerEntity.SetValue("Parent", entity.parent); 
		serializerEntity.SetValueSet("Child", entity.child);
		entityObject.AddMember("Entity", objTypeEntity, doc.GetAllocator());

		SERIALIZE(TransformComponent);
		SERIALIZE(ColliderComponent);
		SERIALIZE(RigidBodyComponent);
		SERIALIZE(CameraComponent);
		SERIALIZE(TextureComponent);
		SERIALIZE(UIComponent);
		SERIALIZE(FontComponent);

		ScriptComponent* csScript = dreamECSGame->GetComponentPTR<ScriptComponent>(entityId);
		if (csScript != nullptr) {
			LOG_ASSERT(csScript);
			rapidjson::Value objTypeScriptComponent(rapidjson::kArrayType);
			SSerializer serializerScriptComponent(doc, objTypeScriptComponent);
			csScript->Serialize(serializerScriptComponent);
			entityObject.AddMember("ScriptComponent", objTypeScriptComponent, doc.GetAllocator());
		}

		doc.PushBack(entityObject, doc.GetAllocator());
		

		std::ofstream fileStream(filename);
		rapidjson::OStreamWrapper osw(fileStream);

		rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
		doc.Accept(writer);

		fileStream.close();
	}

	void GameSceneSerializer::DeserializePrefab(std::string _filename, unsigned int* id, Math::vec2 position, float angle) {
		std::string filename = TO_FULL_PREFAB(_filename);
		
		std::ifstream fileStream;
		rapidjson::Document doc;

		fileStream.open(filename);
		rapidjson::IStreamWrapper isw(fileStream);

		doc.ParseStream(isw);

		for (auto& obj : doc.GetArray()) {
			rapidjson::Value::ConstMemberIterator itr;

			DESERIALIZE_ENTITY;
			if (entity.id == DEFAULT_ENTITY_ID) return;
			dreamECSGame->AddPrefab(Prefab(_filename, entity));

			if (id != nullptr)
				*id = entity.id;

			itr = obj.FindMember("TransformComponent");
			if (itr != obj.MemberEnd()) {
					DSerializer serializer{ itr }; 
					auto& transform = TransformComponent{ entity.id }.Deserialize(serializer);
					dreamECSGame->AddComponent(
						 TransformComponent{ entity.id, position, transform.scale, transform.angle + angle }
					); 
					transform.localPosition = position;
			}

			DESERIALIZE(ColliderComponent);
			DESERIALIZE(RigidBodyComponent);
			DESERIALIZE(CameraComponent);
			DESERIALIZE(TextureComponent);
			DESERIALIZE(UIComponent);
			DESERIALIZE(FontComponent);

			itr = obj.FindMember("ScriptComponent");
			if (itr != obj.MemberEnd()) {
				DSerializer serializer{ itr };
				dreamECSGame->AddComponent(
					std::move(ScriptComponent{ entity.id }.Deserialize(serializer))
				);
			}
		}

		fileStream.close();
	}

	void GameSceneSerializer::RefreshPrefab(std::string filename, Entity_id id) {
		filename = TO_FULL_PREFAB(filename);

		std::ifstream fileStream;
		rapidjson::Document doc;

		fileStream.open(filename);
		rapidjson::IStreamWrapper isw(fileStream);

		doc.ParseStream(isw);

		for (auto& obj : doc.GetArray()) {
			rapidjson::Value::ConstMemberIterator itr;

			//Logic for each component
			//1. if in prefab file have a particular component
			//	1.1 if ECS have the same component for that entity
			//		change/ammend the variables of the component
			//	1.2 if entity doesnt have that component
			//		add component
			//2. else if entity doesnt have that component (assuming prefab file doesnt have the component too opposite of 1.)
			//	remove component since prefab file dont have but ECS have

			itr = obj.FindMember("TransformComponent");
			TransformComponent* transformComponent = dreamECSGame->GetComponentPTR<TransformComponent>(id);
			if (itr != obj.MemberEnd()) {
				DSerializer serializer{ itr }; 
				if (transformComponent != nullptr) {
					TransformComponent tem(id);
					tem.Deserialize(serializer);
					transformComponent->angle = tem.angle;
					transformComponent->layer = tem.layer;
				}
				else 
					dreamECSGame->AddComponent(TransformComponent{ id }.Deserialize(serializer));
			}
			else if (transformComponent != nullptr) {
				dreamECSGame->RemoveComponent<TransformComponent>(id);
			}

			REFRESH_PREFAB(ColliderComponent);
			REFRESH_PREFAB(RigidBodyComponent);
			REFRESH_PREFAB(CameraComponent);
			REFRESH_PREFAB(TextureComponent);
			REFRESH_PREFAB(UIComponent);
			REFRESH_PREFAB(FontComponent);
			
			itr = obj.FindMember("ScriptComponent");
			ScriptComponent* compScript = dreamECSGame->GetComponentPTR<ScriptComponent>(id);
			if (itr != obj.MemberEnd()) {
				DSerializer serializer{ itr };
				if (compScript != nullptr)
					*compScript = std::move(ScriptComponent{ id }.Deserialize(serializer));
				else
					dreamECSGame->AddComponent(std::move(ScriptComponent{ id }.Deserialize(serializer)));
			}
			else if (compScript != nullptr) {
				dreamECSGame->RemoveComponent<ScriptComponent>(id);
			}
		}

		fileStream.close();
	}

}