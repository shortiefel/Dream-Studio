/* Start Header**********************************************************************************/
/*
@file    InputCode.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    31/08/2021
\brief
This file has the enum for input codes


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef INPUT_CODE_HPP
#define INPUT_CODE_HPP


namespace Engine {
	enum class Input_MouseCode {
		Mouse_Left = 0,
		Mouse_Right = 1,
		Mouse_Middle = 2,
		Mouse_LeftSide_Front = 4,
		Mouse_LeftSide_Back = 3
	};

	//Numbers from ASCII Table and GLFW
	enum class Input_KeyCode {
		//Numbers on top of letters
		T0 = 48,
		T1 = 49,
		T2 = 50,
		T3 = 51,
		T4 = 52,
		T5 = 53,
		T6 = 54,
		T7 = 55,
		T8 = 56,
		T9 = 57,

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,
		
		//Function keys
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		
		//Left side
		Escape = 27,
		GraveAccent = 96, //` and ~ (Tilde)
		Tab = 9,
		CapsLock = 17,

		Shift = 160,
		Control = 162,
		Alt = 164,
		
		Space = 32,
		
		//Right side
		Minus = 45,
		Equal = 61,
		Backspace = 8,

		LeftBracket = 91,
		RightBracket = 93,
		BackSlash = 92, // \

		Semicolon = 59,
		Apostrophe = 39,
		Enter = 13,

		Comma = 44,
		Period = 46,
		FrontSlash = 47, /* / */
		

		PrintScreen = 283,
		ScrollLock = 281,
		Pause = 284,
		
		Insert = 260,
		Delete = 261,
		Home = 268,
		End = 269,
		PageUp = 266,
		PageDown = 267,

		//Arrow Keys
		Left = 263,
		Right = 262,
		Up = 265,
		Down = 264,

		//Keypad
		NumLock = 282,
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335
	};
}

#endif