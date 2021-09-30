/* Start Header**********************************************************************************/
/*
@file    ScriptClassVariable.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
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
#include "Engine/Header/Math/MathLib.hpp"

namespace Engine {
	CSPublicVariable::CSPublicVariable(const std::string& vn, CSType type) : variableName(vn), variableType(type) {
		unsigned int size = 0;
		size = GetVariableSize(variableType);
		variableData = new char[size];


		void* v = nullptr;

		if (variableType == CSType::FLOAT) {
			float tem{};
			v = &tem;
		}

		else if (variableType == CSType::INT) {
			int tem{};
			v = &tem;
		}

		else if (variableType == CSType::UINT) {
			unsigned int tem{};
			v = &tem;
		}

		else if (variableType == CSType::CHAR) {
			char tem{};
			v = &tem;
		}

		else if (variableType == CSType::BOOL) {
			bool tem{};
			v = &tem;
		}

		else if (variableType == CSType::VEC2) {
			Math::vec2 tem{};
			v = &tem;
		}

		SetVariableData(v);
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
		return 0;
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