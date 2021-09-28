/* Start Header**********************************************************************************/
/*
@file    Monobehaviour.cs
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    21/08/2021
\brief
This file has the function definition for MonoBehaviour

List of virtual functions to override:
void        Init            ()
void        Update          ()
void        OnEnable        ()
void        OnDisable       ()

Example code: (not yet done)
GetComponent<Transform>.enabled = true;


Limitations:
Doesnt support namespace (class cant be in a namespace)
Doesnt support public enum and string

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/


using System;
//using System.Collections.Generic;
/*using System.Linq;
using System.Text;
using System.Threading.Tasks;*/
using System.Runtime.CompilerServices; //For internal calls

public class MonoBehaviour
{
    //public GameObject gameObject;
    public uint entityId;

    public virtual void OnInit() { }
    public virtual void OnUpdate() { }
    public virtual void OnDestroy() { }
    public virtual void OnCollisionEnter() { }
    public virtual void OnCollisionStay() { }
    public virtual void OnCollisionExit() { }
    public virtual void OnTriggerEnter() { }
    public virtual void OnTriggerStay() { }
    public virtual void OnTriggerExit() { }

    public MonoBehaviour() { }
    public MonoBehaviour(uint id)
    {
        entityId = id;
        Console.WriteLine("Constructor new");
        //gameObject = new GameObject();
        //gameObject.entityId = id;
    }

    public T GetComponent<T>() where T : Component, new()
    {
        if (HasComponent(entityId, typeof(T)))
        {
            T component = new T();
            component.entityId = entityId;
            return component;
        }
        
        else
        {
            throw new NullReferenceException();
        }
    }

    public T GetComponentWithID<T>(uint id) where T : Component, new()
    {
        if (HasComponent(id, typeof(T)))
        {
            T component = new T();
            component.entityId = id;
            return component;
        }

        return default(T);
    }

    public bool HasComponent(uint id, Type type)
    {

        switch (GenericTypeFinder.dictonary[type])
        {
            case genTypes.Transform:
                return HasComponent_Transform_Engine(id);
            case genTypes.Collider:
                return HasComponent_Collider_Engine(id);
            default:
                return false;

        }
    }

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern bool HasComponent_Transform_Engine(uint entityID);
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern bool HasComponent_Collider_Engine(uint entityID);


    public void DestroySelf()
    {
        Destroy_Entity_Engine(entityId);
    }
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void Destroy_Entity_Engine(uint entityID);



    //-----------------------------------------------------------------------------------------------------------------
    //Destroy
    public void Destroy<T>(T type = default)
    {
        Console.WriteLine("Destroy not yet done");
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
    //Enable
    /*
    public void Enable<T>(T type)
    {
        Console.WriteLine("Enable not yet done");
        if (!GenericTypeFinder.dictonary.ContainsKey(typeof(T)))
        {
            //Active_Script_Engine(entityId, true, typeof(T).ToString());
            return;
        }

        switch (GenericTypeFinder.dictonary[typeof(T)])
        {
            case genTypes.Transform:
                //Active_Transform_Engine(entityId, true);
                break;
            case genTypes.Collider:
                //Active_Collider_Engine(entityId, true);
                break;
            default:
                return;

        }
    }
    */



    //-----------------------------------------------------------------------------------------------------------------
    //Disable
    /*
    public void Disable<T>(T type)
    {
        Console.WriteLine("Disable not yet done");
        if (!GenericTypeFinder.dictonary.ContainsKey(typeof(T)))
        {
            //Active_Script_Engine(entityId, false, typeof(T).ToString());
            return;
        }

        switch (GenericTypeFinder.dictonary[typeof(T)])
        {
            case genTypes.Transform:
                //Active_Transform_Engine(entityId, false);
                break;
            case genTypes.Collider:
                //Active_Collider_Engine(entityId, false);
                break;
            default:
                return;

        }
    }
    */
    /*[MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void Active_Transform_Engine(uint entityID, bool active);

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void Active_Collider_Engine(uint entityID, bool active);

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void Active_Script_Engine(uint entityID, bool active, String className);*/


    public void Instantiate(string prefabName, Vec2 position, float angle = 0)
    {
        Instantiate_Prefab(prefabName, position, angle);
    }

    public void Instantiate_Entity(string prefabName)
    {
        Instantiate_Prefab(prefabName, new Vec2(0,0), 0);
    }

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void Instantiate_Prefab(String prefabName, Vec2 position, float angle);

    /*public virtual void OnEnable()
    {
        Console.WriteLine("OnEnable");
    }

    public virtual void OnDisable()
    {
        Console.WriteLine("OnDisable");
    }*/
}

