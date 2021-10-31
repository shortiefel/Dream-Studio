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
using System.Runtime.CompilerServices; //For internal calls

public class MonoBehaviour : IComponent
{
    //public GameObject gameObject;
    public uint entityId { get; set; }

    public virtual void Start() { }
    public virtual void Update() { }
    public virtual void OnDestroy() { }
    public virtual void OnCollisionEnter() { }
    public virtual void OnCollisionStay() { }
    public virtual void OnCollisionExit() { }
    public virtual void OnTriggerEnter() { }
    public virtual void OnTriggerStay() { }
    public virtual void OnTriggerExit() { }
    public virtual void OnMouseEnter() { }
    public virtual void OnMouseClick() { }
    public virtual void OnMouseOver() { }
    public virtual void OnMouseExit() { }

    public MonoBehaviour() { }
    public MonoBehaviour(uint id)
    {
        entityId = id;
    }

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
    public void Enable<T>(T type)
    {
        Console.WriteLine("Enable not yet done");
        if (!GenericTypeFinder.dictonary.ContainsKey(typeof(T)))
        {
            Active_Script_Engine(entityId, true, typeof(T).ToString());
            return;
        }

        switch (GenericTypeFinder.dictonary[typeof(T)])
        {
            case genTypes.Transform:
                Active_Transform_Engine(entityId, true);
                break;
            case genTypes.Collider:
                Active_Collider_Engine(entityId, true);
                break;
            default:
                return;

        }
    }




    //-----------------------------------------------------------------------------------------------------------------
    //Disable
    public void Disable<T>(T type)
    {
        Console.WriteLine("Disable not yet done");
        if (!GenericTypeFinder.dictonary.ContainsKey(typeof(T)))
        {
            Active_Script_Engine(entityId, false, typeof(T).ToString());
            return;
        }

        switch (GenericTypeFinder.dictonary[typeof(T)])
        {
            case genTypes.Transform:
                Active_Transform_Engine(entityId, false);
                break;
            case genTypes.Collider:
                Active_Collider_Engine(entityId, false);
                break;
            default:
                return;

        }
    }
    
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void Active_Transform_Engine(uint entityID, bool active);

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void Active_Collider_Engine(uint entityID, bool active);

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void Active_Script_Engine(uint entityID, bool active, String className);


    //-----------------------------------------------------------------------------------------------------------------
    //Instantiate
    public void Instantiate(string prefabName, Transform transform)
    {
        Instantiate_Prefab_Transform_Engine(prefabName, transform.entityId);
    }
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void Instantiate_Prefab_Transform_Engine(String prefabName, uint entityID);

    public void Instantiate(string prefabName, Vector2 position, float angle = 0)
    {
        Instantiate_Prefab_Engine(prefabName, position, angle);
    }

    public void Instantiate(string prefabName)
    {
        Instantiate_Prefab_Engine(prefabName, new Vector2(0,0), 0);
    }

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void Instantiate_Prefab_Engine(String prefabName, Vector2 position, float angle);

    /*public virtual void OnEnable()
    {
        Console.WriteLine("OnEnable");
    }

    public virtual void OnDisable()
    {
        Console.WriteLine("OnDisable");
    }*/
}

