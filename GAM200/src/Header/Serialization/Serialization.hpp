/* Start Header**********************************************************************************/
/*!
\file Serialization.hpp
\team name Dream Studio
\software name
\authors
NAME							EMAIL									ROLE
Tan Wei Ling Felicia			weilingfelicia.tan@digipen.edu			PRODUCER
Goh	See Yong Denise				2001220@sit.singaporetech.edu.sg
Ow Jian Wen						jianwen123321@hotmail.com				TECHINCAL DIRECTOR
Chia Yi Da						chiayida98@gmail.com
Margaret Teo Boon See			Teo.b@digipen.edu
Wang Ao							Ao.Wang@digipen.edu
Ng Jia Yi						Jiayi.ng@digipen.edu
\date 24/05/2021
\brief
Serialization.hpp: This header file defines the base serializer.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/
#pragma once

#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <string>
//Base Serializer Class
class Serializer
{
public:
	//Open the serialization stream from file.
	virtual bool OpenFile(const std::string& file) = 0;

	//Does the stream stil have data?
	virtual bool Is_Good() = 0;

	//Reading types of file
	virtual void Read_Int(int& i) = 0;
	virtual void Read_Float(float& f) = 0;
	virtual void Read_String(std::string& str) = 0;
};

#endif

