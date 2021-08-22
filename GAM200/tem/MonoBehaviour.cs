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

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/


using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.CompilerServices; //For internal calls


/*public class Transform
{


    [MethodImpl(MethodImplOptions.InternalCall)]
    public extern void GetTransform_Native(int entityID, out Transform outTransform);
}*/

public struct Vec2
{
    public float x, y;
}

public class Transform
{
    public Vec2 pos, scale;
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



//public class TransformComponent {




//}

public class MonoBehaviour
{
    GameObject gameObject;

    public virtual void Init() {}
    public virtual void Update() {}
    public virtual void Destroy() {}

    public void Constructor(int id)
    {
        //entityId = id;
        //Transform trans = new Transform();
        //trans.GetTransform_Native(entityId, out trans);

        //gameObject = new GameObject();

        //Transform trans = new Transform();

        //gameObject.transform = trans;
    }



    public virtual void OnEnable()
    {
        Console.WriteLine("OnEnable");
    }

    public virtual void OnDisable()
    {
        Console.WriteLine("OnDisable");
    }

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

