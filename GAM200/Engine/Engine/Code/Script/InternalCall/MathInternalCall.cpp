/* Start Header**********************************************************************************/
/*
@file    MathInternalCall.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu		100%
@date    04/01/2022
\brief
#include "Engine/Header/Script/InternalCall/MathInternalCall.hpp"
This file contain the definition of MathInternalCall


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Script/InternalCall/MathInternalCall.hpp"
#include "Engine/Header/Math/MathLib.hpp"

#include <mono/jit/jit.h>

namespace Engine {
	namespace InternalCall {
		void Atan2_Engine(float* outFloat, float xVal, float yVal);
		void Approximately_Engine(float num1, float num2, bool* result);
		void Lerp_Engine(float* num1, float num2, float t);

		void GetDistance_Engine(float* outFloat, Math::vec2 a, Math::vec2 b);
		void GetLength_Engine(float* length, Math::vec2 vec);
		void GetNormalised_Engine(Math::vec2* vec);
		void DotProduct_Engine(float* outFloat, Math::vec2 lhs, Math::vec2 rhs);
		void AngleBetween_Engine(float* outFloat, Math::vec2 lhs, Math::vec2 rhs);

		void QuadraticBezier_Engine(Math::vec2 p0, Math::vec2 p1, Math::vec2 p2, float tVal, Math::vec2* vec, float* angle);

		void RegisterMathInternalCall() {
			mono_add_internal_call("Mathf::Atan2_Engine", Atan2_Engine);
			mono_add_internal_call("Mathf::Approximately_Engine", Approximately_Engine);
			mono_add_internal_call("Mathf::Lerp_Engine", Lerp_Engine);

			mono_add_internal_call("Vector2::GetDistance_Engine", GetDistance_Engine);
			mono_add_internal_call("Vector2::GetLength_Engine", GetLength_Engine);
			mono_add_internal_call("Vector2::GetNormalised_Engine", GetNormalised_Engine);
			mono_add_internal_call("Vector2::DotProduct_Engine", DotProduct_Engine);
			mono_add_internal_call("Vector2::AngleBetween_Engine", AngleBetween_Engine);

			mono_add_internal_call("Vector2::QuadraticBezier_Engine", QuadraticBezier_Engine);
		}

		void Atan2_Engine(float* outFloat, float xVal, float yVal) {
			if (Math::EpsilonCheck(xVal)) {
				*outFloat = 0.f;
				return;
			}
			*outFloat = atan2(yVal, xVal);
		}

		void Approximately_Engine(float num1, float num2, bool* result) {
			*result = Math::EpsilonCheck(num1, num2);
		}

		void Lerp_Engine(float* num1, float num2, float t) {
			*num1 = Math::Lerp(*num1, num2, t);
		}

		void GetDistance_Engine(float* outFloat, Math::vec2 a, Math::vec2 b) {
			*outFloat = Math::distance(a, b);
		}

		void GetLength_Engine(float* length, Math::vec2 vec) {
			*length = Math::length(vec);
		}

		void GetNormalised_Engine(Math::vec2* vec) {
			Math::vec2 temp = *vec;
			*vec = Math::normalize(temp);
		}

		void DotProduct_Engine(float* outFloat, Math::vec2 lhs, Math::vec2 rhs) {
			*outFloat = Math::dot(lhs, rhs);
		}

		void AngleBetween_Engine(float* outFloat, Math::vec2 lhs, Math::vec2 rhs) {
			*outFloat = Math::degrees(std::acos(Math::dot(Math::normalize(lhs), Math::normalize(rhs))));
		}

		void QuadraticBezier_Engine(Math::vec2 p0, Math::vec2 p1, Math::vec2 p2, float tVal, Math::vec2* vec, float* angle) {
			Math::vec2 
				fp = ((1 - tVal) * p0) + (tVal * p1),
				sp = ((1 - tVal) * p1) + (tVal * p2);

			*vec = ((1 - tVal) * fp) + (tVal * sp);
			Math::vec2 dir = sp - fp;
			*vec = fp + (tVal * (dir));
			*angle = Math::degrees(std::acos(Math::dot(Math::normalize(dir), Math::vec2{ 1.f,0.f })));
			if (dir.y < 0.f) *angle *= -1;

		}
	}
}