/* Start Header**********************************************************************************/
/*
@file    Rigidbody2D.cs
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    08/11/2021
\brief
This file has the function definition for Rigidbody2D


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

using System.Runtime.CompilerServices; //For internal calls

public class Rigidbody2D : IComponent
{
    public uint entityId { get; set; }
    public Rigidbody2D() { }
    public Rigidbody2D(uint entity_id) { entityId = entity_id; }

    public Vector2 velocity
    {
        get
        {
            GetRigidbody_LinearVelocity_Engine(entityId, out Vector2 velocity);
            return velocity;
        }
        set { SetRigidbody_LinearVelocity_Engine(entityId, ref value); }
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void GetRigidbody_LinearVelocity_Engine(uint entityID, out Vector2 velocity);
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void SetRigidbody_LinearVelocity_Engine(uint entityID, ref Vector2 inVec2);

    public float angularVelocity
    {
        get
            {
                GetRigidbody_AngularVelocity_Engine(entityId, out float velocity);
                return velocity;
            }
        set
            { SetRigidbody_AngularVelocity_Engine(entityId, ref value); }
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void GetRigidbody_AngularVelocity_Engine(uint entityID, out float velocity);
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void SetRigidbody_AngularVelocity_Engine(uint entityID, ref float inVec2);

/* public float inertia
 {
     get
     {
         GetRigidbody_Inertia_Engine(entityId, out float result);
         return result;
     }
     set { SetRigidbody_Inertia_Engine(entityId, ref value); }
 }
 [MethodImpl(MethodImplOptions.InternalCall)]
 internal static extern void GetRigidbody_Inertia_Engine(uint entityID, out float result);
 [MethodImpl(MethodImplOptions.InternalCall)]
 internal static extern void SetRigidbody_Inertia_Engine(uint entityID, ref float inertia);*/

public void AddForce(Vector2 force)
    {
        AddForce_Physics_Engine(entityId, force);
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void AddForce_Physics_Engine(uint entityId, Vector2 force);

    public void AddTorque(float torque)
    {
        AddTorque_Physics_Engine(entityId, torque);
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void AddTorque_Physics_Engine(uint entityId, float torque);
}