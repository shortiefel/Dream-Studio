/* Start Header**********************************************************************************/
/*
@file    Collider.cs
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    21/08/2021
\brief
This file has the function definition for Collider


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

using System.Runtime.CompilerServices; //For internal calls

public class Collider : IComponent
{
    //public uint entityId { get; set; }
    public Collider() { }
    public Collider(uint entity_id) { entityId = entity_id; }


    /*public bool GetActive()
    {
        GetCollider_Active_Engine(entityId, out bool _isActive);
        return _isActive;
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void GetCollider_Active_Engine(uint entityID, out bool _isActive);

    public void SetActive(bool _bool)
    {
        SetCollider_Active_Engine(entityId, _bool);
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void SetCollider_Active_Engine(uint entityID, bool _isActive);*/

}