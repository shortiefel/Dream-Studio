/* Start Header**********************************************************************************/
/*
@file    Serializer.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu			100%
@date    06/11/2021
\brief
#include "Engine/Header/Serialize/Serializer.hpp"
This file contain the Serializer definition


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Logging.hpp"

#include "Engine/Header/Serialize/Serializer.hpp"
#include "Engine/Header/Serialize/SSerializer.hpp"

#include "Engine/Header/ECS/DreamECS.hpp"

#include "Engine/Header/Management/ResourceManager.hpp"

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


namespace Engine {
	int Serializer::seCounter = 0;

	rapidjson::Value::ConstMemberIterator itr;
	rapidjson::Value arrayObjType;


	Serializer::Serializer(const std::string& fp) {
		filePath = fp;
	}

	Serializer::~Serializer() {
		if (seCounter != 0) LOG_ERROR("Serializer: Calls to StartSerialize and EndSerialize does not match!");
	}

	void Serializer::StartSerialize() {
		seCounter++;
		doc = rapidjson::Document{ rapidjson::kArrayType };
		
	}

	void Serializer::EndSerialize() {
		seCounter--;

		std::ofstream fileStream(filePath);
		rapidjson::OStreamWrapper osw(fileStream);

		rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
		doc.Accept(writer);

		fileStream.close();
	}

	void Serializer::StartEntitySerialize(const Entity& entity) {
		if (entCounter != 0) LOG_WARNING("Serializer: Calls to StartEntitySerialize and EndEntitySerialize does not match!");
		entCounter++;

		mainObject = rapidjson::Value{ rapidjson::kObjectType };

		rapidjson::Value objTypeEntity(rapidjson::kObjectType);

		SSerializer serializerEntity(doc, objTypeEntity);
		serializerEntity.SetValue("Name", entity.name);
		serializerEntity.SetValue("Parent", entity.parent);
		serializerEntity.SetValueSet("Child", entity.child);
		mainObject.AddMember("Entity", objTypeEntity, doc.GetAllocator());
	}
	
	void Serializer::StartEntitySerializePrefab(const Entity& entity) {
		if (entCounter != 0) LOG_WARNING("Serializer: Calls to StartEntitySerialize and EndEntitySerialize does not match!");
		entCounter++;

		mainObject = rapidjson::Value{ rapidjson::kObjectType };

		rapidjson::Value objTypeEntity(rapidjson::kObjectType);

		SSerializer serializerEntity(doc, objTypeEntity);
		serializerEntity.SetValue("Name", entity.name);
		serializerEntity.SetValue("EntityId", entity.id);
		serializerEntity.SetValue("Parent", entity.parent);
		serializerEntity.SetValueSet("Child", entity.child);
		mainObject.AddMember("Entity", objTypeEntity, doc.GetAllocator());
	}

	void Serializer::EndEntitySerialize() {
		entCounter--;
		doc.PushBack(mainObject, doc.GetAllocator());
	}

	void Serializer::AddData(const TransformComponent* const t) {
		if (t == nullptr) return;
		LOG_ASSERT(t); 
		rapidjson::Value objType(rapidjson::kObjectType); 
		SSerializer _serializer(doc, objType);
		
		_serializer.SetValue("Position", t->position);
		_serializer.SetValue("LocalPosition", t->localPosition);
		
		_serializer.SetValue("Scale", t->scale);
		_serializer.SetValue("Angle", t->angle);
		
		_serializer.SetValue("Layer", t->layer);
		_serializer.SetValue("IsActive", t->isActive);

		mainObject.AddMember("TransformComponent", objType, doc.GetAllocator());
	}

	void Serializer::AddData(const ColliderComponent* const t) {
		if (t == nullptr) return;
		LOG_ASSERT(t);
		rapidjson::Value objType(rapidjson::kObjectType);
		SSerializer _serializer(doc, objType);

		_serializer.SetValue("ColliderType", (int)t->cType);
		_serializer.SetValue("Position", t->offset_position);
		_serializer.SetValue("Scale", t->offset_scale);
		_serializer.SetValue("Angle", t->angle);
		_serializer.SetValue("IsTrigger", t->isTrigger);
		_serializer.SetValue("IsActive", t->isActive);
		
		mainObject.AddMember("ColliderComponent", objType, doc.GetAllocator());
	}

	void Serializer::AddData(const RigidBodyComponent* const t) {
		if (t == nullptr) return;
		LOG_ASSERT(t);
		rapidjson::Value objType(rapidjson::kObjectType);
		SSerializer _serializer(doc, objType);

		_serializer.SetValue("Speed", t->speed);

		_serializer.SetValue("Mass", t->mass);
		_serializer.SetValue("LinearDrag", t->linearDrag);
		_serializer.SetValue("AngularDrag", t->angularDrag);

		_serializer.SetValue("IsActive", t->isActive);

		mainObject.AddMember("RigidBodyComponent", objType, doc.GetAllocator());
	}

	void Serializer::AddData(const CameraComponent* const t) {
		if (t == nullptr) return;
		LOG_ASSERT(t);
		rapidjson::Value objType(rapidjson::kObjectType);
		SSerializer _serializer(doc, objType);

		_serializer.SetValue("Height", t->height);
		_serializer.SetValue("FOV", t->fov);
		_serializer.SetValue("AR", t->ar);

		_serializer.SetValue("IsActive", t->isActive);

		mainObject.AddMember("CameraComponent", objType, doc.GetAllocator());
	}

	void Serializer::AddData(const TextureComponent* const t) {
		if (t == nullptr) return;
		LOG_ASSERT(t);
		rapidjson::Value objType(rapidjson::kObjectType);
		SSerializer _serializer(doc, objType);

		_serializer.SetValue("Filepath", t->filepath);
		_serializer.SetValue("Shape", int(t->mdl_ref));

		_serializer.SetValue("Colour", t->colour);

		_serializer.SetValue("IsAnimation", t->isAnimation);

		/*cellWidth = static_cast<float>(width) / totalColumns;
		cellHeight = static_cast<float>(height) / totalRows;*/

		if (t->isAnimation) {
			_serializer.SetValue("TotalRow", t->totalRows);
			_serializer.SetValue("TotalColumns", t->totalColumns);

			_serializer.SetValue("CurrentAnimationState", t->currAnimationState);

			rapidjson::Value allAnimation(rapidjson::kArrayType);

			for (auto& [name, state] : t->animationStateList) {
				rapidjson::Value classObj(rapidjson::kObjectType);
				SSerializer cserializer(_serializer, classObj);

				cserializer.SetValue("StateName", state.stateName);
				cserializer.SetValue("StateRow", state.stateRow);
				cserializer.SetValue("StartFrame", state.startX);
				cserializer.SetValue("EndFrame", state.endX);
				cserializer.SetValue("TimePerFrame", state.fTime);
				cserializer.SetValue("IsLoop", state.isLoop);
				
				rapidjson::Value frameArrayType(rapidjson::kArrayType);
				SSerializer _framesSerializer(_serializer, frameArrayType);

				size_t tempv = state.frameTime.size();
				for (int i{ 0 }; i < tempv; i++)
				{
					frameArrayType.PushBack(state.frameTime[i], doc.GetAllocator());
				}

				classObj.AddMember("Frames", frameArrayType, doc.GetAllocator());


				_serializer.SetValueJSonArray(allAnimation, classObj);
			}

			_serializer.SetValueJSonArray("AnimationState", allAnimation);
		}

		_serializer.SetValue("IsActive", t->isActive);

		mainObject.AddMember("TextureComponent", objType, doc.GetAllocator());
	}

	void Serializer::AddData(const UIComponent* const t) {
		if (t == nullptr) return;
		LOG_ASSERT(t);
		rapidjson::Value objType(rapidjson::kObjectType);
		SSerializer _serializer(doc, objType);

		_serializer.SetValue("Filepath", t->filepath);
		_serializer.SetValue("Colour", t->colour);
		_serializer.SetValue("IsActive", t->isActive);

		mainObject.AddMember("UIComponent", objType, doc.GetAllocator());
	}

	void Serializer::AddData(const FontComponent* const t) {
		if (t == nullptr) return;
		LOG_ASSERT(t);
		rapidjson::Value objType(rapidjson::kObjectType);
		SSerializer _serializer(doc, objType);

		_serializer.SetValue("Filepath", t->filepath);
		_serializer.SetValue("Text", t->text);

		_serializer.SetValue("Colour", t->colour);

		_serializer.SetValue("IsActive", t->isActive);

		mainObject.AddMember("FontComponent", objType, doc.GetAllocator());
	}

	void Serializer::AddData(const SoundComponent* const t) {
		if (t == nullptr) return;
		LOG_ASSERT(t);
		rapidjson::Value objType(rapidjson::kObjectType);
		SSerializer _serializer(doc, objType);

		//_serializer.SetValue("SoundGrpType", (int)_SG);
		_serializer.SetValue("IsActive", t->isActive);
		_serializer.SetValue("IsLoop", t->loop);
		//_serializer.SetValue("IsPause", Pause);
		_serializer.SetValue("filepath", t->filepath);
		//std::cout << "filepath: " << filepath << "\n";
		_serializer.SetValue("volume", t->volume);
		_serializer.SetValue("isSound", t->isSound);
		_serializer.SetValue("IsMute", t->isMute);
		_serializer.SetValue("SoundGroup", static_cast<int>(t->soundType));

		mainObject.AddMember("SoundComponent", objType, doc.GetAllocator());
	}

	void Serializer::AddData(const WaypointComponent* const t) {
		if (t == nullptr) return;
		printf("adding data here \n");
		LOG_ASSERT(t);
		rapidjson::Value objType(rapidjson::kObjectType);
		SSerializer _serializer(doc, objType);

		_serializer.SetValue("Waypoints", t->listOfWaypoint);
		_serializer.SetValue("Order", t->numOfWaypoint);
		_serializer.SetValue("Section", t->section);

		mainObject.AddMember("WaypointComponent", objType, doc.GetAllocator());
	}

	void Serializer::AddData(const ParticleComponent* const t) {
		if (t == nullptr) return;
		LOG_ASSERT(t);
		rapidjson::Value objType(rapidjson::kObjectType);
		SSerializer _serializer(doc, objType);

		_serializer.SetValue("Filepath", t->filepath);
		_serializer.SetValue("Shape", int(t->mdl_ref));

		_serializer.SetValue("EmitSize", t->emitSize);
		_serializer.SetValue("IsActive", t->isActive);

		// Particle Data
		_serializer.SetValue("OffsetPosition", t->particleData.offsetPosition);

		_serializer.SetValue("Velocity", t->particleData.velocity);
		_serializer.SetValue("VelocityVariation", t->particleData.velocityVariation);

		_serializer.SetValue("ColorBegin", t->particleData.colorBegin);
		_serializer.SetValue("ColorEnd", t->particleData.colorEnd);

		_serializer.SetValue("SizeBegin", t->particleData.sizeBegin);
		_serializer.SetValue("SizeEnd", t->particleData.sizeEnd);
		_serializer.SetValue("SizeVariation", t->particleData.sizeVariation);

		_serializer.SetValue("LifeTime", t->particleData.lifeTime);

		// Particle loop
		_serializer.SetValue("IsLooping", t->isLooping);

		// Boolean for random effets
		_serializer.SetValue("IsAngleRandom", t->isAngleRandom);
		_serializer.SetValue("IsVelocityVariation", t->isVelocityVariation);

		mainObject.AddMember("ParticleComponent", objType, doc.GetAllocator());
	}

	void Serializer::AddData(const LightComponent* const t) {
		if (t == nullptr) return;
		LOG_ASSERT(t);
		rapidjson::Value objType(rapidjson::kObjectType);
		SSerializer _serializer(doc, objType);

		_serializer.SetValue("Ambient", t->ambient);
		_serializer.SetValue("Colour", t->colour);
		_serializer.SetValue("IsActive", t->isActive);

		mainObject.AddMember("LightComponent", objType, doc.GetAllocator());
	}

	void Serializer::AddData(const ScriptComponent* const t) {
		if (t == nullptr) return;
		LOG_ASSERT(t);
		rapidjson::Value objType(rapidjson::kArrayType);
		SSerializer _serializer(doc, objType);

		for (const auto& [className, scriptInstance] : t->klassInstance) {
			rapidjson::Value classObj(rapidjson::kObjectType);
			SSerializer cserializer(_serializer, classObj);

			cserializer.SetValue("Class", scriptInstance.csClass.fullName);
			cserializer.SetValue("IsActive", scriptInstance.isActive);

#if 0
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
#endif

			_serializer.SetValueJSonArray(classObj);
		}

		mainObject.AddMember("ScriptComponent", objType, doc.GetAllocator());
	}

	/*void Serializer::SetSerializeData(const std::string& str) {
		serializeTargetName = str; 

		temObjType = rapidjson::Value{ rapidjson::kObjectType };
		serializerMain = SSerializer(doc, temObjType);
	}*/





	bool Serializer::SelectDeserializeDataType(const std::string& type) {
		//arrayObjType is set in the DeserializeArray function
		itr = arrayObjType.FindMember(type.c_str());
		if (itr != arrayObjType.MemberEnd()) {
			deserializer.SetIterator(itr);
			return true;
		}

		return false;
	}

	rapidjson::GenericArray<true, rapidjson::Value> Serializer::RetrieveDataArray(std::string name) {
		if (!name.empty())
			return deserializer.GetValueArray(name.c_str());
		return deserializer.GetArray();
	}

	/*void Serializer::StartArrayRetrieveData(std::string name, void (*fp)()) {
		rapidjson::GenericArray arrayType = deserializer.GetValueArray(name.c_str());
		rapidjson::GenericArray::ValueType& testState = arrayType[0];

		for (auto& state : arrayType) {
			fp();
		}
	}*/


	void Serializer::DeserializeArray(std::function<void(void)> fp) {
		//FILE_CREATION(filename.c_str(), "rb");
		//FILE* fp = FileManager::GetInstance().Open_File(filename);
		std::ifstream fileStream(filePath);
		rapidjson::IStreamWrapper isw(fileStream);

		doc.ParseStream(isw);

		for (auto& obj : doc.GetArray()) {
			arrayObjType = obj;

			fp();
		}
		fileStream.close();
	}

//	unsigned int Serializer::RetrieveId() {
//		return entityId;
//	}
//
//	Entity Serializer::RetrieveEntity() {
//		std::string entityName = DEFAULT_ENTITY_NAME;
//		Entity_id parent = DEFAULT_ENTITY_ID; 
//		std::unordered_set<Entity_id> child{}; 
//			
//		itr = objType.FindMember("Entity");
//		if (itr != objType.MemberEnd()) {
//				DSerializer serializer{ itr };
//				entityName = serializer.GetValue<std::string>("Name"); 
//				parent = serializer.GetValue<unsigned int>("Parent"); 
//					
//		}
//		/*if (!SelectDataType("Entity")) return Entity{};
//		RetrieveData(
//			"Name", entityName,
//			"Parent", parent);*/
//
//		Entity entity = dreamECSGame->CreateEntity(entityName.c_str(), child, parent);
//		entityId = entity.id;
//
//		return entity;
//	}
//
//	bool Serializer::RetrieveTransform() {
//		TransformComponent tem(entityId);
//		if (!SelectDataType("TransformComponent")) return false;
//		RetrieveData(
//			"Position", tem.position,
//			"LocalPosition", tem.localPosition,
//			"Scale", tem.scale,
//			"Angle", tem.angle,
//			"Layer", tem.layer,
//			"IsActive", tem.isActive);
//
//		dreamECSGame->AddComponent(tem);
//		return true;
//
//		//DESERIALIZE(TransformComponent,
//		//TransformComponent tem(entityId);
//		///*tem.position = _serializer.GetValue<Math::vec2>("Position");
//		//tem.localPosition = _serializer.GetValue<Math::vec2>("LocalPosition");
//
//		//tem.scale = _serializer.GetValue<Math::vec2>("Scale");
//		//tem.angle = _serializer.GetValue<float>("Angle");
//
//		//tem.layer = _serializer.GetValue<int>("Layer");
//		//tem.isActive = _serializer.GetValue<bool>("IsActive");*/
//
//		////dreamECSGame->AddComponent(tem);
//
//		//return true;
//		//);
//
//		return false;
//	}
//
//	void Serializer::RetrieveCollider() {
//		DESERIALIZE(ColliderComponent,
//		ColliderComponent tem(entityId);
//		tem.cType = ColliderType(_serializer.GetValue<int>("ColliderType"));
//		tem.offset_position = _serializer.GetValue<Math::vec2>("Position");
//		tem.offset_scale = _serializer.GetValue<Math::vec2>("Scale");
//		tem.angle = _serializer.GetValue<float>("Angle");
//		tem.isTrigger = _serializer.GetValue<bool>("IsTrigger");
//		tem.isActive = _serializer.GetValue<bool>("IsActive");
//		);
//	}
//
//	void Serializer::RetrieveRigidBody() {
//		DESERIALIZE(RigidBodyComponent,
//		RigidBodyComponent tem(entityId);
//		tem.speed = _serializer.GetValue<float>("Speed");
//
//		tem.mass = _serializer.GetValue<int>("Mass");
//		/*linearVelocity = _serializer.GetValue<float>("LinearVelocity");
//		linearAcceleration = _serializer.GetValue<Math::vec2>("LinearAcceleration");*/
//		tem.linearDrag = _serializer.GetValue<float>("LinearDrag");
//
//		/*angularVelocity = _serializer.GetValue<float>("AngularVelocity");
//		angularAcceleration = _serializer.GetValue<float>("AngularAcceleration");*/
//		tem.angularDrag = _serializer.GetValue<float>("AngularDrag");
//
//		tem.isActive = _serializer.GetValue<bool>("IsActive");
//		);
//	}
//
//	void Serializer::RetrieveCamera() {
//		DESERIALIZE(CameraComponent,
//		CameraComponent tem(entityId);
//		tem.height = _serializer.GetValue<float>("Height");
//		tem.fov = _serializer.GetValue<float>("FOV");
//		tem.ar = _serializer.GetValue<float>("AR");
//
//		tem.isActive = _serializer.GetValue<bool>("IsActive");
//		);
//	}
//
//	void Serializer::RetrieveTexture() {
//		DESERIALIZE(TextureComponent,
//		TextureComponent tem(entityId);
//		GraphicImplementation::SetTexture(&tem, std::move(_serializer.GetValue<std::string>("Filepath")));
//
//		tem.mdl_ref = GraphicShape(_serializer.GetValue<int>("Shape"));
//
//		tem.colour = _serializer.GetValue<Math::vec4>("Colour");
//
//		// For animation
//		tem.isAnimation = _serializer.GetValue<bool>("IsAnimation");
//
//		if (tem.isAnimation) {
//			tem.totalRows = _serializer.GetValue<int>("TotalRow");
//			tem.totalColumns = _serializer.GetValue<int>("TotalColumns");
//
//			tem.cellWidth = static_cast<float>(tem.width) / tem.totalColumns;
//			tem.cellHeight = static_cast<float>(tem.height) / tem.totalRows;
//
//			tem.currAnimationState = _serializer.GetValue<std::string>("CurrentAnimationState");
//
//			auto animationStates = _serializer.GetValueArray("AnimationState");
//			for (auto& state : animationStates) {
//				std::string stateName = state["StateName"].GetString();
//
//				int stateRow = state["StateRow"].GetInt();
//
//				int startX = state["StartFrame"].GetInt();
//				int endX = state["EndFrame"].GetInt();
//
//				float fTime = state["TimePerFrame"].GetFloat();
//
//				bool isLoop = state["IsLoop"].GetBool();
//
//				AnimationState animstate = AnimationState(stateName, stateRow, startX, endX, fTime, isLoop);
//
//				tem.animationStateList.emplace(stateName, animstate);
//			}
//		}
//
//		tem.isActive = _serializer.GetValue<bool>("IsActive");
//		);
//	}
//
//	void Serializer::RetrieveUI() {
//		DESERIALIZE(UIComponent,
//		UIComponent tem(entityId);
//		GraphicImplementation::SetTexture(&tem, std::move(_serializer.GetValue<std::string>("Filepath")));
//
//		tem.colour = _serializer.GetValue<Math::vec4>("Colour");
//
//		tem.isActive = _serializer.GetValue<bool>("IsActive");
//		);
//	}
//
//	void Serializer::RetrieveFont() {
//		DESERIALIZE(FontComponent,
//		FontComponent tem(entityId);
//		GraphicImplementation::SetFont(&tem, std::move(_serializer.GetValue<std::string>("Filepath")));
//		tem.text = _serializer.GetValue<std::string>("Text");
//
//		tem.colour = _serializer.GetValue<Math::vec4>("Colour");
//
//		tem.isActive = _serializer.GetValue<bool>("IsActive");
//		);
//	}
//
//	void Serializer::RetrieveSound() {
//		DESERIALIZE(SoundComponent,
//		SoundComponent tem(entityId);
//		//SoundGrp(_serializer.GetValue<int>("SoundGrpType"));
//		tem.isActive = _serializer.GetValue<bool>("IsActive");
//		tem.loop = _serializer.GetValue<bool>("IsLoop");
//		//Pause = _serializer.GetValue<bool>("IsPause");
//		tem.filepath = _serializer.GetValue<std::string>("filepath");
//		tem.soundName = tem.filepath.substr(tem.filepath.find_last_of("\\") + 1);
//		tem.soundName = tem.soundName.substr(0, tem.soundName.find_last_of("."));
//
//		//SoundManager::GetInstance().GetSound(filepath, soundName);
//		tem.volume = _serializer.GetValue<float>("volume");
//		tem.isSound = _serializer.GetValue<bool>("isSound");
//		tem.soundType = static_cast<SoundGrp>(_serializer.GetValue<int>("SoundGroup"));
//		);
//	}
//
//	void Serializer::RetrieveParticle() {
//		DESERIALIZE(ParticleComponent,
//		ParticleComponent tem(entityId);
//		GraphicImplementation::SetTexture(&tem, std::move(_serializer.GetValue<std::string>("Filepath")));
//
//		tem.mdl_ref = GraphicShape(_serializer.GetValue<int>("Shape"));
//
//		tem.emitSize = _serializer.GetValue<int>("EmitSize");
//		tem.isActive = _serializer.GetValue<bool>("IsActive");
//
//		// Particle Data
//		Math::vec2 offsetPosition = _serializer.GetValue<Math::vec2>("OffsetPosition");
//
//		Math::vec2 velocity = _serializer.GetValue<Math::vec2>("Velocity");
//		Math::vec2 velocityVariation = _serializer.GetValue<Math::vec2>("VelocityVariation");
//
//		Math::vec4 colorBegin = _serializer.GetValue<Math::vec4>("ColorBegin");
//		Math::vec4 colorEnd = _serializer.GetValue<Math::vec4>("ColorEnd");
//
//		Math::vec2 sizeBegin = _serializer.GetValue<Math::vec2>("SizeBegin");
//		Math::vec2 sizeEnd = _serializer.GetValue<Math::vec2>("SizeEnd");
//		Math::vec2 sizeVariation = _serializer.GetValue<Math::vec2>("SizeVariation");
//
//		float lifeTime = _serializer.GetValue<float>("LifeTime");
//
//		(tem.particleData = { offsetPosition, velocity, velocityVariation,
//						 colorBegin, colorEnd, sizeBegin, sizeEnd, sizeVariation,
//						 lifeTime });
//
//		// Particle loop
//		tem.isLooping = _serializer.GetValue<bool>("IsLooping");
//
//		// Boolean for random effets
//		tem.isAngleRandom = _serializer.GetValue<bool>("IsAngleRandom");
//		tem.isVelocityVariation = _serializer.GetValue<bool>("IsVelocityVariation");
//		);
//	}
//
//	void Serializer::RetrieveScript() {
//		itr = objType.FindMember("ScriptComponent");
//		if (itr != objType.MemberEnd()) {
//			DSerializer _serializer{ itr };
//
//		ScriptComponent tem(entityId);
//		for (auto& classJSon : _serializer.GetArray()) {
//			const auto& fullName = classJSon["Class"].GetString();
//
//			CSScriptInstance csScriptInstance(
//				fullName,
//				classJSon["IsActive"].GetBool() );
//
//			rapidjson::Value::ConstMemberIterator variableItr = classJSon.FindMember("Variable");
//			if (!Scripting::InitCSClass(csScriptInstance, entityId)) { continue; }
//#if 0
//			if (variableItr != classJSon.MemberEnd()) {
//				for (auto& variableData : variableItr->value.GetArray()) {
//					const auto& variableName = variableData["Name"].GetString();
//					const auto& variableType = CSType{ variableData["Type"].GetInt() };
//
//
//					CSPublicVariable csPublicvariable{ variableName, variableType };
//
//					if (variableType == CSType::CHAR) {
//						char charData = static_cast<char>(variableData["Data"].GetInt());
//						csPublicvariable.SetVariableData(&charData);
//					}
//
//					else if (variableType == CSType::BOOL) {
//						bool boolData = variableData["Data"].GetBool();
//						csPublicvariable.SetVariableData(&boolData);
//					}
//
//					else if (variableType == CSType::FLOAT) {
//						float floatData = variableData["Data"].GetFloat();
//						csPublicvariable.SetVariableData(&floatData);
//					}
//					else if (variableType == CSType::INT) {
//						int intData = variableData["Data"].GetInt();
//						csPublicvariable.SetVariableData(&intData);
//					}
//					else if (variableType == CSType::UINT) {
//						unsigned int uinData = variableData["Data"].GetUint();
//						csPublicvariable.SetVariableData(&uinData);
//					}
//
//					else if (variableType == CSType::VEC2) {
//						Math::vec2 vec2Data{ variableData["Data"].GetArray()[0].GetFloat(),
//											variableData["Data"].GetArray()[1].GetFloat() };
//						csPublicvariable.SetVariableData(&vec2Data);
//					}
//					/*else if (variableType == CSType::GAMEOBJECT) {
//						const char* tem = variableData["Data"].GetString();
//						csPublicvariable.SetVariableData(const_cast<char*>(tem));
//					}*/
//
//					csScriptInstance.csVariableMap.emplace(variableName, std::move(csPublicvariable));
//				}
//
//			}
//#endif
//			//klassInstance[csScriptInstance.csClass.className] = std::move(csScriptInstance);
//			//Scripting::InitVariable(csScriptInstance);
//			//Scripting::InitScript(GetEntityId(), csScriptInstance);
//
//			tem.klassInstance.emplace(csScriptInstance.csClass.className, std::move(csScriptInstance));
//		}
//
//		dreamECSGame->AddComponent(std::move(tem));
//		}
//	}

}