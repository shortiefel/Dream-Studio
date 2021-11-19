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
#include "Engine/Header/Layer/LayerStack.hpp"

#include "Engine/Header/Management/FileWindowDialog.hpp"
#include "Engine/Header/ECS/System/TransformCalculationSystem.hpp"
#include "Engine/Header/Graphic/ResourceSet.hpp"
#include "Engine/Header/ECS/Component/UI/FontComponent.hpp"
#include "Engine/Header/ECS/Component/UI/ButtonComponent.hpp"
#include "Engine/Header/Management/ResourceManager.hpp"
#include "Engine/Header/Graphic/ResourceSet.hpp"

#include "Engine/Header/Scene/Prefab.hpp"
#include "Engine/Header/Serialize/GameSceneSerializer.hpp"
#include "Engine/Header/Management/GameState.hpp"

#include "Engine/Header/Input/Input.hpp"

#include "Engine/Header/Commands/Command.hpp"
#include "Engine/Header/Commands/ObjectCommand.hpp"

#include <Imgui/imgui_internal.h>
#include <filesystem>

namespace Editor {
	extern const std::filesystem::path _assetPath;
	namespace GUI_Windows {
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
					if (ImGui::Selectable(" + Scripts##addScriptcom")) {
						std::string filePath = Engine::FileWindowDialog::OpenFile("Scripts (*.cs)\0*.cs\0");

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
					ImGui::CheckBox_Dream("##TransformActive", &(transComp->isActive));
					ImGui::SameLine();

					if (ImGui::CollapsingHeader("Transform"))
					{
						/**
						*	Position
						*/
						ImGui::AlignTextToFramePadding();
				
						ImGui::Text("Position");
						ImGui::SameLine(halfWidth);
						ImGui::PushFont(boldFont);
						ImGui::Text(" X");
						ImGui::SameLine(halfWidth * 1.120f, 0);
						ImGui::SetNextItemWidth(halfWidth * 0.5f);
						if (ImGui::DragFloat("##TransformXPos", &transComp->localPosition.x, 0.1f, -360.0f, 360.f, "%.1f", 1))
							Engine::TransformCalculationSystem::GetInstance().Update();
						
						ImGui::SameLine(halfWidth * 1.7f);
						ImGui::Text(" Y");
						ImGui::SameLine(halfWidth * 1.820f, 0);
						ImGui::SetNextItemWidth(halfWidth * 0.5f);
						if (ImGui::DragFloat("##TransformYPos", &transComp->localPosition.y, 0.1f, -360.0f, 360.f, "%.1f", 1))
							Engine::TransformCalculationSystem::GetInstance().Update();

						ImGui::PopFont();


						/**
						*	Scale
						*/
						
						ImGui::Spacing();

						ImGui::AlignTextToFramePadding();
						
						ImGui::Text("Scale");
						ImGui::SameLine(halfWidth);
						ImGui::PushFont(boldFont);
						ImGui::Text(" X");
						ImGui::SameLine(halfWidth * 1.120f, 0);
						ImGui::SetNextItemWidth(halfWidth * 0.5f);
						if (ImGui::DragFloat("##TransformXscale", &transComp->scale.x, 0.1f, -360.0f, 360.f, "%.1f", 1))
							Engine::TransformCalculationSystem::GetInstance().Update();
						ImGui::SameLine(halfWidth * 1.7f);
						ImGui::Text(" Y");
						ImGui::SameLine(halfWidth * 1.820f, 0);
						ImGui::SetNextItemWidth(halfWidth * 0.5f);
						if (ImGui::DragFloat("##TransformYscale", &transComp->scale.y, 0.1f, -360.0f, 360.f, "%.1f", 1))
							Engine::TransformCalculationSystem::GetInstance().Update();

						ImGui::PopFont();

						/**
						*	Rotation
						*/
						ImGui::AlignTextToFramePadding();
					
						ImGui::Text("Rotation");
						ImGui::SameLine(halfWidth);
						ImGui::SetNextItemWidth(halfWidth);
						ImGui::PushFont(boldFont);
						if (ImGui::DragFloat("##TransformYrot", &transComp->angle, 0.1f, -360.0f, 360.f, "%.1f", 1))
							Engine::TransformCalculationSystem::GetInstance().Update();

						ImGui::PopFont();


						/*
						*	Layer
						*/
						ImGui::Spacing();

						ImGui::AlignTextToFramePadding();
						ImGui::Text("Layer");
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
					std::shared_ptr<Engine::ICommand> new_command = std::make_shared<Engine::ObjectAddCommand>();
					Engine::UndoRedoManager::GetInstance().RecordState(new_command);
				}

				/*
				*	Collider for each component
				*/
				Engine::ColliderComponent* colComp = Engine::dreamECSGame->GetComponentPTR<Engine::ColliderComponent>(entity_selected);
				if (colComp != nullptr)
				{


					ImGui::CheckBox_Dream("##ColliderActive", &(colComp->isActive));
					ImGui::SameLine();

					if (ImGui::CollapsingHeader("Collider"))
					{

						/**
						*	Position
						*/
						ImGui::AlignTextToFramePadding();
						ImGui::Text("Position");
						ImGui::SameLine(halfWidth);

						ImGui::PushFont(boldFont);
						ImGui::Text(" X");
						ImGui::SameLine(halfWidth * 1.120f, 0);
						ImGui::SetNextItemWidth(halfWidth * 0.375f);
						ImGui::SameLine(halfWidth * 1.120f, 0);
						ImGui::SetNextItemWidth(halfWidth * 0.5f);
						if (ImGui::DragFloat("##ColliderXPos", &colComp->offset_position.x, 0.1f, -360.0f, 360.f, "%.1f", 1))
							Engine::TransformCalculationSystem::GetInstance().Update();
						ImGui::SameLine(halfWidth * 1.7f);
						ImGui::Text(" Y");
						ImGui::SameLine(halfWidth * 1.820f, 0);
						ImGui::SetNextItemWidth(halfWidth * 0.5f);
						if (ImGui::DragFloat("##ColliderYPos", &colComp->offset_position.y, 0.1f, -360.0f, 360.f, "%.1f", 1))
							Engine::TransformCalculationSystem::GetInstance().Update();
						ImGui::PopFont();

						ImGui::AlignTextToFramePadding();
						ImGui::Text("Collider Type");
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

						ImGui::PushFont(boldFont);
						ImGui::SameLine(halfWidth);
						ImGui::Text(" X");
						ImGui::SameLine(halfWidth * 1.120f, 0);
						ImGui::SetNextItemWidth(halfWidth * 0.5f);
						if (ImGui::DragFloat("##ColliderXscale", &colComp->offset_scale.x, 0.1f, -360.0f, 360.f, "%.1f", 1))
							Engine::TransformCalculationSystem::GetInstance().Update();
						ImGui::SameLine(halfWidth * 1.7f);
						ImGui::Text(" Y");
						ImGui::SameLine(halfWidth * 1.820f, 0);
						ImGui::SetNextItemWidth(halfWidth * 0.5f);
						if (ImGui::DragFloat("##ColliderYscale", &colComp->offset_scale.y, 0.1f, -360.0f, 360.f, "%.1f", 1))
							Engine::TransformCalculationSystem::GetInstance().Update();
						ImGui::PopFont();


						/**
						*	Rotation
						*/
						ImGui::AlignTextToFramePadding();
						ImGui::Text("Rotation");
						ImGui::SameLine(halfWidth);
						ImGui::SetNextItemWidth(halfWidth);
						ImGui::PushFont(boldFont);
						if (ImGui::DragFloat("##ColliderRotate", &colComp->angle, 0.1f, -360.0f, 360.f, "%.1f", 1))
							Engine::TransformCalculationSystem::GetInstance().Update();
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

					ImGui::CheckBox_Dream("##CameraActive", &(camComp->isActive));
					ImGui::SameLine();

					if (ImGui::CollapsingHeader("Camera"))
					{
						/**
						*	FOV
						*/
						ImGui::AlignTextToFramePadding();
						ImGui::Text("FOV");
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
						ImGui::CheckBox_Dream("##RidgidisActive", &(rigidComp->isActive));
						ImGui::SameLine();

						if (ImGui::CollapsingHeader("Rigidbody"))
						{
							/**
							*	Mass
							*/
							ImGui::AlignTextToFramePadding();
							ImGui::Text("Mass");
							ImGui::SameLine(halfWidth);
							ImGui::SetNextItemWidth(halfWidth);
							ImGui::PushFont(boldFont);
							ImGui::InputInt("##objectMass", &rigidComp->mass, 0);
							if (rigidComp->mass == 0) { rigidComp->mass = 1;  }
							ImGui::PopFont();

							/**
							*	LinearDrag
							*/
							ImGui::AlignTextToFramePadding();
							ImGui::Text("Linear Drag");
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
					ImGui::CheckBox_Dream("##TextureActive", &(textureComp->isActive));
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
							
							std::string filePath = Engine::FileWindowDialog::OpenFile("Files | (*.jpg; *.jpeg; *.png; *.svg;)\0*.jpg; *.jpeg; *.png; *.svg;\0");

							if (!filePath.empty()) {
								Engine::GraphicImplementation::SetTexture(textureComp, filePath);
							}
						}

						if (ImGui::Button("Refresh Texture##RefreshTextureTexture")) {
							Engine::ResourceManager::GetInstance().RefreshTexture(textureComp);
						}

						

						/*
						*	Animation
						*/
						
						ImGui::AlignTextToFramePadding();

						ImGui::Text("Animation");
						ImGui::SameLine(halfWidth);
						ImGui::SetNextItemWidth(halfWidth);
						ImGui::Checkbox("##isAnimation",&(textureComp->isAnimation));
						if (textureComp->isAnimation == true)
						{
							ImGui::Spacing();
							ImGui::AlignTextToFramePadding();
							ImGui::Text("Looping");
							ImGui::SameLine(halfWidth);
							ImGui::SetNextItemWidth(halfWidth);
							ImGui::Checkbox("##isLoop", &(textureComp->isLoop));

							ImGui::Spacing();
							ImGui::AlignTextToFramePadding();
							ImGui::Text("Frame End");
							ImGui::SameLine(halfWidth);
							ImGui::SetNextItemWidth(halfWidth);
							ImGui::PushFont(boldFont);
							ImGui::InputInt("##frameEnd", &textureComp->endFrame, 0);
							ImGui::PopFont();


							ImGui::Spacing();
							ImGui::AlignTextToFramePadding();
							ImGui::Text("Time Per Frame");
							ImGui::SameLine(halfWidth);
							ImGui::SetNextItemWidth(halfWidth);
							ImGui::PushFont(boldFont);
							ImGui::InputFloat("##timeFrame", &textureComp->fTime, 0.f, 0.f, "%.1f", ImGuiInputTextFlags_EnterReturnsTrue);
							ImGui::PopFont();

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
					ImGui::CheckBox_Dream("##TextActive", &(textComp->isActive));
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
						ImGui::SetNextItemWidth(halfWidth *1.8f);
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

						if (ImGui::Button("Change Font##ChangeFont")) {

							std::string filePath = Engine::FileWindowDialog::OpenFile("Files | (*.ttf;)\0*.ttf;\0");

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
						ImGui::ColorPicker3("Color", (float*)&textComp->colour, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_DisplayRGB);
						ImGui::PushFont(boldFont);
						ImGui::Text(" R");
						ImGui::SameLine(halfWidth * 1.125f, 0);
						ImGui::SetNextItemWidth(halfWidth * 0.375f);
						ImGui::InputFloat("##colorRed", &textComp->colour.r, 0.f, 0.f, "%.1f", ImGuiInputTextFlags_EnterReturnsTrue);
						ImGui::SameLine(halfWidth * 1.5f);
						ImGui::Text(" G");
						ImGui::SameLine(halfWidth * 1.620f, 0);
						ImGui::SetNextItemWidth(halfWidth * 0.375f);
						ImGui::InputFloat("##colorGreen", &textComp->colour.g, 0.f, 0.f, "%.1f", ImGuiInputTextFlags_EnterReturnsTrue);
						ImGui::SameLine(halfWidth * 2.f);
						ImGui::Text(" B");
						ImGui::SameLine(halfWidth * 2.1f, 0);
						ImGui::SetNextItemWidth(halfWidth * 0.375f);
						ImGui::InputFloat("##colorBlue", &textComp->colour.b, 0.f, 0.f, "%.1f", ImGuiInputTextFlags_EnterReturnsTrue);
						ImGui::PopFont();

						//deleteComponent
						if (ImGui::Button("Delete Component##DeleteText", { ImGui::GetContentRegionAvail().x, 0 }))
							Engine::dreamECSGame->RemoveComponent<Engine::FontComponent>(entity_selected);
					}
				}

				/*
				*	Sound component
				*/
			/*	Engine::SoundComponent* soundComp = Engine::dreamECSGame->GetComponentPTR<Engine::SoundComponent>(entity_selected);
				if (soundComp != nullptr)
				{
					ImGui::CheckBox_Dream("##SoundActive", &(soundComp->isActive));
					ImGui::SameLine();

					if (ImGui::Button("Sound Picker##PickSound")) {
						std::string filePath = Engine::FileWindowDialog::OpenFile("Files | (*.wav; *");

					if (!filePath.empty()) {
							Engine::SoundComponent::Load(filePath);
						}
					}

				}*/



				/*
				*	Color component
				*/


				/*
				*	UI component
				*/
				Engine::UIComponent* uiComp = Engine::dreamECSGame->GetComponentPTR<Engine::UIComponent>(entity_selected);
				{
					if (uiComp != nullptr)
					{
						ImGui::CheckBox_Dream("##UIActive", &(uiComp->isActive));
						ImGui::SameLine();

						if (ImGui::CollapsingHeader("UI"))
						{
							ImGui::AlignTextToFramePadding();
							ImGui::Text("UI##UIComp");
							ImGui::SameLine(halfWidth);
							ImGui::SetNextItemWidth(halfWidth);
							ImGui::Text(uiComp->textureName.c_str());


							ImGui::Spacing();
							ImGui::AlignTextToFramePadding();
							ImGui::SameLine(halfWidth * 1.2f);
							if (ImGui::Button("Change Texture##ChangeUITexture")) {
								std::string filePath = Engine::FileWindowDialog::OpenFile("Files | (*.jpg; *.jpeg; *.png; *.svg;)\0*.jpg; *.jpeg; *.png; *.svg;\0");

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
						ImGui::CheckBox_Dream(std::string{ "##ScriptActive" + className }.c_str(), &(csScriptInstance.isActive));
						ImGui::SameLine();
						if (ImGui::CollapsingHeader(std::string{ className + " (Script)" }.c_str()))
						{
							//ImGui::Spacing();

							//for (auto& [varName, csPublicVariable] : csScriptInstance.csVariableMap)
							//{
							//	ImGui::Text(varName.c_str());
							//	ImGui::SameLine();
							//	switch (csPublicVariable.variableType)
							//	{
							//	case Engine::CSType::CHAR:
							//		//ImGui::InputFloat("A", (float*)csPublicVariable.GetVariableDataPTR<char>(), 0);
							//		break;
							//	case Engine::CSType::BOOL:
							//		ImGui::Checkbox(std::string{ "##" + varName }.c_str(), &(csPublicVariable.GetVariableData<bool>()));
							//		break;
							//	case Engine::CSType::FLOAT:
							//		ImGui::InputFloat(std::string{ "##" + varName }.c_str(), &(csPublicVariable.GetVariableData<float>()), 0);
							//		break;
							//	case Engine::CSType::INT:
							//		ImGui::InputInt(std::string{ "##" + varName }.c_str(), &(csPublicVariable.GetVariableData<int>()), 0);
							//		break;
							//	case Engine::CSType::UINT:
							//		//ImGui::InputFloat("E", (float*)csPublicVariable.GetVariableDataPTR<unsigned int>(), 0);
							//		break;
							//	case Engine::CSType::VEC2:
							//		Math::vec2& tem = csPublicVariable.GetVariableData<Math::vec2>();
							//		ImGui::InputFloat(std::string{ "##" + varName }.c_str(), &(tem.x), 0);
							//		ImGui::InputFloat(std::string{ "##" + varName }.c_str(), &(tem.y), 0);
							//		break;
							//	}
							//}

							/**
							*	DELETE
							*/
							ImGui::AlignTextToFramePadding();
							//ImGui::SameLine(halfWidth);
							if (ImGui::Button("Delete Component##DeleteScript", { ImGui::GetContentRegionAvail().x, 0 }))
								Engine::dreamECSGame->RemoveScript(entity_selected, className.c_str());

							//ImGui::TreePop();
						}
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