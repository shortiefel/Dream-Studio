/* Start Header**********************************************************************************/
/*
@file    EngineTypes.cs
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    21/08/2021
\brief
This file has the function definition for EngineTypes


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

using System.Runtime.CompilerServices; //For internal calls


//Default Component that contains entityId
public interface Component
{
    uint entityId { get; set; }
}

/*public class Component
{
    public uint entityId;
}*/

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
Transform
----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
public struct Transform : Component
{
    public uint entityId { get; set; }
    //-----------------------------------------------------------------------------------------------------------------
    //Position
    public Vec2 position
    {
        get
        {
            GetTransform_Position_Engine(entityId, out Vec2 result);
            return result;
        }
        set { SetTransform_Position_Engine(entityId, ref value); }
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void GetTransform_Position_Engine(uint entityID, out Vec2 outVec2);
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void SetTransform_Position_Engine(uint entityID, ref Vec2 inVec2);
    //-----------------------------------------------------------------------------------------------------------------
    //Scale
    public Vec2 scale
    {
        get
        {
            GetTransform_Scale_Engine(entityId, out Vec2 result);
            return result;
        }
        set { SetTransform_Scale_Engine(entityId, ref value); }
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void GetTransform_Scale_Engine(uint entityID, out Vec2 outVec2);
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void SetTransform_Scale_Engine(uint entityID, ref Vec2 inVec2);
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

    public void Move(Vec2 dir)
    {
        MoveTransform_Position_Engine(entityId, ref dir);
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void MoveTransform_Position_Engine(uint entityID, ref Vec2 inVec2);

    //-----------------------------------------------------------------------------------------------------------------
    //Forward
    public Vec2 forward
    {
        get
        {
            GetTransform_forward_Engine(entityId, out Vec2 result);
            return result;
        }
        set {}
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void GetTransform_forward_Engine(uint entityID, out Vec2 outVec2);

    //-----------------------------------------------------------------------------------------------------------------
    //Right
    public Vec2 right
    {
        get
        {
            GetTransform_right_Engine(entityId, out Vec2 result);
            return result;
        }
        set {}
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void GetTransform_right_Engine(uint entityID, out Vec2 outVec2);

    public bool GetActive()
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
    internal static extern void SetTransform_Active_Engine(uint entityID, bool _isActive);

}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
Other scripts
----------------------------------------------------------------------------------------------------------------------------------------------------------------*/





/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
Collider
----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
public struct Collider : Component
{
    public uint entityId { get; set; }


    public bool GetActive()
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
    internal static extern void SetCollider_Active_Engine(uint entityID, bool _isActive);

}




/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
Rigidbody
----------------------------------------------------------------------------------------------------------------------------------------------------------------*/





/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
Camera2D
----------------------------------------------------------------------------------------------------------------------------------------------------------------*/





/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
Texture
----------------------------------------------------------------------------------------------------------------------------------------------------------------*/





/*----------------------------------------------------------------------------------------------------------------------------------------------------------------

----------------------------------------------------------------------------------------------------------------------------------------------------------------*/


/*public class GameObject
{
    public uint entityId;

    public Transform transform;
    *//*public Transform transform
    {
        get
        {
            Console.WriteLine("Getting values");
            GetTransform_Native(entityId, out Transform result);
            return result;
        } 
       set
        {
            Console.WriteLine("Setting values");
            SetTransform_Native(entityId, ref value);
        }
    }

    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void GetTransform_Native(uint entityID, out Transform outTransform);
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void SetTransform_Native(uint entityID, ref Transform inTransform);*//*
}*/
