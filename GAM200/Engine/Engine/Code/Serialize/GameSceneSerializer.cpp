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
#include "Engine/Header/Serialize/Serializer.hpp"

#include "Engine/Header/Management/Settings.hpp"
#include "Engine/Header/Scene/Prefab.hpp"
#include "Engine/Header/Scene/SceneManager.hpp"
#include "Engine/Header/Parent/ParentManager.hpp"

#include "Engine/Header/Script/Scripting.hpp"

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
//#define DESERIALIZE_INTERNAL(type, dreamECS) \
//itr = obj.FindMember(#type);\
//if (itr != obj.MemberEnd()) {\
//	DSerializer serializer{ itr }; \
//		dreamECSGame->AddComponent(\
//			type{ entity.id }.Deserialize(serializer)\
//		);\
//}

//#define DESERIALIZE(type) DESERIALIZE_INTERNAL(type, dreamECSGame)



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

#include <iostream>

namespace Engine {
	void DeserializeOtherComponents(Serializer& sceneSerializer, const unsigned int& entityId) {
		if (sceneSerializer.SelectDeserializeDataType("ColliderComponent")) {
			ColliderComponent tem(entityId);
			int colType;
			sceneSerializer.RetrieveData(
				"ColliderType", colType,
				"Position", tem.offset_position,
				"Scale", tem.offset_scale,
				"Angle", tem.angle,
				"IsTrigger", tem.isTrigger,
				"IsActive", tem.isActive);

			tem.cType = ColliderType(colType);
			dreamECSGame->AddComponent(tem);
		}

		if (sceneSerializer.SelectDeserializeDataType("RigidBodyComponent")) {
			RigidBodyComponent tem(entityId);
			sceneSerializer.RetrieveData(
				"Speed", tem.speed,
				"Mass", tem.mass,
				"LinearDrag", tem.linearDrag,
				"AngularDrag", tem.angularDrag,
				"IsActive", tem.isActive);

			dreamECSGame->AddComponent(tem);
		}

		if (sceneSerializer.SelectDeserializeDataType("CameraComponent")) {
			CameraComponent tem(entityId);
			sceneSerializer.RetrieveData(
				"Height", tem.height,
				"FOV", tem.fov,
				"AR", tem.ar,
				"IsActive", tem.isActive);

			dreamECSGame->AddComponent(tem);
		}

		if (sceneSerializer.SelectDeserializeDataType("TextureComponent")) {
			TextureComponent tem(entityId);
			std::string fp;
			sceneSerializer.RetrieveData("Filepath", fp);
			GraphicImplementation::SetTexture(&tem, std::move(fp));

			int shapeType;
			sceneSerializer.RetrieveData(
				"Shape", shapeType,
				"Colour", tem.colour,
				"IsAnimation", tem.isAnimation,
				"IsActive", tem.isActive);

			if (tem.isAnimation) {
				sceneSerializer.RetrieveData(
					"TotalRow", tem.totalRows,
					"TotalColumns", tem.totalColumns,
					"CurrentAnimationState", tem.currAnimationState);

				auto animationStates = sceneSerializer.RetrieveDataArray("AnimationState");
				for (auto& state : animationStates) {
					std::string stateName = state["StateName"].GetString();

					int stateRow = state["StateRow"].GetInt();

					int startX = state["StartFrame"].GetInt();
					int endX = state["EndFrame"].GetInt();

					float fTime = state["TimePerFrame"].GetFloat();

					bool isLoop = state["IsLoop"].GetBool();

					std::vector<float> frameTimes;
					if (state.FindMember("Frames") != state.MemberEnd()) {
						for (auto& frameTime : state["Frames"].GetArray()) {
							frameTimes.push_back(frameTime.GetFloat());
						}
					}

					AnimationState animstate = AnimationState(stateName, stateRow, startX, endX, fTime, isLoop, frameTimes);

					tem.animationStateList.emplace(stateName, animstate);
				}
			}

			tem.cellWidth = static_cast<float>(tem.width) / tem.totalColumns;
			tem.cellHeight = static_cast<float>(tem.height) / tem.totalRows;
			tem.mdl_ref = GraphicShape(shapeType);
			dreamECSGame->AddComponent(tem);
		}

		if (sceneSerializer.SelectDeserializeDataType("UIComponent")) {
			UIComponent tem(entityId);
			std::string fp;
			sceneSerializer.RetrieveData("Filepath", fp);
			GraphicImplementation::SetTexture(&tem, fp);
			sceneSerializer.RetrieveData(
				"Colour", tem.colour,
				"IsActive", tem.isActive);

			dreamECSGame->AddComponent(tem);
		}


		if (sceneSerializer.SelectDeserializeDataType("FontComponent")) {
			FontComponent tem(entityId);
			std::string fp;
			sceneSerializer.RetrieveData("Filepath", fp);
			GraphicImplementation::SetFont(&tem, fp);
			sceneSerializer.RetrieveData(
				"Text", tem.text,
				"Colour", tem.colour,
				"IsActive", tem.isActive);

			dreamECSGame->AddComponent(tem);
		}

		if (sceneSerializer.SelectDeserializeDataType("SoundComponent")) {
			SoundComponent tem(entityId);
			int soundGrpTem;
			sceneSerializer.RetrieveData(
				"IsLoop", tem.loop,
				"filepath", tem.filepath,
				"volume", tem.volume,
				"isSound", tem.isSound,
				"SoundGroup", soundGrpTem,
				"IsMute", tem.isMute,
				"IsActive", tem.isActive);

			tem.soundName = tem.filepath.substr(tem.filepath.find_last_of("\\") + 1);
			tem.soundName = tem.soundName.substr(0, tem.soundName.find_last_of("."));

			tem.soundType = static_cast<SoundGrp>(soundGrpTem);

			dreamECSGame->AddComponent(tem);
		}

		if (sceneSerializer.SelectDeserializeDataType("ParticleComponent")) {
			ParticleComponent tem(entityId);
			std::string fp;
			sceneSerializer.RetrieveData("Filepath", fp);
			GraphicImplementation::SetTexture(&tem, fp);
			int graphicShapeTem;

			Math::vec2 offsetPosition, velocity, velocityVariation,
				sizeBegin, sizeEnd, sizeVariation;

			Math::vec4 colorBegin, colorEnd;
			float lifeTime;

			sceneSerializer.RetrieveData(
				"Shape", graphicShapeTem,
				"EmitSize", tem.emitSize,
				"OffsetPosition", offsetPosition,
				"Velocity", velocity,
				"VelocityVariation", velocityVariation,
				"ColorBegin", colorBegin,
				"ColorEnd", colorEnd,
				"SizeBegin", sizeBegin,
				"SizeEnd", sizeEnd,
				"SizeVariation", sizeVariation,
				"LifeTime", lifeTime,
				"IsLooping", tem.isLooping,
				"IsAngleRandom", tem.isAngleRandom,
				"IsVelocityVariation", tem.isVelocityVariation,
				"IsActive", tem.isActive);

			tem.mdl_ref = GraphicShape(graphicShapeTem);
			tem.particleData = { offsetPosition, velocity, velocityVariation,
						 colorBegin, colorEnd, sizeBegin, sizeEnd, sizeVariation,
						 lifeTime };

			dreamECSGame->AddComponent(tem);
		}

		if (sceneSerializer.SelectDeserializeDataType("ScriptComponent")) {
			ScriptComponent tem(entityId);
			for (auto& classJSon : sceneSerializer.RetrieveDataArray("")) {
				const auto& fullName = classJSon["Class"].GetString();

				CSScriptInstance csScriptInstance(
					fullName,
					classJSon["IsActive"].GetBool());

				rapidjson::Value::ConstMemberIterator variableItr = classJSon.FindMember("Variable");
				if (!Scripting::InitCSClass(csScriptInstance, entityId)) { continue; }
#if 0
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
#endif
				//klassInstance[csScriptInstance.csClass.className] = std::move(csScriptInstance);
				//Scripting::InitVariable(csScriptInstance);
				//Scripting::InitScript(GetEntityId(), csScriptInstance);

				tem.klassInstance.emplace(csScriptInstance.csClass.className, std::move(csScriptInstance));
			}


			dreamECSGame->AddComponent(std::move(tem));
		}
	}
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
		Serializer sceneSerializer (filename);
		sceneSerializer.StartSerialize();

		auto& entityMap = dreamECSGame->GetUsedConstEntityMap();

		for (const auto& [entityId, entity] : entityMap) {
			sceneSerializer.StartEntitySerialize(entity);
			sceneSerializer.AddData(dreamECSGame->GetComponentPTR<TransformComponent>(entityId)); 
			sceneSerializer.AddData(dreamECSGame->GetComponentPTR<ColliderComponent>(entityId)); 
			sceneSerializer.AddData(dreamECSGame->GetComponentPTR<RigidBodyComponent>(entityId)); 
			sceneSerializer.AddData(dreamECSGame->GetComponentPTR<CameraComponent>(entityId)); 
			sceneSerializer.AddData(dreamECSGame->GetComponentPTR<TextureComponent>(entityId)); 
			sceneSerializer.AddData(dreamECSGame->GetComponentPTR<UIComponent>(entityId));
			sceneSerializer.AddData(dreamECSGame->GetComponentPTR<FontComponent>(entityId));
			sceneSerializer.AddData(dreamECSGame->GetComponentPTR<SoundComponent>(entityId)); 
			sceneSerializer.AddData(dreamECSGame->GetComponentPTR<WaypointComponent>(entityId));
			sceneSerializer.AddData(dreamECSGame->GetComponentPTR<ParticleComponent>(entityId)); 
			sceneSerializer.AddData(dreamECSGame->GetComponentPTR<ScriptComponent>(entityId)); 
			sceneSerializer.EndEntitySerialize();
		}
		sceneSerializer.EndSerialize();


		/*Serializer sceneSerializerTest(TO_FULL_SCENE(std::string{ "TestSeralizeScene" }));
		sceneSerializer.StartSerialize();

		for (const auto& [entityId, entity] : entityMap) {
			sceneSerializer.StartEntitySerialize(entity);
			TransformComponent* tc = dreamECSGame->GetComponentPTR<TransformComponent>(entityId);
			if (tc != nullptr) {
				sceneSerializer.AddData(
					"Position", tc->position, 
					"LocalPosition", tc->localPosition,
					"Scale", tc->scale, 
					"Angle", tc->angle, 
					"Layer", tc->layer, 
					"IsActive", tc->isActive);
			}

			sceneSerializer.EndEntitySerialize();
		}
		sceneSerializer.EndSerialize();*/
#if 0
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
			SERIALIZE(SoundComponent);
			SERIALIZE(ParticleComponent);

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
#endif
	}

	void GameSceneSerializer::DeserializeScene(std::string filename) {
		filename = TO_FULL_SCENE(filename);
		Serializer sceneSerializer(filename);

		std::function<void(void)> deserializeSceneFP = [&sceneSerializer]() -> void {
			//unsigned int entityId = sceneSerializer.RetrieveEntity().id;
			unsigned int entityId = DEFAULT_ENTITY_ID;
			if (sceneSerializer.SelectDeserializeDataType("Entity")) {
				std::string entityName = DEFAULT_ENTITY_NAME;
				Entity_id parent = DEFAULT_ENTITY_ID;
				std::unordered_set<Entity_id> child{};
				sceneSerializer.RetrieveData(
					"Name", entityName,
					"Parent", parent);

				entityId = dreamECSGame->CreateEntity(entityName.c_str(), child, parent).id;
			}
			if (entityId == DEFAULT_ENTITY_ID) {
				LOG_WARNING("Deserialize entity failed\n");
				return;
			}
			



			if (sceneSerializer.SelectDeserializeDataType("TransformComponent")) {
				TransformComponent tem(entityId);
				sceneSerializer.RetrieveData(
					"Position", tem.position,
					"LocalPosition", tem.localPosition,
					"Scale", tem.scale,
					"Angle", tem.angle,
					"Layer", tem.layer,
					"IsActive", tem.isActive);

				dreamECSGame->AddComponent(tem);
			}

			if (sceneSerializer.SelectDeserializeDataType("WaypointComponent")) {
				WaypointComponent tem(entityId);
				sceneSerializer.RetrieveData(
					"Waypoints", tem.listOfWaypoint,
					"Order", tem.numOfWaypoint);

				dreamECSGame->AddComponent(tem);
			}

			DeserializeOtherComponents(sceneSerializer, entityId);
		};

		sceneSerializer.DeserializeArray(deserializeSceneFP);

#if 0
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
			DESERIALIZE(SoundComponent);
			DESERIALIZE(ParticleComponent);

			itr = obj.FindMember("ScriptComponent");
			if (itr != obj.MemberEnd()) {
				DSerializer serializer{ itr };
				dreamECSGame->AddComponent(
					std::move(ScriptComponent{ entity.id }.Deserialize(serializer))
			);

			}
		}
		fileStream.close();
#endif
	}

	void GameSceneSerializer::SerializePrefab(std::string _filename, Entity_id entity_id) {
		std::string filename = TO_FULL_PREFAB(_filename);
		Serializer sceneSerializer(filename);
		sceneSerializer.StartSerialize();

		auto& entityMap = dreamECSGame->GetUsedConstEntityMap();

		auto [entityId, entity] = *entityMap.find(entity_id);
		entity.name = _filename;
		sceneSerializer.StartEntitySerializePrefab(entity);
		sceneSerializer.AddData(dreamECSGame->GetComponentPTR<TransformComponent>(entityId));
		sceneSerializer.AddData(dreamECSGame->GetComponentPTR<ColliderComponent>(entityId));
		sceneSerializer.AddData(dreamECSGame->GetComponentPTR<RigidBodyComponent>(entityId));
		sceneSerializer.AddData(dreamECSGame->GetComponentPTR<CameraComponent>(entityId));
		sceneSerializer.AddData(dreamECSGame->GetComponentPTR<TextureComponent>(entityId));
		sceneSerializer.AddData(dreamECSGame->GetComponentPTR<UIComponent>(entityId));
		sceneSerializer.AddData(dreamECSGame->GetComponentPTR<FontComponent>(entityId));
		sceneSerializer.AddData(dreamECSGame->GetComponentPTR<SoundComponent>(entityId));
		sceneSerializer.AddData(dreamECSGame->GetComponentPTR<ParticleComponent>(entityId));
		sceneSerializer.AddData(dreamECSGame->GetComponentPTR<ScriptComponent>(entityId));
		sceneSerializer.AddData(dreamECSGame->GetComponentPTR<WaypointComponent>(entityId));
		sceneSerializer.EndEntitySerialize();

		sceneSerializer.EndSerialize();


#if 0
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
		SERIALIZE(SoundComponent);
		SERIALIZE(ParticleComponent);

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
#endif
	}

	void GameSceneSerializer::DeserializePrefab(std::string _filename, unsigned int* id, Math::vec2 position, float angle, int layer) {
#if 1
		//NOTE: Assumes that parent is deserialized before child

		std::string filename = TO_FULL_PREFAB(_filename);
		Serializer sceneSerializer(filename);
		
		float cosX = Math::cosDeg(angle);
		float sinX = Math::sinDeg(angle);
		
		Math::mat3 rotationAndTranslate{ cosX, sinX, 0.f, -sinX, cosX, 0.f, position.x, position.y, 1.f };
		
		std::function<void(void)> deserializePrefabFP = [&sceneSerializer, &angle, &layer, &id, &_filename, &rotationAndTranslate]() -> void {
			//Prefab saved parents entity id which may not be the correct one in a new scene
			//This map will check if an entity has 
			static std::unordered_map<uint32_t, uint32_t> oldParentToNewParent;

			Entity entity;
			if (sceneSerializer.SelectDeserializeDataType("Entity")) {
				std::string entityName = DEFAULT_ENTITY_NAME;
				Entity_id entityId = DEFAULT_ENTITY_ID;
				Entity_id parent = DEFAULT_ENTITY_ID;
				std::list<Entity_id> child{};
				sceneSerializer.RetrieveData(
					"Name", entityName,
					"EntityId", entityId,
					"Parent", parent,
					"Child", child);

				entity = dreamECSGame->CreateEntity(entityName.c_str());
				
				if (child.size() != 0) 
					oldParentToNewParent[entityId] = entity.id;


				if (parent != DEFAULT_ENTITY_ID) {
					parent = oldParentToNewParent[parent];
					auto& temMap = dreamECSGame->GetUsedEntityMap();
					auto p_ = temMap.find(parent);
					if (p_ != temMap.end())
						p_->second.child.insert(entity.id);
					//temMap[parent].child.insert(entity.id);
					else
						LOG_WARNING("DeserializePrefab: Parents not found");

					auto t_ = temMap.find(entity.id);
					if (t_ != temMap.end())
						t_->second.parent = parent;
						//temMap[entity.id].parent = parent;
					else
						LOG_WARNING("DeserializePrefab: Parents not found");
				}
			}

			if (entity.id == DEFAULT_ENTITY_ID) {
				LOG_WARNING("Deserialize entity failed\n");
				return;
			}


			dreamECSGame->AddPrefab(Prefab(_filename, entity));
			unsigned int entityId = entity.id;

			if (id != nullptr)
				*id = entityId;

			if (sceneSerializer.SelectDeserializeDataType("TransformComponent")) {
				TransformComponent tem(entityId);
				sceneSerializer.RetrieveData(
					"Position", tem.position,
					"Scale", tem.scale,
					"Angle", tem.angle
				);

				Math::vec3 temVec{ tem.position.x, tem.position.y, 1.f };
				temVec = rotationAndTranslate * temVec;
				tem.position.x = temVec.x;
				tem.position.y = temVec.y;

				dreamECSGame->AddComponent(
					//TransformComponent{ entityId, tem.position + position, tem.scale, tem.angle + angle, layer }
					TransformComponent{ entityId, tem.position, tem.scale, tem.angle + angle, layer }
				);

				ParentManager::GetInstance().UpdateTruePos(entityId);
			}

			if (sceneSerializer.SelectDeserializeDataType("WaypointComponent")) {
				WaypointComponent tem(entityId);
				sceneSerializer.RetrieveData(
					"Waypoints", tem.listOfWaypoint,
					"Order", tem.numOfWaypoint);

				for (auto& i : tem.listOfWaypoint) {
					Math::vec3 newPos = rotationAndTranslate * Math::vec3{i.x, i.y, 1.f};
					i.x = newPos.x;
					i.y = newPos.y;
				}

				dreamECSGame->AddComponent(tem);
			}

			DeserializeOtherComponents(sceneSerializer, entityId);
		};

		sceneSerializer.DeserializeArray(deserializePrefabFP);
#else
		std::string filename = TO_FULL_PREFAB(_filename);
		Serializer sceneSerializer(filename);

		std::ifstream fileStream(filename);
		rapidjson::IStreamWrapper isw(fileStream);

		rapidjson::Document doc;
		doc.ParseStream(isw);

		for (auto& obj : doc.GetArray()) {
			arrayObjType = obj;

			fp();
		}
		fileStream.close();
#endif

#if 0
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
						 TransformComponent{ entity.id, position, transform.scale, transform.angle + angle, layer }
					); 
					ParentManager::GetInstance().UpdateTruePos(entity.id);
			}

			DESERIALIZE(ColliderComponent);
			DESERIALIZE(RigidBodyComponent);
			DESERIALIZE(CameraComponent);
			DESERIALIZE(TextureComponent);
			DESERIALIZE(UIComponent);
			DESERIALIZE(FontComponent);
			DESERIALIZE(SoundComponent);
			DESERIALIZE(ParticleComponent);

			itr = obj.FindMember("ScriptComponent");
			if (itr != obj.MemberEnd()) {
				DSerializer serializer{ itr };
				dreamECSGame->AddComponent(
					std::move(ScriptComponent{ entity.id }.Deserialize(serializer))
				);
			}
		}

		fileStream.close();
#endif
	}

	void GameSceneSerializer::RefreshPrefab(std::string filename, Entity_id id) {
		filename;
		id;
		std::cout << "Refresh not in use, please delete and add the prefab\n";
		//filename = TO_FULL_PREFAB(filename);

		//std::ifstream fileStream;
		//rapidjson::Document doc;

		//fileStream.open(filename);
		//rapidjson::IStreamWrapper isw(fileStream);

		//doc.ParseStream(isw);

		//for (auto& obj : doc.GetArray()) {
		//	rapidjson::Value::ConstMemberIterator itr;

		//	//Logic for each component
		//	//1. if in prefab file have a particular component
		//	//	1.1 if ECS have the same component for that entity
		//	//		change/ammend the variables of the component
		//	//	1.2 if entity doesnt have that component
		//	//		add component
		//	//2. else if entity doesnt have that component (assuming prefab file doesnt have the component too opposite of 1.)
		//	//	remove component since prefab file dont have but ECS have

		//	itr = obj.FindMember("TransformComponent");
		//	TransformComponent* transformComponent = dreamECSGame->GetComponentPTR<TransformComponent>(id);
		//	if (itr != obj.MemberEnd()) {
		//		DSerializer serializer{ itr }; 
		//		if (transformComponent != nullptr) {
		//			TransformComponent tem(id);
		//			tem.Deserialize(serializer);
		//			transformComponent->angle = tem.angle;
		//			transformComponent->layer = tem.layer;
		//		}
		//		else 
		//			dreamECSGame->AddComponent(TransformComponent{ id }.Deserialize(serializer));
		//	}
		//	else if (transformComponent != nullptr) {
		//		dreamECSGame->RemoveComponent<TransformComponent>(id);
		//	}

		//	REFRESH_PREFAB(ColliderComponent);
		//	REFRESH_PREFAB(RigidBodyComponent);
		//	REFRESH_PREFAB(CameraComponent);
		//	REFRESH_PREFAB(TextureComponent);
		//	REFRESH_PREFAB(UIComponent);
		//	REFRESH_PREFAB(FontComponent);
		//	REFRESH_PREFAB(SoundComponent);
		//	REFRESH_PREFAB(ParticleComponent);
		//	
		//	itr = obj.FindMember("ScriptComponent");
		//	ScriptComponent* compScript = dreamECSGame->GetComponentPTR<ScriptComponent>(id);
		//	if (itr != obj.MemberEnd()) {
		//		DSerializer serializer{ itr };
		//		if (compScript != nullptr)
		//			*compScript = std::move(ScriptComponent{ id }.Deserialize(serializer));
		//		else
		//			dreamECSGame->AddComponent(std::move(ScriptComponent{ id }.Deserialize(serializer)));
		//	}
		//	else if (compScript != nullptr) {
		//		dreamECSGame->RemoveComponent<ScriptComponent>(id);
		//	}
		//}

		//fileStream.close();
	}

}