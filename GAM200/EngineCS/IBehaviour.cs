/* Start Header**********************************************************************************/
/*
@file    IBehaviour.cs
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    03/11/2021
\brief
This file has the function definition for IBehaviour


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

using System.Runtime.CompilerServices; //For internal calls
using System;

public class IBehaviour : IComponent
{
    public uint entityId { get; set; }
    public IBehaviour() { }
    public IBehaviour(uint id)
    {
        entityId = id;
    }
    //-----------------------------------------------------------------------------------------------------------------
    //Component
    public T GetComponent<T>() where T : class, IComponent, new()
    {
        if (HasComponent<T>(entityId))
        {
            T component = new T();
            component.entityId = entityId;
            return component;
        }

        return null;
    }

    /*public T GetComponentWithID<T>(uint id) where T : class, IComponent, new()
    {
        if (HasComponent<T>(id))
        {
            T component = new T();
            component.entityId = id;
            return component;
        }

        return null;
    }*/

    public bool HasComponent<T>(uint id)
    {
        if (!GenericTypeFinder.dictonary.ContainsKey(typeof(T)))
        {
            return HasComponent_Scripts_Engine(id, typeof(T).ToString());
        }

        switch (GenericTypeFinder.dictonary[typeof(T)])
        {
            case genTypes.Transform:
                return HasComponent_Transform_Engine(id);
            case genTypes.Collider:
                return HasComponent_Collider_Engine(id);
            case genTypes.Camera:
                return HasComponent_Camera_Engine(id);
            default:
                return false;

        }
    }
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern bool HasComponent_Scripts_Engine(uint entityId, string name);

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern bool HasComponent_Transform_Engine(uint entityId);
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern bool HasComponent_Collider_Engine(uint entityId);
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern bool HasComponent_Camera_Engine(uint entityId);
    //-----------------------------------------------------------------------------------------------------------------
    //Destroy
    public void Destroy(uint id)
    {
        Destroy_Entity_Engine(id);
    }
    public void Destroy(GameObject go)
    {
        Destroy_Entity_Engine(go.entityId);
    }
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void Destroy_Entity_Engine(uint entityID);

    public void Destroy<T>(T type = default)
    {
        //Console.WriteLine("Destroy not yet done");
        if (!GenericTypeFinder.dictonary.ContainsKey(typeof(T)))
        {
            Destroy_Script_Engine(entityId, typeof(T).ToString());
            return;
        }

        switch (GenericTypeFinder.dictonary[typeof(T)])
        {
            case genTypes.Transform:
                Destroy_Transform_Engine(entityId);
                break;
            case genTypes.Collider:
                Destroy_Collider_Engine(entityId);
                break;
            default:
                return;

        }
    }
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void Destroy_Transform_Engine(uint entityID);

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void Destroy_Collider_Engine(uint entityID);

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void Destroy_Script_Engine(uint entityID, String className);
    //-----------------------------------------------------------------------------------------------------------------
}

