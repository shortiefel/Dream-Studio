
#include "Editor/Header/GUI/GUI_Windows/GUI_InspectorWindow.hpp"
#include "Editor/Header/GUI/GUI_Imgui.hpp"
#include "Engine/Header/Layer/LayerStack.hpp"

#include "Engine/Header/Management/FileWindowDialog.hpp"
#include "Engine/Header/ECS/System/TransformCalculationSystem.hpp"
#include "Engine/Header/Graphic/TextureSet.hpp"

#include "Engine/Header/Input/Input.hpp"

//#include <Imgui/imgui_internal.h>

namespace Editor {
	namespace GUI_Windows {
		void GUI_Inspector(bool* inspector_bool, float textSize, const Engine::Entity_id& entity_selected, ImGuiWindowFlags window_flags) {
			if (*inspector_bool) {
				ImGui::Begin("Inspector", inspector_bool, window_flags);

				if (EntityId_Check(entity_selected)) {
					ImGui::End();
					return;
				}
				auto& entityMap = Engine::DreamECS::GetInstance().GetUsedEntityMap();
				////Remove if entity is deleted
				//const auto& itr = entityMap.find(entity_selected);
				//if (itr == entityMap.end()) {
				//	entity_selected = DEFAULT_ENTITY_ID;
				//	ImGui::End();
				//	return;
				//}
				//float width = 120;
				//bool selectEntity = 0;
				char eName[100];
				std::string& entityName = entityMap[entity_selected].name;
				strcpy(eName, entityName.c_str());
				ImGui::PushItemWidth(textSize);
				ImGui::Text("Entity Name: ");
				ImGui::SameLine();
				if (ImGui::InputText("##EntityName", eName, 100)) {
					if (Engine::Input::IsKeyPressed(Engine::Input_KeyCode::Enter)) {
						std::string newName = std::string{ eName };
						Engine::DreamECS::GetInstance().DuplicateNameCheck(newName);
						Engine::DreamECS::GetInstance().ChangeName(entityName, newName);
						entityName = newName;
					}
				}
				ImGui::PopItemWidth();

				/**
				*	Transform Properties
				*/
				Engine::TransformComponent* transComp = Engine::DreamECS::GetInstance().GetComponentPTR<Engine::TransformComponent>(entity_selected);
				if (transComp != nullptr)
				{
					ImGui::CheckBox_Dream("##TransformActive", &(transComp->isActive));
					ImGui::SameLine();

					if (ImGui::CollapsingHeader("Transform"))
					{
						ImGui::Spacing();
						//Updating of position
						ImGui::Text("Position");
						ImGui::Spacing();
						ImGui::Text("X: ");
						ImGui::SameLine();
						if (ImGui::InputFloat("##TransformXPos", &transComp->localPosition.x, 0.0f))
							Engine::TransformCalculationSystem::GetInstance().Update();
						ImGui::Text("Y: ");
						ImGui::SameLine();
						if (ImGui::InputFloat("##TransformYPos", &transComp->localPosition.y, 0.0f))
							Engine::TransformCalculationSystem::GetInstance().Update();


						//Updating of scaling
						ImGui::Text("Scaling ");
						ImGui::Spacing();
						ImGui::Text("X: ");
						ImGui::SameLine();
						if (ImGui::InputFloat("##TransformXscale", &transComp->scale.x, 0.0f))
							Engine::TransformCalculationSystem::GetInstance().Update();
						ImGui::Text("Y: ");
						ImGui::SameLine();
						if (ImGui::InputFloat("##TransformYscale", &transComp->scale.y, 0.0f))
							Engine::TransformCalculationSystem::GetInstance().Update();


						ImGui::Text("Rotation ");
						ImGui::Spacing();
						if (ImGui::SliderFloat("##TransformRotate", &transComp->angle, -360.f, 360.f))
							Engine::TransformCalculationSystem::GetInstance().Update();

						//deleteComponent
						if (ImGui::Button("Delete Component##DeleteTransform", { ImGui::GetContentRegionAvail().x, 0 }))
							Engine::DreamECS::GetInstance().RemoveComponent<Engine::TransformComponent>(entity_selected);


					}
				}

				/*
				*	Collider for each component
				*/
				Engine::ColliderComponent* colComp = Engine::DreamECS::GetInstance().GetComponentPTR<Engine::ColliderComponent>(entity_selected);
				if (colComp != nullptr)
				{

					ImGui::CheckBox_Dream("##ColliderActive", &(colComp->isActive));
					ImGui::SameLine();

					if (ImGui::CollapsingHeader("Collider"))
					{

						ImGui::Spacing();
						//Updating of position
						ImGui::Text("Position");
						ImGui::Spacing();
						ImGui::Text("X: ");
						ImGui::SameLine();
						ImGui::InputFloat("##ColliderXPos", &colComp->offset_position.x, 0.0f);
						ImGui::Text("Y: ");
						ImGui::SameLine();
						ImGui::InputFloat("##ColliderYPos", &colComp->offset_position.y, 0.0f);


						//Updating of scaling
						ImGui::Text("Scaling ");
						ImGui::Spacing();
						ImGui::Text("X: ");
						ImGui::SameLine();
						ImGui::InputFloat("##ColliderXscale", &colComp->offset_scale.x, 0.0f);
						ImGui::Text("Y: ");
						ImGui::SameLine();
						ImGui::InputFloat("##ColliderYscale", &colComp->offset_scale.y, 0.0f);


						ImGui::Text("Rotation ");
						ImGui::Spacing();
						ImGui::SliderFloat("##ColliderRotate", &colComp->angle, -360.f, 360.f);


						//deleteComponent
						if (ImGui::Button("Delete Component##DeleteCollider", { ImGui::GetContentRegionAvail().x, 0 }))
							Engine::DreamECS::GetInstance().RemoveComponent<Engine::ColliderComponent>(entity_selected);
					}
				}

				/*
				*	Camera component
				*/
				Engine::CameraComponent* camComp = Engine::DreamECS::GetInstance().GetComponentPTR<Engine::CameraComponent>(entity_selected);
				if (camComp != nullptr) {

					ImGui::CheckBox_Dream("##CameraActive", &(camComp->isActive));
					ImGui::SameLine();

					if (ImGui::CollapsingHeader("Camera"))
					{
						ImGui::Spacing();
						ImGui::Text("FOV");
						ImGui::SameLine();
						ImGui::InputFloat("##camFOV", &camComp->fov, 0.0f);
						ImGui::Text("Height");
						ImGui::SameLine();
						ImGui::InputInt("##camheight", &camComp->height, 0);

						//deleteComponent
						if (ImGui::Button("Delete Component##DeleteCamera", { ImGui::GetContentRegionAvail().x, 0 }))
							Engine::DreamECS::GetInstance().RemoveComponent<Engine::CameraComponent>(entity_selected);

					}

				}


				/*
				*	RigidBody component
				*/
				Engine::RigidBodyComponent* rigidComp = Engine::DreamECS::GetInstance().GetComponentPTR<Engine::RigidBodyComponent>(entity_selected);
				{
					if (rigidComp != nullptr)
					{
						ImGui::CheckBox_Dream("##RidgidisActive", &(rigidComp->isActive));
						ImGui::SameLine();

						if (ImGui::CollapsingHeader("Rigidbody"))
						{
							ImGui::Spacing();
							ImGui::Text("Speed");
							ImGui::SameLine();
							ImGui::InputFloat("##camFOV", &rigidComp->speed, 0.0f);

							//deleteComponent
							if (ImGui::Button("Delete Component##DeleteRigid", { ImGui::GetContentRegionAvail().x, 0 }))
								Engine::DreamECS::GetInstance().RemoveComponent<Engine::RigidBodyComponent>(entity_selected);
							
						}
					}
				}

				/*
				*	Texture component
				*/
				Engine::TextureComponent* textureComp = Engine::DreamECS::GetInstance().GetComponentPTR<Engine::TextureComponent>(entity_selected);
				if (textureComp != nullptr)
				{
					ImGui::CheckBox_Dream("##TextureActive", &(textureComp->isActive));
					ImGui::SameLine();


					if (ImGui::CollapsingHeader("Texture"))
					{

						/*
						*	Layer
						*/
						ImGui::Spacing();
						ImGui::Text("Layer");
						ImGui::SameLine();

						//selection
						static ImGuiComboFlags flags = 0;
						int index = static_cast<int>(textureComp->layerIndex);
						//arrays
						const int sz = 4;
						const char* layerName[sz] = { "Background", "UI Layer", "Manager", "Game Object" };
						const char* previewLayer = layerName[index];


						if (ImGui::BeginCombo("##Layering", previewLayer, flags))
						{
							for (int i{ 0 }; i < sz; i++) {
								const bool isSelected = (index == i);
								if (ImGui::Selectable(layerName[i], isSelected)) {
									textureComp->layerIndex = static_cast<Engine::GraphicLayer>(i);
								}

								// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
								if (isSelected)
									ImGui::SetItemDefaultFocus();

							}

							ImGui::EndCombo();
						}


						/*
						*	Texture files
						*/
						///files
						ImGui::Spacing();
						ImGui::Text("Texture: %s", textureComp->textureName.c_str());

						if (ImGui::Button("Change Texture##ChangeTextureTexture")) {
							std::string filePath = Engine::FileWindowDialog::OpenFile("Files | (*.jpg; *.jpeg; *.png; *.svg;)\0*.jpg; *.jpeg; *.png; *.svg;\0");

							if (!filePath.empty()) {
								Engine::GraphicImplementation::SetTexture(textureComp, filePath);
							}
						}


						//deleteComponent
						if (ImGui::Button("Delete Component##DeleteTexture", { ImGui::GetContentRegionAvail().x, 0 }))
							Engine::DreamECS::GetInstance().RemoveComponent<Engine::TextureComponent>(entity_selected);

					}
				}


				/*
				*	Text component
				*/



				/*
				*	Color component
				*/


				/*
				*	UI component
				*/
				Engine::UIComponent* uiComp = Engine::DreamECS::GetInstance().GetComponentPTR<Engine::UIComponent>(entity_selected);
				{
					if (uiComp != nullptr)
					{
						ImGui::CheckBox_Dream("##UIActive", &(uiComp->isActive));
						ImGui::SameLine();

						if (ImGui::CollapsingHeader("UI"))
						{
							ImGui::Text("Texture: %s", uiComp->textureName.c_str());

							if (ImGui::Button("Change Texture##ChangeUITexture")) {
								std::string filePath = Engine::FileWindowDialog::OpenFile("Files | (*.jpg; *.jpeg; *.png; *.svg;)\0*.jpg; *.jpeg; *.png; *.svg;\0");

								if (!filePath.empty()) {
									Engine::GraphicImplementation::SetTexture(uiComp, filePath);
								}
							}

							//deleteComponent
							if (ImGui::Button("Delete Component##DeletUI", { ImGui::GetContentRegionAvail().x, 0 }))
								Engine::DreamECS::GetInstance().RemoveComponent<Engine::UIComponent>(entity_selected);

						}
					}
				}





				/**
				*	Scripts for each component
				*/
				Engine::ScriptComponent* scriptComp = Engine::DreamECS::GetInstance().GetComponentPTR<Engine::ScriptComponent>(entity_selected);
				if (scriptComp != nullptr) {
					//if (ImGui::TreeNode("Script")) {
					auto& scriptsList = scriptComp->klassInstance;

					for (auto& [className, csScriptInstance] : scriptsList) {
						//ImGui::Checkbox(className.c_str(), &(csScriptInstance.isActive));
						ImGui::CheckBox_Dream(std::string{ "##ScriptActive" + className }.c_str(), &(csScriptInstance.isActive));
						ImGui::SameLine();
						if (ImGui::CollapsingHeader(std::string{ className + " (Script)" }.c_str()))
						{
							ImGui::Spacing();

							for (auto& [varName, csPublicVariable] : csScriptInstance.csVariableMap)
							{
								ImGui::Text(varName.c_str());
								ImGui::SameLine();
								switch (csPublicVariable.variableType)
								{
								case Engine::CSType::CHAR:
									//ImGui::InputFloat("A", (float*)csPublicVariable.GetVariableDataPTR<char>(), 0);
									break;
								case Engine::CSType::BOOL:
									ImGui::Checkbox(std::string{ "##" + varName }.c_str(), &(csPublicVariable.GetVariableData<bool>()));
									break;
								case Engine::CSType::FLOAT:
									ImGui::InputFloat(std::string{ "##" + varName }.c_str(), &(csPublicVariable.GetVariableData<float>()), 0);
									break;
								case Engine::CSType::INT:
									ImGui::InputInt(std::string{ "##" + varName }.c_str(), &(csPublicVariable.GetVariableData<int>()), 0);
									break;
								case Engine::CSType::UINT:
									//ImGui::InputFloat("E", (float*)csPublicVariable.GetVariableDataPTR<unsigned int>(), 0);
									break;
								case Engine::CSType::VEC2:
									Math::vec2& tem = csPublicVariable.GetVariableData<Math::vec2>();
									ImGui::InputFloat(std::string{ "##" + varName }.c_str(), &(tem.x), 0);
									ImGui::InputFloat(std::string{ "##" + varName }.c_str(), &(tem.y), 0);
									break;
								}
							}

							//deleteComponent
							if (ImGui::Button("Delete Component##DeleteScript", { ImGui::GetContentRegionAvail().x, 0 }))
								Engine::DreamECS::GetInstance().RemoveScript(entity_selected, className.c_str());

							ImGui::TreePop();
						}
					}
				}


				/**
				*	Add New Components
				*/

				if (ImGui::Button("Add Component##addcomponentbtn", { ImGui::GetContentRegionAvail().x, 0 }))
				{
					ImGui::OpenPopup("##addcomponentpopup");
				}
				if (ImGui::BeginPopup("##addcomponentpopup"))
				{
					float AvailWidth = ImGui::GetContentRegionAvail().x;
					ImGui::PushItemWidth(AvailWidth);

					if (ImGui::Selectable("Transform##addTransformcom"))
						Engine::DreamECS::GetInstance().AddComponent<Engine::TransformComponent>(entity_selected);
					if (ImGui::Selectable("Collider##addTCollidercom"))
						Engine::DreamECS::GetInstance().AddComponent<Engine::ColliderComponent>(entity_selected);
					if (ImGui::Selectable("Texture##addTTexturecom"))
						Engine::DreamECS::GetInstance().AddComponent<Engine::TextureComponent>(entity_selected);
					if (ImGui::Selectable("Rigidbody##addRigidbodycom"))
						Engine::DreamECS::GetInstance().AddComponent<Engine::RigidBodyComponent>(entity_selected);
					if (ImGui::Selectable("Script##addScriptcom"))
						Engine::DreamECS::GetInstance().AddComponent<Engine::ScriptComponent>(entity_selected);
					if (ImGui::Selectable("Camera##addCameracom"))
						Engine::DreamECS::GetInstance().AddComponent<Engine::CameraComponent>(entity_selected);
					if (ImGui::Selectable("UI##addUIcom"))
						Engine::DreamECS::GetInstance().AddComponent<Engine::UIComponent>(entity_selected);

					char text[100]{};
					ImGui::PushItemWidth(textSize);
					ImGui::Text("Script: ");
					if (ImGui::InputText("##addcomponenttype", text, 100)) {
						if (Engine::Input::IsKeyPressed(Engine::Input_KeyCode::Enter)) {
							std::string textStr{ text };
							Engine::DreamECS::GetInstance().AddComponent(
								//std::move(Engine::ScriptComponent{ entity_selected, textStr.c_str() }.Deserialize())
								std::move(Engine::ScriptComponent{ entity_selected, textStr.c_str() })
							);
						}
					}
					ImGui::PopItemWidth();

					ImGui::EndPopup();
				}


				ImGui::End();
			}
		}
	}
}