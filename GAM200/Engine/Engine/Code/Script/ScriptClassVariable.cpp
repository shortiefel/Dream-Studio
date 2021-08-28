/* Start Header**********************************************************************************/
/*
@file    ScriptClassVariable.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    26/06/2021
\brief
This file contain definition for class PublicCSVariable


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Script/ScriptClassVariable.hpp"

namespace Engine {
	namespace Scripting {

		CSPublicVariable::CSPublicVariable(const std::string& vn, CSType type) : variableName(vn), variableType(type) {
			unsigned int size = 0;
			switch (variableType) {
			case CSType::FLOAT:
			case CSType::INT:
			case CSType::UINT:
				size = 4;
				break;
			case CSType::VEC2:
				size = 4 * 2;
				break;

			}
			//variableData = new char[size];
			//variableData = nullptr;
		}

		CSPublicVariable::CSPublicVariable(CSPublicVariable&& rhs) noexcept {
			
			variableName = std::move(rhs.variableName);
			variableType = rhs.variableType;

			//variableData = rhs.variableData;

			//rhs.variableData = nullptr;
		}

		void CSPublicVariable::SetVariableData(void* data) {

		}

		CSPublicVariable::~CSPublicVariable() {
			//delete[] variableData;
		}
	}
}