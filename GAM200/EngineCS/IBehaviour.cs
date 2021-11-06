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
using System.Collections.Generic; //Dictionary


/*public class GenericDictionary
{
    //private Dictionary<string, object> _dict = new Dictionary<string, object>();
    private Dictionary<Type, Dictionary<uint, dynamic>> dictonaryOfTypes = new Dictionary<Type, Dictionary<uint, dynamic>>();

    public void Add<T>(uint key, T value) where T : class
    {
        dictonaryOfTypes[typeof(T)].Add(key, value);
    }

    public T GetValue<T>(uint key) where T : class
    {
        return dictonaryOfTypes[typeof(T)][key] as T;
    }
}*/

public class IBehaviour : IComponent
{
    protected static Dictionary<Type, Dictionary<uint, dynamic>> dictonaryOfTypes = new Dictionary<Type, Dictionary<uint, dynamic>>();
    //private static GenericDictionary dictonaryOfTypes;

    public uint entityId { get; set; }
    public IBehaviour() {
        //Console.WriteLine("111: " + this.GetType().Name);
    }
    public IBehaviour(uint id)
    {
        entityId = id;
        //Console.WriteLine("2222: " + this.GetType().Name);
    }
    //-----------------------------------------------------------------------------------------------------------------
    //Component

    protected void RecordScript(Type type, uint entityId) 
    {
        //Console.WriteLine(type.Name);
        if (!dictonaryOfTypes.ContainsKey(type))
        {
            dictonaryOfTypes.Add(type, new Dictionary<uint, dynamic>());
        }

        if (!dictonaryOfTypes[type].ContainsKey(entityId))
        {
            dictonaryOfTypes[type].Add(entityId, this);

            //Console.WriteLine("True " +type.Name);
        }
    }

    protected void RecordComponent<T>(uint entityId) where T : class, IComponent, new()
    {
        //Console.WriteLine("Custom typeeeeeeeeeeeeeeeeeeeeeeeeee ");
        Type type = typeof(T);
        if (!dictonaryOfTypes.ContainsKey(type))
        {
            dictonaryOfTypes.Add(type, new Dictionary<uint, dynamic>());
        }

        if (!dictonaryOfTypes[type].ContainsKey(entityId))
        {
            T comp = new T();
            comp.entityId = entityId;
            dictonaryOfTypes[type].Add(entityId, comp);
            //Console.WriteLine("Custom typeeeeeeeeeeeeeeeeeeeeeeeeee addddddddddddddddddddd");
        }
    }

    public T GetComponent<T>() where T : class, IComponent, new()
    {
        if (HasComponent<T>(entityId))
        {
            //Debug.Log(typeof(T));
            //Console.WriteLine("First " + typeof(T));
            if(GenericTypeFinder.dictonary.ContainsKey(typeof(T)))
                RecordComponent<T>(entityId);
            else
                RecordScript(typeof(T), entityId);
            //Console.WriteLine("Got " + typeof(T));

            return dictonaryOfTypes[typeof(T)][entityId] as T;
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
            case genTypes.Texture:
                return HasComponent_Texture_Engine(id);
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
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern bool HasComponent_Texture_Engine(uint entityId);
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

