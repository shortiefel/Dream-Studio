/* Start Header**********************************************************************************/
/*!
\file System.hpp
\team name
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
\date 13/05/2021
\brief



Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/
#pragma once

#ifndef MESSAGE_H
#define MESSAGE_H

#pragma optimize("", off)

namespace Message_Id // Message id
{
    enum MessageIdType
    {
        None,
        Quit,
        Collide,
        ToggleDebugInfo,
        CharacterKey,
        MouseButton,
        MouseMove,
        FileDrop,
        CollisionStarted,
        CollisionPersisted,
        CollisionEnded,
        Collision
    };
}

///Base message class. New message types are defined by deriving from this
///class and mapping defined an element of the MessageIdType enumeration.
class Message
{
public:
    Message(Message_Id::MessageIdType id) : MessageId(id) {};
    Message_Id::MessageIdType MessageId;
    virtual ~Message() {};
};
#endif