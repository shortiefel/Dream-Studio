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
#include <glm/glm.hpp>

namespace Engine {
	namespace Scripting {

		CSPublicVariable::CSPublicVariable(const std::string& vn, CSType type) : variableName(vn), variableType(type) {
			unsigned int size = 0;
			size = GetVariableSize(variableType);
			variableData = new char[size];
		}

		unsigned int CSPublicVariable::GetVariableSize(CSType type) const {
			switch (type) {

			case CSType::FLOAT:
			case CSType::INT:
			case CSType::UINT:
				return 4;
			case CSType::CHAR:
			case CSType::BOOL:
				return 1;
				break;
			case CSType::VEC2:
				return (4 * 2);
			}
		}

		CSPublicVariable::CSPublicVariable(CSPublicVariable&& rhs) noexcept {
			
			variableName = std::move(rhs.variableName);
			variableType = rhs.variableType;

			variableData = rhs.variableData;

			rhs.variableData = nullptr;
		}

		void CSPublicVariable::SetVariableData(void* data) {
			memcpy(variableData, data, GetVariableSize(variableType));
		}

		void CSPublicVariable::GetVariableDataVoid(void* value) const {
			memcpy(value, variableData, GetVariableSize(variableType));
		}

		CSPublicVariable::~CSPublicVariable() {
			delete[] variableData;
		}
	}
}