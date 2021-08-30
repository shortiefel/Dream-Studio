using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
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
    public uint entityId { get; set;  }
    //-----------------------------------------------------------------------------------------------------------------
    //Position
    public Vec2 position
    {
        get { GetTransform_Position_Engine(entityId, out Vec2 result);
              return result; }
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
        get { GetTransform_Scale_Engine(entityId, out Vec2 result);
              return result; }
        set { SetTransform_Scale_Engine(entityId, ref value); }
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void GetTransform_Scale_Engine(uint entityID, out Vec2 outVec2);
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void SetTransform_Scale_Engine(uint entityID, ref Vec2 inVec2);

    public override string ToString() { return "Pos: " + position + " scale: " + scale; }

    public void Move(Vec2 dir)
    {

    }
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
Other scripts
----------------------------------------------------------------------------------------------------------------------------------------------------------------*/





/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
Collider
----------------------------------------------------------------------------------------------------------------------------------------------------------------*/





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
