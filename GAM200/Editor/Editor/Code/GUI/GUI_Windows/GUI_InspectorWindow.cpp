/* Start Header**********************************************************************************/
/*
@file    GUIWindow.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu		10%
					Goh See Yong, Denise   g.seeyongdenise@digipen.edu	10%
					 Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu	80%
@date    26/07/2021
\brief
This file contain the GUIWindow definition
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Editor/Header/GUI/GUI_Windows/GUI_InspectorWindow.hpp"
#include "Editor/Header/GUI/GUI_Imgui.hpp"

#include "Engine/Header/Management/FileWindowDialog.hpp"
#include "Engine/Header/Parent/ParentManager.hpp"
#include "Engine/Header/Graphic/ResourceSet.hpp"
#include "Engine/Header/ECS/Component/UI/FontComponent.hpp"
#include "Engine/Header/ECS/Component/UI/ButtonComponent.hpp"
#include "Engine/Header/Management/ResourceManager.hpp"
#include "Engine/Header/Graphic/ResourceSet.hpp"
#include "Engine/Header/ECS/Component/Sound/SoundComponent.hpp"
#include "Engine/Header/ECS/System/SoundSystem.hpp"
#include "Engine/Header/Management/SoundManager.hpp"
#include "Engine/Header/ECS/Component/Graphics/ParticleComponent.hpp"

#include "Engine/Header/Scene/Prefab.hpp"
#include "Engine/Header/Serialize/GameSceneSerializer.hpp"
#include "Engine/Header/Management/GameState.hpp"

#include "Engine/Header/Input/Input.hpp"

#include "Editor/Header/Commands/Command.hpp"
#include "Editor/Header/Commands/ObjectCommand.hpp"

#include <Imgui/imgui_internal.h>
#include <filesystem>

namespace Editor {
	extern const std::filesystem::path _assetPath;

	namespace GUI_Windows {

		void HelperMarker(const char* desc)
		{
			ImGui::TextDisabled("(?)");
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
				ImGui::TextUnformatted(desc);
				ImGui::PopTextWrapPos();
				ImGui::EndTooltip();
			}
		}


		void GUI_Inspector(bool* inspector_bool, float textSize, const Engine::Entity_id& entity_selected, ImGuiWindowFlags window_flags) {
			if (*inspector_bool) {
				/**
				*	WIDTH
				*/
				float halfWidth = ImGui::GetContentRegionAvail().x / 2.f;
				//float quadWidth = ImGui::GetContentRegionAvail().x / 2.5f;

				/**
				*	FONT
				*/
				ImGuiIO& io = ImGui::GetIO();
				auto boldFont = io.Fonts->Fonts[0];





				/**
				*	INSPECTOR STARTS
				*/
				ImGui::Begin("Inspector", inspector_bool, window_flags);


				/**
				*	Entity Names
				*/
				if (EntityId_Check(entity_selected)) {
					ImGui::End();
					return;
				}
				auto& entityMap = Engine::dreamECSGame->GetUsedEntityMap();
				if (entityMap.empty()) {
					ImGui::End();
					return;
				}
				const auto& itr = entityMap.find(entity_selected);
				if (itr == entityMap.end()) {
					ImGui::End();
					return;
				}

				std::string& entityName = itr->second.name;
				char eName[100];
				strcpy(eName, entityName.c_str());
				ImGui::PushItemWidth(textSize);
				ImGui::AlignTextToFramePadding();

				//ImGui::Text("Entity Name: ");
				//ImGui::SameLine(halfWidth);
				ImGui::SetNextItemWidth(halfWidth * 0.9f);
				if (ImGui::InputText("##EntityName", eName, 100)) {
					if (Engine::Input::IsKeyPressed(Engine::Input_KeyCode::Enter)) {
						std::string newName = std::string{ eName };
						Engine::dreamECSGame->DuplicateNameCheck(newName);
						Engine::dreamECSGame->ChangeName(entityName, newName);
						entityName = newName;

					}
				}

				ImGui::PopItemWidth();

				//ImGui::Spacing();
				ImGui::AlignTextToFramePadding();
				ImGui::SameLine(halfWidth);
				if (ImGui::Button("Add Component##addcomponentbtn", { ImGui::GetContentRegionAvail().x ,  0 }))
				{
					ImGui::OpenPopup("##addcomponentpopup");
				}

				if (ImGui::BeginPopup("##addcomponentpopup"))
				{

					ImGui::AlignTextToFramePadding();

					if (ImGui::Selectable(" + Transform##addTransformcom"))
						Engine::dreamECSGame->AddComponent<Engine::TransformComponent>(entity_selected);
					if (ImGui::Selectable(" + Collider##addTCollidercom"))
						Engine::dreamECSGame->AddComponent<Engine::ColliderComponent>(entity_selected);
					if (ImGui::Selectable(" + Texture##addTTexturecom"))
						Engine::dreamECSGame->AddComponent<Engine::TextureComponent>(entity_selected);
					if (ImGui::Selectable(" + Rigidbody##addRigidbodycom"))
						Engine::dreamECSGame->AddComponent<Engine::RigidBodyComponent>(entity_selected);
					if (ImGui::Selectable(" + Camera##addCameracom"))
						Engine::dreamECSGame->AddComponent<Engine::CameraComponent>(entity_selected);
					if (ImGui::Selectable(" + UI##addUIcom"))
						Engine::dreamECSGame->AddComponent<Engine::UIComponent>(entity_selected);
					if (ImGui::Selectable(" + Text##addTextcom"))
						Engine::dreamECSGame->AddComponent<Engine::FontComponent>(entity_selected);
					if (ImGui::Selectable(" + Sound##addSoundcom"))
						Engine::dreamECSGame->AddComponent<Engine::SoundComponent>(entity_selected);
					if (ImGui::Selectable(" + Particle##addParticlecom"))
						Engine::dreamECSGame->AddComponent<Engine::ParticleComponent>(entity_selected);
					if (ImGui::Selectable(" + Scripts##addScriptcom")) {
						std::string filePath = Engine::FileWindowDialog::OpenFile("Scripts (*.cs)\0*.cs\0", Engine::File_Dialog_Type::Scripts);

						if (!filePath.empty()) {
							REMOVE_FROM_FILEPATH;

							Engine::dreamECSGame->AddComponent(
								std::move(Engine::ScriptComponent{ entity_selected, filePath.c_str() }));
						}
					}


					ImGui::EndPopup();
				}



				/**
				*	Transform Properties
				*/
				Engine::TransformComponent* transComp = Engine::dreamECSGame->GetComponentPTR<Engine::TransformComponent>(entity_selected);
				if (transComp != nullptr)
				{
					DreamImGui::CheckBox_Dream("##TransformActive", &(transComp->isActive));
					ImGui::SameLine();

					if (ImGui::CollapsingHeader("Transform"))
					{
						/**
						*	Position
						*/
						ImGui::AlignTextToFramePadding();

						ImGui::Text("Position");
						ImGui::SameLine();
						HelperMarker("Position of the entity");
						ImGui::SameLine(halfWidth);
						ImGui::PushFont(boldFont);
						ImGui::Text(" X");
						ImGui::SameLine(halfWidth * 1.120f, 0);
						ImGui::SetNextItemWidth(halfWidth * 0.5f);
						if (ImGui::DragFloat("##TransformXPos", &transComp->localPosition.x, 0.1f, -360.0f, 360.f, "%.1f", 1))
							Engine::ParentManager::GetInstance().UpdateTruePos(entity_selected);


						ImGui::SameLine(halfWidth * 1.7f);
						ImGui::Text(" Y");
						ImGui::SameLine(halfWidth * 1.820f, 0);
						ImGui::SetNextItemWidth(halfWidth * 0.5f);
						if (ImGui::DragFloat("##TransformYPos", &transComp->localPosition.y, 0.1f, -360.0f, 360.f, "%.1f", 1))
							Engine::ParentManager::GetInstance().UpdateTruePos(entity_selected);

						ImGui::PopFont();


						/**
						*	Scale
						*/

						ImGui::Spacing();

						ImGui::AlignTextToFramePadding();

						ImGui::Text("Scale");
						ImGui::SameLine();
						HelperMarker("Scaling of the entity");
						ImGui::SameLine(halfWidth);
						ImGui::PushFont(boldFont);
						ImGui::Text(" X");
						ImGui::SameLine(halfWidth * 1.120f, 0);
						ImGui::SetNextItemWidth(halfWidth * 0.5f);
						if (ImGui::DragFloat("##TransformXscale", &transComp->scale.x, 0.1f, -360.0f, 360.f, "%.1f", 1))
							Engine::ParentManager::GetInstance().UpdateTruePos(entity_selected);
						ImGui::SameLine(halfWidth * 1.7f);
						ImGui::Text(" Y");
						ImGui::SameLine(halfWidth * 1.820f, 0);
						ImGui::SetNextItemWidth(halfWidth * 0.5f);
						if (ImGui::DragFloat("##TransformYscale", &transComp->scale.y, 0.1f, -360.0f, 360.f, "%.1f", 1))
							Engine::ParentManager::GetInstance().UpdateTruePos(entity_selected);

						ImGui::PopFont();

						/**
						*	Rotation
						*/
						ImGui::AlignTextToFramePadding();

						ImGui::Text("Rotation");
						ImGui::SameLine();
						HelperMarker("Rotation of the entity");
						ImGui::SameLine(halfWidth);
						ImGui::SetNextItemWidth(halfWidth);
						ImGui::PushFont(boldFont);
						if (ImGui::DragFloat("##TransformYrot", &transComp->angle, 0.1f, -360.0f, 360.f, "%.1f", 1))
							Engine::ParentManager::GetInstance().UpdateTruePos(entity_selected);

						ImGui::PopFont();


						/*
						*	Layer
						*/
						ImGui::Spacing();

						ImGui::AlignTextToFramePadding();
						ImGui::Text("Layer");
						ImGui::SameLine();
						HelperMarker("Assignment of entity to different layer");
						ImGui::SameLine(halfWidth);

						//selection
						static ImGuiComboFlags flags = 0;
						int index = static_cast<int>(transComp->layer);
						//arrays
						const int sz = 5;
						const char* layerName[sz] = { "Background", "Layer 1", "Layer 2", "Layer 3", "Layer 4" };
						const char* previewLayer = layerName[index];

						ImGui::AlignTextToFramePadding();
						ImGui::SetNextItemWidth(halfWidth);
						if (ImGui::BeginCombo("##TextureLayering", previewLayer, flags))
						{
							for (int i{ 0 }; i < sz; i++) {
								const bool isSelected = (index == i);
								if (ImGui::Selectable(layerName[i], isSelected)) {
									transComp->layer = i;
								}

								// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
								if (isSelected)
									ImGui::SetItemDefaultFocus();

							}

							ImGui::EndCombo();
						}

						ImGui::Spacing();

						/**
						*	DELETE
						*/
						ImGui::AlignTextToFramePadding();
						ImGui::SameLine(halfWidth);
						if (ImGui::Button("Delete Component##DeleteTransform", { ImGui::GetContentRegionAvail().x, 0 }))
							Engine::dreamECSGame->RemoveComponent<Engine::TransformComponent>(entity_selected);

					}

					//record the object state before change
					std::shared_ptr<ICommand> new_command = std::make_shared<ObjectTransformCommand>();
					UndoRedoManager::GetInstance().RecordState(new_command);
				}

				/*
				*	Collider for each component
				*/
				Engine::ColliderComponent* colComp = Engine::dreamECSGame->GetComponentPTR<Engine::ColliderComponent>(entity_selected);
				if (colComp != nullptr)
				{


					DreamImGui::CheckBox_Dream("##ColliderActive", &(colComp->isActive));
					ImGui::SameLine();

					if (ImGui::CollapsingHeader("Collider"))
					{

						/**
						*	Position
						*/
						ImGui::AlignTextToFramePadding();
						ImGui::Text("Position");
						ImGui::SameLine();
						HelperMarker("Collider position");
						ImGui::SameLine(halfWidth);

						ImGui::PushFont(boldFont);
						ImGui::Text(" X");
						ImGui::SameLine(halfWidth * 1.120f, 0);
						ImGui::SetNextItemWidth(halfWidth * 0.375f);
						ImGui::SameLine(halfWidth * 1.120f, 0);
						ImGui::SetNextItemWidth(halfWidth * 0.5f);
						if (ImGui::DragFloat("##ColliderXPos", &colComp->offset_position.x, 0.1f, -360.0f, 360.f, "%.1f", 1))
							Engine::ParentManager::GetInstance().UpdateTruePos(entity_selected);
						ImGui::SameLine(halfWidth * 1.7f);
						ImGui::Text(" Y");
						ImGui::SameLine(halfWidth * 1.820f, 0);
						ImGui::SetNextItemWidth(halfWidth * 0.5f);
						if (ImGui::DragFloat("##ColliderYPos", &colComp->offset_position.y, 0.1f, -360.0f, 360.f, "%.1f", 1))
							Engine::ParentManager::GetInstance().UpdateTruePos(entity_selected);
						ImGui::PopFont();

						ImGui::AlignTextToFramePadding();
						ImGui::Text("Collider Type");
						ImGui::SameLine();
						HelperMarker("Type of collider: Circle or Square");
						ImGui::SameLine(halfWidth);

						ImGui::PushFont(boldFont);
						//selection
						static ImGuiComboFlags flags = 0;
						int index = static_cast<int>(colComp->cType);
						//arrays
						const int sz = 2;
						const char* layerName[sz] = { "Circle", "Square" };
						const char* previewLayer = layerName[index];

						ImGui::AlignTextToFramePadding();
						ImGui::SetNextItemWidth(halfWidth);
						if (ImGui::BeginCombo("##ColliderLayering", previewLayer, flags))
						{
							for (int i{ 0 }; i < sz; i++) {
								const bool isSelected = (index == i);
								if (ImGui::Selectable(layerName[i], isSelected)) {
									colComp->cType = static_cast<Engine::ColliderType>(i);
								}

								// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
								if (isSelected)
									ImGui::SetItemDefaultFocus();

							}

							ImGui::EndCombo();
						}



						ImGui::PopFont();

						/**
						*	Scale
						*/
						ImGui::AlignTextToFramePadding();
						ImGui::Text("Scale");
						ImGui::SameLine();
						HelperMarker("Collider to scale by X and Y");

						ImGui::PushFont(boldFont);
						ImGui::SameLine(halfWidth);
						ImGui::Text(" X");
						ImGui::SameLine(halfWidth * 1.120f, 0);
						ImGui::SetNextItemWidth(halfWidth * 0.5f);
						if (ImGui::DragFloat("##ColliderXscale", &colComp->offset_scale.x, 0.1f, -360.0f, 360.f, "%.1f", 1))
							Engine::ParentManager::GetInstance().UpdateTruePos(entity_selected);
						ImGui::SameLine(halfWidth * 1.7f);
						ImGui::Text(" Y");
						ImGui::SameLine(halfWidth * 1.820f, 0);
						ImGui::SetNextItemWidth(halfWidth * 0.5f);
						if (ImGui::DragFloat("##ColliderYscale", &colComp->offset_scale.y, 0.1f, -360.0f, 360.f, "%.1f", 1))
							Engine::ParentManager::GetInstance().UpdateTruePos(entity_selected);
						ImGui::PopFont();


						/**
						*	Rotation
						*/
						ImGui::AlignTextToFramePadding();
						ImGui::Text("Rotation");
						ImGui::SameLine();
						HelperMarker("Collider to rotate by how many degree (cap to -360 and 360 degree)");
						ImGui::SameLine(halfWidth);
						ImGui::SetNextItemWidth(halfWidth);
						ImGui::PushFont(boldFont);
						if (ImGui::DragFloat("##ColliderRotate", &colComp->angle, 0.1f, -360.0f, 360.f, "%.1f", 1))
							Engine::ParentManager::GetInstance().UpdateTruePos(entity_selected);
						ImGui::PopFont();

						ImGui::Spacing();

						/**
						*	DELETE
						*/
						ImGui::AlignTextToFramePadding();
						ImGui::SameLine(halfWidth);
						if (ImGui::Button("Delete Component##DeleteCollider", { ImGui::GetContentRegionAvail().x, 0 }))
							Engine::dreamECSGame->RemoveComponent<Engine::ColliderComponent>(entity_selected);
					}
				}

				/*
				*	Camera component
				*/
				Engine::CameraComponent* camComp = Engine::dreamECSGame->GetComponentPTR<Engine::CameraComponent>(entity_selected);
				if (camComp != nullptr) {

					DreamImGui::CheckBox_Dream("##CameraActive", &(camComp->isActive));
					ImGui::SameLine();

					if (ImGui::CollapsingHeader("Camera"))
					{
						/**
						*	FOV
						*/
						ImGui::AlignTextToFramePadding();
						ImGui::Text("FOV");
						ImGui::SameLine();
						HelperMarker("Field of View");
						ImGui::SameLine(halfWidth);
						ImGui::SetNextItemWidth(halfWidth);
						ImGui::PushFont(boldFont);
						ImGui::InputFloat("##camFOV", &camComp->fov, 0.f, 0.f, "%.1f", ImGuiInputTextFlags_EnterReturnsTrue);
						ImGui::PopFont();

						/**
						*	Height
						*/
						ImGui::AlignTextToFramePadding();
						ImGui::Text("Height");
						ImGui::SameLine();
						HelperMarker("The distance of camera");
						ImGui::SameLine(halfWidth);
						ImGui::SetNextItemWidth(halfWidth);
						ImGui::PushFont(boldFont);
						ImGui::InputInt("##camheight", &camComp->height, 0);
						ImGui::PopFont();

						ImGui::Spacing();

						/**
						*	DELETE
						*/
						ImGui::AlignTextToFramePadding();
						ImGui::SameLine(halfWidth);
						if (ImGui::Button("Delete Component##DeleteCamera", { ImGui::GetContentRegionAvail().x, 0 }))
							Engine::dreamECSGame->RemoveComponent<Engine::CameraComponent>(entity_selected);

					}

				}


				/*
				*	RigidBody component
				*/
				Engine::RigidBodyComponent* rigidComp = Engine::dreamECSGame->GetComponentPTR<Engine::RigidBodyComponent>(entity_selected);
				{
					if (rigidComp != nullptr)
					{
						DreamImGui::CheckBox_Dream("##RidgidisActive", &(rigidComp->isActive));
						ImGui::SameLine();

						if (ImGui::CollapsingHeader("Rigidbody"))
						{
							/**
							*	Mass
							*/
							ImGui::AlignTextToFramePadding();
							ImGui::Text("Mass");
							ImGui::SameLine();
							HelperMarker("The mass of the entity \n  ");
							ImGui::SameLine(halfWidth);
							ImGui::SetNextItemWidth(halfWidth);
							ImGui::PushFont(boldFont);
							ImGui::InputInt("##objectMass", &rigidComp->mass, 0);
							if (rigidComp->mass == 0) { rigidComp->mass = 1; }
							ImGui::PopFont();

							/**
							*	LinearDrag
							*/
							ImGui::AlignTextToFramePadding();
							ImGui::Text("Linear Drag");
							ImGui::SameLine();
							HelperMarker("Positional movement ");
							ImGui::SameLine(halfWidth);
							ImGui::SetNextItemWidth(halfWidth);
							ImGui::PushFont(boldFont);
							ImGui::InputFloat("##LinearDrag", &rigidComp->linearDrag, 0.f, 0.f, "%.1f", ImGuiInputTextFlags_EnterReturnsTrue);
							ImGui::PopFont();

							/**
							*	AngularDrag
							*/
							ImGui::AlignTextToFramePadding();
							ImGui::Text("Angular Drag");
							ImGui::SameLine();
							HelperMarker("Affects rotational movement \n A higher value of drag will cause an object's rotation to come to rest more quickly following a force.");
							ImGui::SameLine(halfWidth);
							ImGui::SetNextItemWidth(halfWidth);
							ImGui::PushFont(boldFont);
							ImGui::InputFloat("##AngularDrag", &rigidComp->angularDrag, 0.f, 0.f, "%.1f", ImGuiInputTextFlags_EnterReturnsTrue);
							ImGui::PopFont();

							/**
							*	Speed
							*/
							ImGui::AlignTextToFramePadding();
							ImGui::Text("Speed");
							ImGui::SameLine(halfWidth);
							ImGui::SetNextItemWidth(halfWidth);
							ImGui::PushFont(boldFont);
							ImGui::InputFloat("##camFOV", &rigidComp->speed, 0.f, 0.f, "%.1f", ImGuiInputTextFlags_EnterReturnsTrue);
							ImGui::PopFont();

							ImGui::Spacing();

							/**
							*	DELETE
							*/
							ImGui::AlignTextToFramePadding();
							ImGui::SameLine(halfWidth);
							if (ImGui::Button("Delete Component##DeleteRigid", { ImGui::GetContentRegionAvail().x, 0 }))
								Engine::dreamECSGame->RemoveComponent<Engine::RigidBodyComponent>(entity_selected);


						}
					}
				}

				/*
				*	Texture component
				*/
				Engine::TextureComponent* textureComp = Engine::dreamECSGame->GetComponentPTR<Engine::TextureComponent>(entity_selected);
				if (textureComp != nullptr)
				{
					DreamImGui::CheckBox_Dream("##TextureActive", &(textureComp->isActive));
					ImGui::SameLine();


					if (ImGui::CollapsingHeader("Texture"))
					{
						/*
						*	Texture files
						*/
						ImGui::Spacing();

						ImGui::AlignTextToFramePadding();
						ImGui::Text("Texture");
						ImGui::SameLine(halfWidth);
						ImGui::SetNextItemWidth(halfWidth);
						ImGui::PushFont(boldFont);
						ImGui::Text(textureComp->textureName.c_str());
						ImGui::PopFont();

						ImGui::Spacing();

						ImGui::AlignTextToFramePadding();
						ImGui::SameLine(halfWidth * 1.2f);

						if (ImGui::BeginDragDropTarget())
						{
							ImGui::Text("I'm Dropping.");
							if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
							{
								const wchar_t* path = (const wchar_t*)payload->Data;
								std::filesystem::path texturePath = std::filesystem::path(_assetPath) / path;
								Engine::GraphicImplementation::SetTexture(textureComp, texturePath.string());
							}
							ImGui::EndDragDropTarget();
						}

						if (ImGui::Button("Change Texture##ChangeTextureTexture")) {

							std::string filePath = Engine::FileWindowDialog::OpenFile("Files | (*.jpg; *.jpeg; *.png; *.svg;)\0*.jpg; *.jpeg; *.png; *.svg;\0", Engine::File_Dialog_Type::Textures);

							if (!filePath.empty()) {
								Engine::GraphicImplementation::SetTexture(textureComp, filePath);
							}
						}

						ImGui::Spacing();

						ImGui::AlignTextToFramePadding();
						ImGui::SameLine(halfWidth * 1.2f);
						if (ImGui::Button("Refresh Texture##RefreshTextureTexture")) {
							Engine::ResourceManager::GetInstance().RefreshTexture(textureComp);
						}

						ImGui::Spacing();

						/**
						*	TEXTURE COLOR
						*/

						ImGui::AlignTextToFramePadding();
						ImGui::Text("Color");
						ImGui::SameLine(halfWidth);
						ImGui::ColorPicker4("Color", (float*)&textureComp->colour, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_DisplayRGB);

						ImGui::Spacing();

						/*
						*	Animation
						*/
						ImGui::AlignTextToFramePadding();
						ImGui::Text("Is Animation");
						ImGui::SameLine();
						HelperMarker("Is this entity to be animated");
						ImGui::SameLine(halfWidth);
						ImGui::SetNextItemWidth(halfWidth);
						DreamImGui::CheckBox_Dream("##isAnimation", &(textureComp->isAnimation));
						if (textureComp->isAnimation) {
							ImGui::AlignTextToFramePadding();
							/**
							*	TOTAL COLUMNS & ROWS
							*/
							ImGui::Text("Sprite Sheet");
							ImGui::PushFont(boldFont);
							ImGui::SameLine(halfWidth);
							ImGui::Text("Cols");
							ImGui::SameLine();
							HelperMarker("Total number of columns on sprite sheet");
							ImGui::SameLine(halfWidth * 1.5f, 0);
							ImGui::SetNextItemWidth(halfWidth * 0.5f);
							ImGui::InputInt("##AnimationTotalCols", &textureComp->totalColumns);

							ImGui::Spacing();

							ImGui::AlignTextToFramePadding();
							ImGui::SameLine(halfWidth);
							ImGui::Text("Rows");
							ImGui::SameLine();
							HelperMarker("Total number of rows on sprite sheet");
							ImGui::SameLine(halfWidth * 1.5f, 0);
							ImGui::SetNextItemWidth(halfWidth * 0.5f);
							ImGui::InputInt("##AnimationTotalRows", &textureComp->totalRows);
							ImGui::PopFont();

							ImGui::Spacing();
							ImGui::Spacing();

							ImGui::AlignTextToFramePadding();
							ImGui::Text("Start State");
							ImGui::SameLine();
							HelperMarker("List of Animation state created. To do so, add a state.");
							ImGui::SameLine(halfWidth);

							ImGui::AlignTextToFramePadding();
							ImGui::SetNextItemWidth(halfWidth);
							std::string& currAnimStateString = textureComp->currAnimationState;
							if (ImGui::BeginCombo("##StartAnimState", currAnimStateString.c_str())) {
								for (auto [name, animState] : textureComp->animationStateList) {

									if (ImGui::Selectable(name.c_str())) {
										currAnimStateString = name;
									}
								}
								ImGui::EndCombo();
							}

							ImGui::Spacing();
							ImGui::Spacing();

							ImGui::AlignTextToFramePadding();
							ImGui::Text("Add State");
							ImGui::SameLine(halfWidth);
							ImGui::SetNextItemWidth(halfWidth);

							char createAnim[100];
							strcpy(createAnim, "");
							if (ImGui::InputText("##createStatename", createAnim, 100)) {
								if (Engine::Input::IsKeyPressed(Engine::Input_KeyCode::Enter)) {
									textureComp->AddRefreshAnimationState(std::string{ createAnim });
								}
							}

							ImGui::Spacing();

					

							/**
							*	ANIMATION STATE
							*/
							ImGui::PushFont(boldFont);
							for (auto& [name, animState] : textureComp->animationStateList) {
								ImGui::AlignTextToFramePadding();
								ImGui::Text("State Name");
								ImGui::SameLine(halfWidth);
								ImGui::SetNextItemWidth(halfWidth);

								char aniDisplay[100];
								strcpy(aniDisplay, name.c_str());
								if (ImGui::InputText(std::string{ "##displayStatename" + name }.c_str(), aniDisplay, 100)) {
									if (Engine::Input::IsKeyPressed(Engine::Input_KeyCode::Enter)) {
										textureComp->AnimationStateRename(name, std::string{ aniDisplay });
									}
								}

								ImGui::AlignTextToFramePadding();
								ImGui::Text("Row");
								ImGui::SameLine();
								HelperMarker("Which row it starts on");
								ImGui::SameLine(halfWidth);
								ImGui::SetNextItemWidth(halfWidth * 0.5f);
								ImGui::InputInt(std::string{ "##AnimStateRow" + name }.c_str(), &animState.stateRow, 1);

								ImGui::AlignTextToFramePadding();
								ImGui::Text("Start Frame");
								ImGui::SameLine();
								HelperMarker("When do animation start");
								ImGui::SameLine(halfWidth);
								ImGui::SetNextItemWidth(halfWidth * 0.5f);
								ImGui::InputInt(std::string{ "##AnimStartFrame" + name }.c_str(), &animState.startX, 1);

								ImGui::AlignTextToFramePadding();
								ImGui::Text("End Frame");
								ImGui::SameLine();
								HelperMarker("When do animation end");
								ImGui::SameLine(halfWidth);
								ImGui::SetNextItemWidth(halfWidth * 0.5f);
								ImGui::InputInt(std::string{ "##AnimEndFrame" + name }.c_str(), &animState.endX, 1);

								ImGui::AlignTextToFramePadding();
								ImGui::Text("Time Per Frame");
								ImGui::SameLine();
								HelperMarker("How many times does it animate per frame");
								ImGui::SameLine(halfWidth);
								ImGui::SetNextItemWidth(halfWidth);
								ImGui::InputFloat(std::string{ "##AnimTimePerFrame" + name }.c_str(), &animState.fTime);

								ImGui::AlignTextToFramePadding();
								ImGui::Text("Is Loop");
								ImGui::SameLine(halfWidth);
								ImGui::SetNextItemWidth(halfWidth);
								DreamImGui::CheckBox_Dream(std::string{ "##AnimIsLoop" + name }.c_str(), &animState.isLoop);

								ImGui::Spacing();
							}
							ImGui::PopFont();

							ImGui::Spacing();
#if 0
							ImGui::AlignTextToFramePadding();
							ImGui::Text("Animation States");
							ImGui::SameLine(halfWidth);

							//selection
							static ImGuiComboFlags flags = 0;
							int index = static_cast<int>(transComp->layer);
							//arrays
							const int sz = 4;
							const char* layerName[sz] = { "Background", "Layer 1", "Layer 2", "Layer 3" };
							const char* previewLayer = layerName[index];

							ImGui::AlignTextToFramePadding();
							ImGui::SetNextItemWidth(halfWidth);
							if (ImGui::BeginCombo("##AnimationStates", previewLayer, flags))
							{
								for (auto [name, animState] : textureComp->animationStateList) {
									std::string& stateName = textureComp->currAnimationState;
									const bool isSelected = false;

									if (ImGui::Selectable(name.c_str(), isSelected)) {

									}
								}

								ImGui::EndCombo();
							}
#endif
						}


						ImGui::Spacing();
						/**
						*	DELETE
						*/
						ImGui::AlignTextToFramePadding();
						ImGui::SameLine(halfWidth);
						if (ImGui::Button("Delete Component##DeleteTexture", { ImGui::GetContentRegionAvail().x, 0 }))
							Engine::dreamECSGame->RemoveComponent<Engine::TextureComponent>(entity_selected);

					}
				}




				/*
				*	Text component
				*/
				Engine::FontComponent* textComp = Engine::dreamECSGame->GetComponentPTR<Engine::FontComponent>(entity_selected);
				if (textComp != nullptr)
				{
					DreamImGui::CheckBox_Dream("##TextActive", &(textComp->isActive));
					ImGui::SameLine();

					if (ImGui::CollapsingHeader("Text"))
					{
						/**
						*	INPUT TEXT
						*/
						std::string& textStuff = textComp->text;
						char textName[100];
						strcpy(textName, textStuff.c_str());
						ImGui::AlignTextToFramePadding();
						ImGui::Text("Input Text");
						ImGui::SameLine(halfWidth);
						ImGui::SetNextItemWidth(halfWidth * 1.8f);
						ImGui::PushFont(boldFont);
						if (ImGui::InputText("##textToInput", textName, IM_ARRAYSIZE(textName)))
						{
							textComp->text = textName;
						}
						ImGui::PopFont();

						ImGui::AlignTextToFramePadding();
						ImGui::Text("Font");
						ImGui::SameLine(halfWidth);
						ImGui::SetNextItemWidth(halfWidth);
						ImGui::PushFont(boldFont);
						ImGui::Text(textComp->fontName.c_str());
						ImGui::PopFont();

						if (ImGui::Button("Change Font##ChangeFont"))
						{

							std::string filePath = Engine::FileWindowDialog::OpenFile("Files | (*.ttf;)\0*.ttf;\0", Engine::File_Dialog_Type::Fonts);

							if (!filePath.empty()) {
								Engine::GraphicImplementation::SetFont(textComp, filePath);
							}
						}



						/**
						*	FONT COLOR
						*/
						ImGui::AlignTextToFramePadding();
						ImGui::Text("Color");
						ImGui::SameLine(halfWidth);
						ImGui::ColorPicker4("Color", (float*)&textComp->colour, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_DisplayRGB);

						ImGui::Spacing();

						/**
						*	DELETE
						*/
						if (ImGui::Button("Delete Component##DeleteText", { ImGui::GetContentRegionAvail().x, 0 }))
							Engine::dreamECSGame->RemoveComponent<Engine::FontComponent>(entity_selected);
					}
				}

				/*
				*	Sound component
				*/
				Engine::SoundComponent* soundComp = Engine::dreamECSGame->GetComponentPTR<Engine::SoundComponent>(entity_selected);
				if (soundComp != nullptr)
				{
					DreamImGui::CheckBox_Dream("##SoundActive", &(soundComp->isActive));
					ImGui::SameLine();

					if (ImGui::CollapsingHeader("Sound"))
					{
						ImGui::AlignTextToFramePadding();
						ImGui::Text("Add Sound");
						/*ImGui::SameLine(halfWidth);
						ImGui::Checkbox("##isSound", &(soundComp->isSound));*/
						//if (soundComp->isSound == true)
						//{
							//ImGui::Text("Sound Picker");
							ImGui::SameLine(halfWidth);
							if (ImGui::Button("Sound Picker##PickSound"))
							{
								soundComp->isSound = true;

								std::string filePath = Engine::FileWindowDialog::OpenFile("Files | (*.wav;)\0*.wav; \0");

								if (!filePath.empty())
								{
									soundComp->filepath = filePath = filePath.substr(filePath.rfind("Assets"));
									filePath = filePath.substr(filePath.find_last_of("\\") + 1);
									soundComp->soundName = filePath.substr(0, filePath.find_last_of("."));
									std::cout << soundComp->filepath << "\n";
									std::cout << soundComp->soundName << "\n";





									//Engine::SoundManager::GetInstance().GetSound(filePath, soundComp->soundName);
								}
							}
						//}

						ImGui::Spacing();

						ImGui::AlignTextToFramePadding();
						ImGui::Text("File");
						ImGui::SameLine(halfWidth);
						ImGui::SetNextItemWidth(halfWidth);
						ImGui::PushFont(boldFont);
						ImGui::Text(soundComp->soundName.c_str());
						ImGui::PopFont();

						ImGui::Spacing();

						ImGui::AlignTextToFramePadding();
						ImGui::Text("Loop");
						ImGui::SameLine(halfWidth);
						ImGui::Checkbox("##soundLoop", &soundComp->loop);

						ImGui::Spacing();

						ImGui::AlignTextToFramePadding();

						//selection
						static ImGuiComboFlags flags = 0;
						//int* index = reinterpret_cast<int*>(&Engine::SoundManager::GetInstance().SG);
						int* index = reinterpret_cast<int*>(&(soundComp->soundType));
						//arrays
						const char* soundName[] = { "MASTER", "MUSIC", "SFX" };
						ImGui::Text("Sound Group");
						ImGui::SameLine(halfWidth);
						ImGui::SetNextItemWidth(halfWidth);

						ImGui::Combo("##soundGroup", index, soundName, IM_ARRAYSIZE(soundName));
						if (static_cast<int>(soundComp->soundType) != *index)
						{
							soundComp->soundType = static_cast<Engine::SoundGrp>(*index);
						}

						ImGui::Spacing();

						ImGui::AlignTextToFramePadding();
						ImGui::Text("Test Sound");
						ImGui::SameLine(halfWidth);
						ImGui::SetNextItemWidth(halfWidth);
						if (ImGui::Button("Play"))
						{
							//int channelID = Engine::SoundManager::GetInstance().ChannelID;
							Engine::SoundSystem::GetInstance().SoundPlay(soundComp);

						}

						ImGui::SameLine(halfWidth * 1.25f);
						ImGui::SetNextItemWidth(halfWidth);
						if (ImGui::Button("Stop"))
						{
							//int channelID = Engine::SoundManager::GetInstance().ChannelID;
							std::cout << "stopping \n";
							Engine::SoundSystem::GetInstance().SoundStopAllSound();
						}

						ImGui::Spacing();

						/**
						*	DELETE
						*/
						ImGui::AlignTextToFramePadding();
						ImGui::SameLine(halfWidth);
						if (ImGui::Button("Delete Component##soundDelete", { ImGui::GetContentRegionAvail().x, 0 }))
							Engine::dreamECSGame->RemoveComponent<Engine::SoundComponent>(entity_selected);
					}

				}

				/*
				*	UI component
				*/
				Engine::UIComponent* uiComp = Engine::dreamECSGame->GetComponentPTR<Engine::UIComponent>(entity_selected);
				{
					if (uiComp != nullptr)
					{
						DreamImGui::CheckBox_Dream("##UIActive", &(uiComp->isActive));
						ImGui::SameLine();

						if (ImGui::CollapsingHeader("UI"))
						{
							ImGui::AlignTextToFramePadding();
							ImGui::Text("UI");
							ImGui::SameLine(halfWidth);
							ImGui::SetNextItemWidth(halfWidth);
							ImGui::Text(uiComp->textureName.c_str());


							ImGui::Spacing();
							ImGui::AlignTextToFramePadding();
							ImGui::SameLine(halfWidth * 1.2f);
							if (ImGui::Button("Change Texture##ChangeUITexture")) {
								std::string filePath = Engine::FileWindowDialog::OpenFile("Files | (*.jpg; *.jpeg; *.png; *.svg;)\0*.jpg; *.jpeg; *.png; *.svg;\0", Engine::File_Dialog_Type::Textures);

								if (!filePath.empty()) {
									Engine::GraphicImplementation::SetTexture(uiComp, filePath);
								}
							}

							ImGui::Spacing();

							/**
							*	DELETE
							*/
							ImGui::AlignTextToFramePadding();
							ImGui::SameLine(halfWidth);
							if (ImGui::Button("Delete Component##DeletUI", { ImGui::GetContentRegionAvail().x, 0 }))
								Engine::dreamECSGame->RemoveComponent<Engine::UIComponent>(entity_selected);

						}
					}
				}


				/**
				*	Scripts for each component
				*/
				Engine::ScriptComponent* scriptComp = Engine::dreamECSGame->GetComponentPTR<Engine::ScriptComponent>(entity_selected);
				if (scriptComp != nullptr) {
					//if (ImGui::TreeNode("Script")) {
					auto& scriptsList = scriptComp->klassInstance;

					for (auto& [className, csScriptInstance] : scriptsList) {
						//ImGui::Checkbox(className.c_str(), &(csScriptInstance.isActive));
						DreamImGui::CheckBox_Dream(std::string{ "##ScriptActive" + className }.c_str(), &(csScriptInstance.isActive));
						ImGui::SameLine();
						HelperMarker("Insert the script you have coded\n To edit the script, go to Editor->Assets->Script and select solution");
						ImGui::SameLine();
						if (ImGui::CollapsingHeader(std::string{ className + " (Script)" }.c_str()))
						{

							/**
							*	DELETE
							*/
							ImGui::AlignTextToFramePadding();
							//ImGui::SameLine(halfWidth);
							if (ImGui::Button("Delete Component##DeleteScript", { ImGui::GetContentRegionAvail().x, 0 }))
								Engine::dreamECSGame->RemoveScript(entity_selected, className.c_str());

						}
					}
				}

				/**
				*		PARTICLE
				*/
				Engine::ParticleComponent* particleComp = Engine::dreamECSGame->GetComponentPTR<Engine::ParticleComponent>(entity_selected);
				if (particleComp != nullptr)
				{
					DreamImGui::CheckBox_Dream("##ParticleActive", &(particleComp->isActive));
					ImGui::SameLine();

					if (ImGui::CollapsingHeader("Particle"))
					{

						/**
						*		FILE SELECTION
						*/
						ImGui::Spacing();
						ImGui::AlignTextToFramePadding();
						ImGui::Text("Particle");
						ImGui::SameLine(halfWidth);
						ImGui::SetNextItemWidth(halfWidth);
						ImGui::PushFont(boldFont);
						ImGui::Text(particleComp->filepath.c_str());
						ImGui::PopFont();

						ImGui::Spacing();

						ImGui::AlignTextToFramePadding();
						ImGui::SameLine(halfWidth * 1.2f);
						ImGui::SetNextItemWidth(halfWidth);
						if (ImGui::Button("Change Particle ##ChangeParticle"))
						{

							std::string filePath = Engine::FileWindowDialog::OpenFile("Files | (*.jpg; *.jpeg; *.png; *.svg;)\0*.jpg; *.jpeg; *.png; *.svg;\0", Engine::File_Dialog_Type::Textures);

							if (!filePath.empty()) {
								Engine::GraphicImplementation::SetTexture(particleComp, filePath);
							}
						}



						/**
						*	Position
						*/
						ImGui::AlignTextToFramePadding();
						ImGui::Text("Offset Position");
						ImGui::SameLine();
						HelperMarker("Particle Position from Object");
						ImGui::SameLine(halfWidth);
						ImGui::PushFont(boldFont);
						ImGui::Text(" X");
						ImGui::SameLine(halfWidth * 1.120f, 0);
						ImGui::SetNextItemWidth(halfWidth * 0.5f);
						ImGui::InputFloat("##offsetPosX", &particleComp->particleData.offsetPosition.x, 0.f, 0.f, "%.1f", 1);

						ImGui::SameLine(halfWidth * 1.7f);
						ImGui::Text(" Y");
						ImGui::SameLine(halfWidth * 1.820f, 0);
						ImGui::SetNextItemWidth(halfWidth * 0.5f);
						ImGui::InputFloat("##offsetPosY", &particleComp->particleData.offsetPosition.y, 0.f, 0.f, "%.1f", 1);

						ImGui::PopFont();

						ImGui::Spacing();


						/**
						*	EMIT SIZE
						*/
						ImGui::AlignTextToFramePadding();

						ImGui::Text("Emit Size");
						ImGui::SameLine();
						HelperMarker("How many particles generated per frame. \n E.g if emit size = 5, On click render -> 5 particles rendered");
						ImGui::SameLine(halfWidth);
						ImGui::PushFont(boldFont);
						ImGui::SetNextItemWidth(halfWidth * 0.5f);
						ImGui::InputInt("##emitSize", &particleComp->emitSize, 0, 0, 1);
						ImGui::PopFont();

						ImGui::Spacing();

						/**
						*	PARTICLE DURATION
						*/
						ImGui::AlignTextToFramePadding();

						ImGui::Text("Duration");
						ImGui::SameLine();
						HelperMarker("Lifetime per particle duration");
						ImGui::SameLine(halfWidth);
						ImGui::PushFont(boldFont);
						ImGui::SetNextItemWidth(halfWidth * 0.5f);
						ImGui::InputFloat("##duration", &particleComp->particleData.lifeTime, 0.f, 0.f, "%.1f", 1);
						ImGui::PopFont();

						ImGui::Spacing();


						/**
						*	LOOP
						*/
						ImGui::AlignTextToFramePadding();

						ImGui::Text("Loop");
						ImGui::SameLine(halfWidth);
						ImGui::SetNextItemWidth(halfWidth);
						ImGui::PushFont(boldFont);
						DreamImGui::CheckBox_Dream(std::string{ "##ParticlesLoop" + particleComp->filepath }.c_str(), &particleComp->isLooping);
						ImGui::PopFont();

						ImGui::Spacing();

						/**
						*	ANGLE
						*/

						ImGui::AlignTextToFramePadding();
						ImGui::Text("Random Angle");
						ImGui::SameLine();
						HelperMarker("False: no rotation of particles \nTrue: all particle rotates randomly.");
						ImGui::SameLine(halfWidth);
						ImGui::SetNextItemWidth(halfWidth);
						ImGui::PushFont(boldFont);
						DreamImGui::CheckBox_Dream(std::string{ "##ParticlesAngle" + particleComp->filepath }.c_str(), &particleComp->isAngleRandom);

						ImGui::PopFont();

						ImGui::Spacing();


						/**
						*	VELOCITY
						*/

						ImGui::Text("Velocity");
						ImGui::SameLine(halfWidth);
						ImGui::PushFont(boldFont);
						ImGui::Text(" X");
						ImGui::SameLine(halfWidth * 1.120f, 0);
						ImGui::SetNextItemWidth(halfWidth * 0.5f);
						ImGui::InputFloat("##particleVeloX", &particleComp->particleData.velocity.x, 0.f, 0.f, "%.1f", 1);

						ImGui::SameLine(halfWidth * 1.7f);
						ImGui::Text(" Y");
						ImGui::SameLine(halfWidth * 1.820f, 0);
						ImGui::SetNextItemWidth(halfWidth * 0.5f);
						ImGui::InputFloat("##particleVeloY", &particleComp->particleData.velocity.y, 0.f, 0.f, "%.1f", 1);

						ImGui::PopFont();

						ImGui::Spacing();

						/**
						*	VELOCITY VARIATION CHECK
						*/
						ImGui::AlignTextToFramePadding();

						ImGui::Text("Velocity Varies");
						ImGui::SameLine();
						HelperMarker("False: all particles will have the same velocity\n True: Random velocity of particles based on particle's velocity += a range from -(Variation/2) to (Variation/2).");
						ImGui::SameLine(halfWidth);
						ImGui::SetNextItemWidth(halfWidth);
						ImGui::PushFont(boldFont);
						DreamImGui::CheckBox_Dream(std::string{ "##veloVari" + particleComp->filepath }.c_str(), &particleComp->isVelocityVariation);

						ImGui::PopFont();

						ImGui::Spacing();


						/**
						*	VELOCITY VARIATION
						*/

						if (particleComp->isVelocityVariation == true)
						{
							ImGui::Text("Velocity Variations");
							ImGui::SameLine(halfWidth);
							ImGui::PushFont(boldFont);
							ImGui::Text(" X");
							ImGui::SameLine(halfWidth * 1.120f, 0);
							ImGui::SetNextItemWidth(halfWidth * 0.5f);
							ImGui::InputFloat("##particleVeloVariX", &particleComp->particleData.velocityVariation.x, 0.f, 0.f, "%.1f", 1);

							ImGui::SameLine(halfWidth * 1.7f);
							ImGui::Text(" Y");
							ImGui::SameLine(halfWidth * 1.820f, 0);
							ImGui::SetNextItemWidth(halfWidth * 0.5f);
							ImGui::InputFloat("##particleVeloVariY", &particleComp->particleData.velocityVariation.y, 0.f, 0.f, "%.1f", 1);

							ImGui::PopFont();

							ImGui::Spacing();
						}


						/**
						*		SIZE BEGIN
						*/
						ImGui::AlignTextToFramePadding();
						ImGui::Text("Size Begin");
						ImGui::SameLine(halfWidth);
						ImGui::PushFont(boldFont);
						ImGui::Text(" X");
						ImGui::SameLine(halfWidth * 1.120f, 0);
						ImGui::SetNextItemWidth(halfWidth * 0.5f);
						ImGui::InputFloat("##particleSizeBeginX", &particleComp->particleData.sizeBegin.x, 0.f, 0.f, "%.1f", 1);

						ImGui::SameLine(halfWidth * 1.7f);
						ImGui::Text(" Y");
						ImGui::SameLine(halfWidth * 1.820f, 0);
						ImGui::SetNextItemWidth(halfWidth * 0.5f);
						ImGui::InputFloat("##particleSizeBeginY", &particleComp->particleData.sizeBegin.y, 0.f, 0.f, "%.1f", 1);

						ImGui::PopFont();

						ImGui::Spacing();


						/**
						*		SIZE END
						*/
						ImGui::AlignTextToFramePadding();
						ImGui::Text("Size End");
						ImGui::SameLine(halfWidth);
						ImGui::PushFont(boldFont);
						ImGui::Text(" X");
						ImGui::SameLine(halfWidth * 1.120f, 0);
						ImGui::SetNextItemWidth(halfWidth * 0.5f);
						ImGui::InputFloat("##particleSizeEndX", &particleComp->particleData.sizeEnd.x, 0.f, 0.f, "%.1f", 1);

						ImGui::SameLine(halfWidth * 1.7f);
						ImGui::Text(" Y");
						ImGui::SameLine(halfWidth * 1.820f, 0);
						ImGui::SetNextItemWidth(halfWidth * 0.5f);
						ImGui::InputFloat("##particleSizeEndY", &particleComp->particleData.sizeEnd.y, 0.f, 0.f, "%.1f", 1);

						ImGui::PopFont();

						ImGui::Spacing();

						/**
						*		SIZE VARIATION
						*/
						ImGui::AlignTextToFramePadding();
						ImGui::Text("Size Variation");
						ImGui::SameLine();
						HelperMarker("if (0,0) = All same size \n if you have different sizes, the particle will be between begin and end of variation");
						ImGui::SameLine(halfWidth);
						ImGui::PushFont(boldFont);
						ImGui::Text(" X");
						ImGui::SameLine(halfWidth * 1.120f, 0);
						ImGui::SetNextItemWidth(halfWidth * 0.5f);
						ImGui::InputFloat("##particleSizeVarX", &particleComp->particleData.sizeVariation.x, 0.f, 0.f, "%.1f", 1);

						ImGui::SameLine(halfWidth * 1.7f);
						ImGui::Text(" Y");
						ImGui::SameLine(halfWidth * 1.820f, 0);
						ImGui::SetNextItemWidth(halfWidth * 0.5f);
						ImGui::InputFloat("##particleSizeVarY", &particleComp->particleData.sizeVariation.y, 0.f, 0.f, "%.1f", 1);

						ImGui::PopFont();

						ImGui::Spacing();


						/**
						*		COLOR  BEGIN
						*/
						ImGui::AlignTextToFramePadding();
						ImGui::Text("Color Begin");
						ImGui::SameLine();
						HelperMarker("Default = White(1,1,1,1) \n This shows that there is no color on top of texture. \n For particles to fade, Begin with (1,1,1,1) and End with (1,1,1,0)");
						ImGui::SameLine(halfWidth);
						ImGui::ColorPicker4("##pColorBegin", (float*)&particleComp->particleData.colorBegin, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_DisplayRGB);

						ImGui::Spacing();

						/**
						*		COLOR  END
						*/
						ImGui::AlignTextToFramePadding();
						ImGui::Text("Color End");
						ImGui::SameLine();
						HelperMarker("Default = White(1,1,1,1) \n This shows that there is no color on top of texture. \n For particles to fade, Begin with (1,1,1,1) and End with (1,1,1,0)");
						ImGui::SameLine(halfWidth);
						ImGui::ColorPicker4("##pColorEnd", (float*)&particleComp->particleData.colorEnd, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_DisplayRGB);

						ImGui::Spacing();



						/**
						*	DELETE
						*/
						ImGui::AlignTextToFramePadding();
						ImGui::SameLine(halfWidth);
						if (ImGui::Button("Delete Component##DeleteParticle", { ImGui::GetContentRegionAvail().x, 0 }))
							Engine::dreamECSGame->RemoveComponent<Engine::ParticleComponent>(entity_selected);


					}
				}


				/**
				*	Prefab
				*/
				const auto& prefabMap = Engine::dreamECSGame->GetConstPrefabMap();

				if (prefabMap.find(entity_selected) != prefabMap.end() && !(Engine::GameState::GetInstance().GetPlaying())) {
					const Engine::Prefab& prefab = prefabMap.find(entity_selected)->second;
					if (ImGui::Button("Update Prefab##prefabupdatebtn", { ImGui::GetContentRegionAvail().x, 0 })) {

						Engine::GameSceneSerializer::SerializePrefab(prefab.prefabName, entity_selected);
					}

					else if (ImGui::Button("Refresh Prefab##btn", { ImGui::GetContentRegionAvail().x, 0 }))
					{

						Engine::GameSceneSerializer::RefreshPrefab(prefab.prefabName, entity_selected);
					}
				}
				ImGui::End();
			}
		}
	}
}