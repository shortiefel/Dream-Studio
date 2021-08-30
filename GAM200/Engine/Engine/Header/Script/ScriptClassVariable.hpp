/* Start Header**********************************************************************************/
/*
@file    ScriptClassVariable.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    26/06/2021
\brief
This file contain 
-enum class for mono type to enum
-map for storing a CS class with its data


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef SCRIPT_CLASS_VARIABLE
#define SCRIPT_CLASS_VARIABLE


#include <string>

namespace Engine {
	namespace Scripting {

		/*-----------------------------------------------------------------------------------------------------------------------------------
		Script variable data
		-----------------------------------------------------------------------------------------------------------------------------------*/
		enum class CSType {
			NONE,
			CHAR,
			BOOL,
			FLOAT,
			INT,
			UINT,
			VEC2
		};

		class CSPublicVariable {
		public:
			std::string variableName;
			CSType variableType;

			//Function to give buffer space
			//Get variable type size
			
			//Set c# side with data
			//Get data
			

			CSPublicVariable(const std::string& vn, CSType type);
			
			//Dont allow copying because variableData is newed each time
			CSPublicVariable(const CSPublicVariable&) = delete;
			CSPublicVariable(CSPublicVariable&& rhs) noexcept;

			unsigned int GetVariableSize(CSType type) const;

			//Used for Editor to set the values
			void SetVariableData(void* data);
			void SetToCS();

			template<typename T>
			T GetVariableData() const{
				T value;
				GetVariableDataVoid(&value);
				return value;
			}


			~CSPublicVariable();

		private:
			void GetVariableDataVoid(void* value) const;

			void* variableData;
		};

	}
}

#endif