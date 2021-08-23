﻿/* Start Header**********************************************************************************/
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


/*public class Transform
{


    [MethodImpl(MethodImplOptions.InternalCall)]
    public extern void GetTransform_Native(int entityID, out Transform outTransform);
}*/

public struct Vec2
{
    public float x, y;

    public Vec2(float n1, float n2)
    {
        x = n1;
        y = n2;
    }
}

public struct Transform
{
    public Vec2 position, scale;

    public override string ToString()
    {
        return "Pos: " + position.x + " " + position.y + " scale: " + scale.x + " " + scale.y + "\n";
    }

    /*public void Move(Vec2 speed)
    {

    }*/

    public Transform (Vec2 p, Vec2 s)
    {
        position = p;
        scale = s;
    }
}

public class GameObject
{
    public int entityId;

    public Transform transform
    {
        get
        {
            Console.WriteLine("Getting values");
            GetTransform_Native(entityId, out Transform result);
            return result;
        }   // get method
        set {
            Console.WriteLine("Setting values");
            SetTransform_Native(entityId, ref value); 
        }  // set method
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void GetTransform_Native(int entityID, out Transform outTransform);
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void SetTransform_Native(int entityID, ref Transform inTransform);
}

public class MonoBehaviour
{
    public GameObject gameObject;

    public virtual void Init() {}
    public virtual void Update() {}
    public virtual void Destroy() {}

    public void Constructor(int id)
    {
        //entityId = id;

        gameObject = new GameObject();
        gameObject.entityId = id;
    }



    public virtual void OnEnable()
    {
        Console.WriteLine("OnEnable");
    }

    public virtual void OnDisable()
    {
        Console.WriteLine("OnDisable");
    }

    public T GetComponent<T>() where T : new()
    {
        if (HasComponent(gameObject.entityId, typeof(T)))
        {
            T component = new T();
            return component;
        }

        return default(T);
    }

    public bool HasComponent(int id, Type type)
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
    internal static extern bool HasComponent_Transform_Engine(int entityID);

    /* public Transform GetComponent()
     {
         Transform trans = new Transform();
         //GetComponentInternalCall(entityId, ref trans);
         return trans;
     }

     [MethodImplAttribute(MethodImplOptions.InternalCall)]
     extern public Transform GetComponentInternalCall(int entityId);*/





    /*public ref T GetComponent<T>()
    {
        return ref GetComponentInternalCall<T>(entityId);
    }

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    extern public ref T GetComponentInternalCall<T>(int entityId);*/



    /*public ref T GetComponent<T>()
    {
        return ref GetComponentInternalCall<T>(entityId);
    }

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    extern public ref T GetComponentInternalCall<T>(int entityId);*/
}

