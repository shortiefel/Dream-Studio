﻿/* Start Header**********************************************************************************/
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

    //public uint entityId { get; set; }
    public IBehaviour()
    {
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

        //else
        //{
        //    Debug.Log("Warning: Entity already has script (" + type.Name + ")");
        //}
    }

    protected void RecordComponent<T>(uint entityId) where T : IComponent, new()
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
            //Console.WriteLine("Adding components: " + type.Name + " size: " + dictonaryOfTypes[type].Count);
        }

        //else
        //{
        //    Debug.Log("Warning: Entity already has a " + typeof(T).ToString() + " component!");
        //}
    }


    public T AddComponent<T>() where T : IComponent, new()
    {
        if (HasComponent<T>(entityId))
        {
            Debug.Log("Warning: Entity already have (" + typeof(T).ToString() + ")");
            return dictonaryOfTypes[typeof(T)][entityId] as T;
        }

        if (!GenericTypeFinder.dictonary.ContainsKey(typeof(T)))
        {
            bool bl = AddComponent_Scripts_Engine(entityId, typeof(T).ToString());
            RecordScript(typeof(T), entityId);
            return dictonaryOfTypes[typeof(T)][entityId] as T;
        }

        if (AddComponentInternal<T>(entityId))
        {
            RecordComponent<T>(entityId);
            return dictonaryOfTypes[typeof(T)][entityId] as T;
        }

        return null;
    }
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern bool AddComponent_Scripts_Engine(uint entityId, string name);

    public T GetComponent<T>() where T : IComponent, new()
    {
        if (HasComponent<T>(entityId))
        {
            //Debug.Log(typeof(T));
            //Console.WriteLine("First " + typeof(T));
            if (GenericTypeFinder.dictonary.ContainsKey(typeof(T)))
                RecordComponent<T>(entityId);
            else
                RecordScript(typeof(T), entityId);
            //Console.WriteLine("Got " + typeof(T));

            return dictonaryOfTypes[typeof(T)][entityId] as T;
        }

        return null;
    }

    public T GetComponent<T>(uint id) where T : IComponent, new()
    {
        if (HasComponent<T>(id))
        {
            //Debug.Log(typeof(T));
            //Console.WriteLine("First " + typeof(T));
            if (GenericTypeFinder.dictonary.ContainsKey(typeof(T)))
                RecordComponent<T>(id);
            else
                RecordScript(typeof(T), id);
            //Console.WriteLine("Got " + typeof(T));

            return dictonaryOfTypes[typeof(T)][id] as T;
        }

        return null;
    }

    //public T GetComponentWithID<T>(uint id) where T : IComponent, new()
    //{
    //    if (HasComponent<T>(id))
    //    {
    //        //Debug.Log(typeof(T));
    //        //Console.WriteLine("First " + typeof(T));
    //        if (GenericTypeFinder.dictonary.ContainsKey(typeof(T)))
    //            RecordComponent<T>(id);
    //        else
    //            RecordScript(typeof(T), id);
    //        //Console.WriteLine("Got " + typeof(T));
    //
    //        return dictonaryOfTypes[typeof(T)][id] as T;
    //    }
    //
    //    return null;
    //}


    protected bool HasComponent<T>(uint id) where T : IComponent, new()
    {
        if (!GenericTypeFinder.dictonary.ContainsKey(typeof(T)))
        {
            return HasComponent_Scripts_Engine(id, typeof(T).ToString());
        }

        return HasComponentInternal<T>(id);

        //switch (GenericTypeFinder.dictonary[typeof(T)])
        //{
        //    case genTypes.Transform:
        //        return HasComponent_Transform_Engine(id);
        //    case genTypes.Collider:
        //        return HasComponent_Collider_Engine(id);
        //    case genTypes.Camera:
        //        return HasComponent_Camera_Engine(id);
        //    case genTypes.Rigidbody2D:
        //        return HasComponent_Rigidbody_Engine(id);
        //    case genTypes.Texture:
        //        return HasComponent_Texture_Engine(id);
        //    case genTypes.Text:
        //        return HasComponent_Font_Engine(id);
        //    case genTypes.Audio:
        //        return HasComponent_Sound_Engine(id);
        //    case genTypes.UI:
        //        return HasComponent_UI_Engine(id);
        //    case genTypes.Animation:
        //        return HasComponent_Texture_Engine(id);
        //    case genTypes.Waypoint:
        //        return HasComponent_Waypoint_Engine(id);
        //    default:
        //        Console.WriteLine("Type cant be found yet");
        //        return false;
        //}
    }
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern bool HasComponent_Scripts_Engine(uint entityId, string name);

    //[MethodImplAttribute(MethodImplOptions.InternalCall)]
    //internal static extern bool HasComponent_Transform_Engine(uint entityId);
    //[MethodImplAttribute(MethodImplOptions.InternalCall)]
    //internal static extern bool HasComponent_Collider_Engine(uint entityId);
    //[MethodImplAttribute(MethodImplOptions.InternalCall)]
    //internal static extern bool HasComponent_Camera_Engine(uint entityId);
    //[MethodImplAttribute(MethodImplOptions.InternalCall)]
    //internal static extern bool HasComponent_Rigidbody_Engine(uint entityId);
    //[MethodImplAttribute(MethodImplOptions.InternalCall)]
    //internal static extern bool HasComponent_Texture_Engine(uint entityId);
    //[MethodImplAttribute(MethodImplOptions.InternalCall)]
    //internal static extern bool HasComponent_Font_Engine(uint entityId);
    //[MethodImplAttribute(MethodImplOptions.InternalCall)]
    //internal static extern bool HasComponent_Sound_Engine(uint entityId);
    //[MethodImplAttribute(MethodImplOptions.InternalCall)]
    //internal static extern bool HasComponent_UI_Engine(uint entityId);
    //[MethodImplAttribute(MethodImplOptions.InternalCall)]
    //internal static extern bool HasComponent_Waypoint_Engine(uint entityId);



    protected bool AddComponentInternal<T>(uint id) where T : IComponent, new()
    {
        return AddComponent_Engine(id, typeof(T));
    }

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern bool AddComponent_Engine(uint entityId, Type type);

    protected bool HasComponentInternal<T>(uint id) where T : IComponent, new()
    {
        return HasComponent_Engine(id, typeof(T));
    }

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern bool HasComponent_Engine(uint entityId, Type type);

    //-----------------------------------------------------------------------------------------------------------------
    //Destroy
    public void Destroy(uint id)
    {
        foreach(var i in dictonaryOfTypes)
        {
            if (i.Value.ContainsKey(id)) i.Value.Remove(id);
        }
        Destroy_Entity_Engine(id);
    }

    private void Remove_Types(uint entityId)
    {
        foreach (KeyValuePair<Type, Dictionary<uint, dynamic>> entry in dictonaryOfTypes)
        {
            if (entry.Value.ContainsKey(entityId))
            {
                entry.Value.Remove(entityId);
            }
        }
    }

    public void Destroy(GameObject go)
    {
        Remove_Types(go.entityId);
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
                Console.WriteLine("Type cant be destroy yet");
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

