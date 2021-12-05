/* Start Header**********************************************************************************/
/*
@file    Animation.cs
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    04/12/2021
\brief
This file has the function definition for Animation


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

using System.Runtime.CompilerServices; //For internal calls

using System;
public class Animation : IComponent
{
    public uint entityId { get; set; }
    public Animation() { }
    public Animation(uint entity_id) { entityId = entity_id; }

    public void Play(string _state)
    {
        SetAnimation_Engine(entityId, _state);
    }

    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void SetAnimation_Engine(uint entityID, string state);
}