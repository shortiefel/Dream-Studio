/* Start Header**********************************************************************************/
/*
@file    Serializer.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu			100%
@date    06/11/2021
\brief
#include "Engine/Header/Serialize/Serializer.hpp"
This file contain the Serializer declaration


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#pragma once

#include <string>
#include <functional>

#include "Engine/Header/Serialize/DSerializer.hpp"

namespace Engine {
	struct Entity;
	struct TransformComponent;
	struct ColliderComponent;
	struct RigidBodyComponent;
	struct CameraComponent;
	struct TextureComponent;
	struct UIComponent;
	struct FontComponent;
	struct SoundComponent;
	struct ParticleComponent;
	struct ScriptComponent;

	//class DSerializer;

	class Serializer {
	public:
		Serializer(const std::string& fp);
		~Serializer();

		void StartSerialize();
		void EndSerialize();

		void StartEntitySerialize(const Entity& entity);
		void EndEntitySerialize();

		//Serialize
		void AddData(const TransformComponent * const t);
		void AddData(const ColliderComponent* const t);
		void AddData(const RigidBodyComponent* const t);
		void AddData(const CameraComponent* const t);
		void AddData(const TextureComponent* const t);
		void AddData(const UIComponent* const t);
		void AddData(const FontComponent* const t);
		void AddData(const SoundComponent* const t);
		void AddData(const ParticleComponent* const t);
		void AddData(const ScriptComponent* const t);

		//Deserialize
		void DeserializeArray(std::function<void(void)> fp);

		unsigned int RetrieveId();
		Entity RetrieveEntity();
		bool RetrieveTransform();
		void RetrieveCollider();
		void RetrieveRigidBody();
		void RetrieveCamera();
		void RetrieveTexture();
		void RetrieveUI();
		void RetrieveFont();
		void RetrieveSound();
		void RetrieveParticle();
		void RetrieveScript();

		/*
		Param is data type in string
		Eg: TransformComponent, ColliderComponent
		If data type is found, return true
		*/
		bool SelectDataType(const std::string& type);

		void RetrieveData() { }
		/*
		1. There must be an even number of parameter
		2. Must alternate between String and (a data type) E.g RetrieveData("Position", position); position here is Vector 2
		*/
		template <typename G, typename... Types>
		void RetrieveData(std::string name, G& data, Types&... param) {
			data = deserializer.GetValue<G>(name.c_str());
			RetrieveData(param...);
		}
		
		rapidjson::GenericArray<true, rapidjson::Value> RetrieveDataArray(std::string name);

		

	private:
		DSerializer deserializer;
		rapidjson::Value arrayType;
		unsigned int arrayIndex = 0;

		static int seCounter;
		int entCounter = 0;
		std::string filePath = "";
	};
}
