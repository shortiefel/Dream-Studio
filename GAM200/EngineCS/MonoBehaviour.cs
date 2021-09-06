/* Start Header**********************************************************************************/
/*
@file    Monobehaviour.cs
@author  Ow Jian Wen	jianwen123321@hotmail.com
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
    uint entityId;

    public virtual void Init() {}
    public virtual void Update() {}
    public virtual void Destroy() {}
    public virtual void OnCollisionEnter() {}
    public virtual void OnCollisionStay() {}
    public virtual void OnCollisionExit() {}
    public virtual void OnTriggerEnter() {}
    public virtual void OnTriggerStay() {}
    public virtual void OnTriggerExit() {}

    public MonoBehaviour() { }
    public MonoBehaviour (uint id)
    {
        entityId = id;
        Console.WriteLine("Constructor ");
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

        return default(T);
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
            default:
                return false;

        }
    }

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern bool HasComponent_Transform_Engine(uint entityID);

    





    /*public virtual void OnEnable()
    {
        Console.WriteLine("OnEnable");
    }

    public virtual void OnDisable()
    {
        Console.WriteLine("OnDisable");
    }*/











    /*public Transform GetTransform()
    {
        Console.WriteLine("Getting values");
        GetTransform_Native(0, out Transform result);
        return result;
    }
    public void SetTransform(Transform trans)
    {
        Console.WriteLine("Setting values");
        SetTransform_Native(0, ref trans);
    }

    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void GetTransform_Native(uint entityID, out Transform outTransform);
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void SetTransform_Native(uint entityID, ref Transform inTransform);*/
}

