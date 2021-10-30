/* Start Header**********************************************************************************/
/*
@file    Transform.cs
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    21/08/2021
\brief
This file has the function definition for Transform


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

using System.Runtime.CompilerServices; //For internal calls

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
Transform
----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
public class Transform : IComponent
{
    public uint entityId { get; set; }
    public Transform() { }
    public Transform(uint entity_id) { entityId = entity_id; }
    //-----------------------------------------------------------------------------------------------------------------
    //Position
    public Vector2 position
    {
        get
        {
            GetTransform_Position_Engine(entityId, out Vector2 result);
            return result;
        }
        set { SetTransform_Position_Engine(entityId, ref value); }
    }


    /* public Vector2 localPosition
     {
         get
         {
             GetTransform_Position_Engine(entityId, out Vector2 result);
             return result;
         }
         set { SetTransform_Position_Engine(entityId, ref value); }
     }*/
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void GetTransform_Position_Engine(uint entityID, out Vector2 outVec2);
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void SetTransform_Position_Engine(uint entityID, ref Vector2 inVec2);

    //-----------------------------------------------------------------------------------------------------------------
    //Scale
    public Vector2 scale
    {
        get
        {
            GetTransform_Scale_Engine(entityId, out Vector2 result);
            return result;
        }
        set { SetTransform_Scale_Engine(entityId, ref value); }
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void GetTransform_Scale_Engine(uint entityID, out Vector2 outVec2);
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void SetTransform_Scale_Engine(uint entityID, ref Vector2 inVec2);
    //-----------------------------------------------------------------------------------------------------------------
    //Angle
    public float angle
    {
        get
        {
            GetTransform_Angle_Engine(entityId, out float result);
            return result;
        }
        set { SetTransform_Angle_Engine(entityId, ref value); }
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void GetTransform_Angle_Engine(uint entityID, out float outVec2);
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void SetTransform_Angle_Engine(uint entityID, ref float inVec2);

    //public override string ToString() { return "Pos: " + position + " scale: " + scale; }

    public void Move(Vector2 dir)
    {
        MoveTransform_Position_Engine(entityId, ref dir);
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void MoveTransform_Position_Engine(uint entityID, ref Vector2 inVec2);

    //-----------------------------------------------------------------------------------------------------------------
    //Forward
    public Vector2 forward
    {
        get
        {
            GetTransform_forward_Engine(entityId, out Vector2 result);
            return result;
        }
        set { }
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void GetTransform_forward_Engine(uint entityID, out Vector2 outVec2);

    //-----------------------------------------------------------------------------------------------------------------
    //Right
    public Vector2 right
    {
        get
        {
            GetTransform_right_Engine(entityId, out Vector2 result);
            return result;
        }
        set { }
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void GetTransform_right_Engine(uint entityID, out Vector2 outVec2);

    /* public bool GetActive()
     {
         GetTransform_Active_Engine(entityId, out bool _isActive);
         return _isActive;
     }
     [MethodImpl(MethodImplOptions.InternalCall)]
     internal static extern void GetTransform_Active_Engine(uint entityID, out bool _isActive);

     public void SetActive(bool _bool)
     {
         SetTransform_Active_Engine(entityId, _bool);
     }
     [MethodImpl(MethodImplOptions.InternalCall)]
     internal static extern void SetTransform_Active_Engine(uint entityID, bool _isActive);*/

}
