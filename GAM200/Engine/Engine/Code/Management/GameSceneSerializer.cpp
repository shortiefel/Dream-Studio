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

#include "Engine/Header/Management/GameSceneSerializer.hpp"

#include "Engine/Header/Debug tools/Logging.hpp"

//External Resources
#include <sstream>

#include <rapidjson/document.h>

#include <rapidjson/writer.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>

#include "Engine/Header/ECS/Entity/EntityManager.hpp"
#include "Engine/Header/ECS/Coordinator.hpp"
#include "Engine/Header/ECS/Component/ComponentList.hpp"

#define Get2DFloatValue(str) \
	MathD::Vec2 {\
		itr->value[str].GetArray()[0].GetFloat(), \
		itr->value[str].GetArray()[1].GetFloat() }

namespace Engine {
	//extern EntityManager entityManager;
	extern Coordinator gCoordinator;

	void GameSceneSerializer::Serialize(std::string filename) {
		FILE* fp;
		fopen_s(&fp, filename.c_str(), "wb");

		if (!fp) {
			LOG_WARNING("File is not found");
			return;
		}
		
		char writeBuffer[1000];
		rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
		
		rapidjson::Document doc (rapidjson::kArrayType);

		const std::vector<Entity>& entList = gCoordinator.GetUsedEntityVector();
		size_t num = entList.size();
		for (size_t i = 0; i < num; i++) {
			rapidjson::Value entityObject(rapidjson::kObjectType);

			Transform* trans = nullptr;
			if (gCoordinator.HasCom<Transform>(trans, entList[i]) && trans != nullptr) {
				LOG_ASSERT(trans);
				rapidjson::Value objType(rapidjson::kObjectType);

				rapidjson::Value pos(rapidjson::kArrayType);
				pos.PushBack(trans->pos.x, doc.GetAllocator());
				pos.PushBack(trans->pos.y, doc.GetAllocator());
				objType.AddMember("Position", pos, doc.GetAllocator());

				rapidjson::Value scale(rapidjson::kArrayType);
				scale.PushBack(trans->scale.x, doc.GetAllocator());
				scale.PushBack(trans->scale.y, doc.GetAllocator());
				objType.AddMember("Scale", scale, doc.GetAllocator());

				entityObject.AddMember("Transform", objType, doc.GetAllocator());
			}

			Collider* col = nullptr;
			if (gCoordinator.HasCom<Collider>(col, entList[i]) && col != nullptr) {
				LOG_ASSERT(col);
				rapidjson::Value objType(rapidjson::kObjectType);

				objType.AddMember("ColliderType", rapidjson::Value((int)col->cType).Move(), doc.GetAllocator());

				rapidjson::Value pos(rapidjson::kArrayType);
				pos.PushBack(col->pos.x, doc.GetAllocator());
				pos.PushBack(col->pos.y, doc.GetAllocator());
				objType.AddMember("Position", pos, doc.GetAllocator());

				rapidjson::Value scale(rapidjson::kArrayType);
				scale.PushBack(col->scale.x, doc.GetAllocator());
				scale.PushBack(col->scale.y, doc.GetAllocator());
				objType.AddMember("Scale", scale, doc.GetAllocator());

				objType.AddMember("isMoveable", col->isMoveable, doc.GetAllocator());
				objType.AddMember("isTrigger", col->isTrigger, doc.GetAllocator());

				entityObject.AddMember("Collider", objType, doc.GetAllocator());
			}

			Camera2D* cam = nullptr;
			if (gCoordinator.HasCom<Camera2D>(cam, entList[i]) && cam != nullptr) {
				LOG_ASSERT(cam);
				rapidjson::Value objType(rapidjson::kObjectType);

				objType.AddMember("FOV", cam->fov, doc.GetAllocator());
				objType.AddMember("AR", cam->ar, doc.GetAllocator());
				objType.AddMember("isActive", cam->isActive, doc.GetAllocator());

				entityObject.AddMember("Camera2D", objType, doc.GetAllocator());
			}

			Texture* tex = nullptr;
			if (gCoordinator.HasCom<Texture>(tex, entList[i]) && tex != nullptr) {
				LOG_ASSERT(tex);
				rapidjson::Value objType(rapidjson::kObjectType);

				rapidjson::Value texFP;
				char buffer[200];
				int len = sprintf_s(buffer, "%s", tex->getFilepath().c_str());
				texFP.SetString(buffer, len, doc.GetAllocator());
				objType.AddMember("Filepath", texFP, doc.GetAllocator());

				rapidjson::Value shapeFP;
				
				len = sprintf_s(buffer, "%s", tex->get_mdl_ref()->first.c_str());
				shapeFP.SetString(buffer, len, doc.GetAllocator());
				objType.AddMember("Shape", shapeFP, doc.GetAllocator());

				rapidjson::Value shaderFP;
				len = sprintf_s(buffer, "%s", tex->get_shd_ref()->first.c_str());
				shaderFP.SetString(buffer, len, doc.GetAllocator());
				objType.AddMember("Shader", shaderFP, doc.GetAllocator());

				entityObject.AddMember("Texture", objType, doc.GetAllocator());
			}

			CSharpScript* script = nullptr;
			if (gCoordinator.HasCom<CSharpScript>(script, entList[i]) && script != nullptr) {
				LOG_ASSERT(script);
				rapidjson::Value objType(rapidjson::kObjectType);

				rapidjson::Value scriptFP;
				char buffer[200];
				int len = sprintf_s(buffer, "%s", script->className.c_str());
				scriptFP.SetString(buffer, len, doc.GetAllocator());
				objType.AddMember("Class", scriptFP, doc.GetAllocator());

				entityObject.AddMember("CSharpScript", objType, doc.GetAllocator());
			}

			doc.PushBack(entityObject, doc.GetAllocator());
		}
		rapidjson::Writer<rapidjson::FileWriteStream> writer(os);
		doc.Accept(writer);
	}

	void GameSceneSerializer::Deserialize(std::string filename) {
		FILE* fp;
		fopen_s(&fp, filename.c_str(), "rb");

		if (!fp) {
			LOG_WARNING("File is not found");
			return;
		}

		char readBuffer[1000];
		rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));

		rapidjson::Document doc;
		doc.ParseStream(is);

		fclose(fp);
		for (auto& obj : doc.GetArray()) {
			Entity ent = gCoordinator.createEntity();

			rapidjson::Value::ConstMemberIterator itr = obj.FindMember("Transform");
			if (itr != obj.MemberEnd()) {
				gCoordinator.AddComponent(ent, 
					Transform{
						Get2DFloatValue("Position"),
						Get2DFloatValue("Scale"),
					});
			}

			itr = obj.FindMember("Collider");
			if (itr != obj.MemberEnd()) {
				gCoordinator.AddComponent(ent,
					Collider {
						ColliderType(itr->value["ColliderType"].GetInt()),
						Get2DFloatValue("Position"),
						Get2DFloatValue("Scale"),
						itr->value["isMoveable"].GetBool(),
						itr->value["isTrigger"].GetBool()
					});
			}

			itr = obj.FindMember("Camera2D");
			if (itr != obj.MemberEnd()) {
				gCoordinator.AddComponent(ent,
					Camera2D {
						itr->value["FOV"].GetFloat(),
						itr->value["AR"].GetFloat(),
						itr->value["isActive"].GetBool()
					});
			}

			itr = obj.FindMember("Texture");
			if (itr != obj.MemberEnd()) {
				gCoordinator.AddComponent(ent,
					Texture {
						itr->value["Filepath"].GetString(),
						itr->value["Shape"].GetString(),
						itr->value["Shader"].GetString()
					});
			}

			itr = obj.FindMember("CSharpScript");
			if (itr != obj.MemberEnd()) {
				gCoordinator.AddComponent(ent,
					CSharpScript{
						itr->value["Class"].GetString()
					});
			}
		}
	}
}