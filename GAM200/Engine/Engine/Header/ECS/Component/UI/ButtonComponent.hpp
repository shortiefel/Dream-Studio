/* Start Header**********************************************************************************/
/*
@file    Button.hpp
@author  Tan Wei Ling Felicia weilingfelicia.tan@digipen.edu
@date    26/10/2021
\brief
This file contain the declaration for ButtonComponent


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef BUTTON_COMPONENT_HPP
#define BUTTON_COMPONENT_HPP

#include "Engine/Header/ECS/Component/IComponent.hpp"
#include "Engine/Header/Event/MouseEvent.hpp"
#include "Engine/Header/ECS/Component/UI/FontComponent.hpp"
#include "Engine/Header/Management/ResourceManager.hpp"
#include "Engine/Header/Graphic/ResourceSet.hpp"
#include "Engine/Header/Graphic/mesh.hpp"

#include "Engine/Header/Serialize/DSerializer.hpp"
#include "Engine/Header/Serialize/SSerializer.hpp"


namespace Engine {
	struct ButtonComponent : public IComponent {
		public:

			//making use of std::function to store, copy, and invoke any CopyConstructible Callable target 
			using Action = std::function<void()>;

			ButtonComponent(const std::string& label);
			bool OnClick(const Engine::MousePressedEvent& e);
			bool OnRelease(const Engine::MouseReleasedEvent& e);
			bool OnMove(const Engine::MouseMoveEvent& e);

			inline void SetLabel(const std::string& label) { ButtonLabel = label; }
			inline const std::string& GetLabel() const { return ButtonLabel; }

			inline void SetFont(FontComponent* fonts) { Fonts = fonts; }
			inline const FontComponent& GetFont() const { return *Fonts; }

			inline void SetAction(const Action& action) { AHandler = action; }

			void OnAction();
			void OnUpdate();
			void OnRender(); 

			ButtonComponent& Deserialize(const DSerializer& _serializer);
			void Serialize(const SSerializer& _serializer);

		private:
			enum ButtonState
			{
				PRESSED,
				RELEASED
			};
			std::string ButtonLabel;
			ButtonState BState;
			FontComponent* Fonts;
			Action AHandler;

			static void NoAction() {}


	};
}

#endif