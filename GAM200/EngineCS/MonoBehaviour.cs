﻿/* Start Header**********************************************************************************/
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

//Only inherited by Scripts
public class MonoBehaviour : IBehaviour
{
    public GameObject gameObject;
    public Transform transform;
    //public uint entityId { get; set; }

    public virtual void Awake() { }
    public virtual void Start() { }
    public virtual void Update() { }
    public virtual void FixedUpdate() { }
    public virtual void OnEnable() { }
    public virtual void OnDisable() { }
    public virtual void OnDestroy() { }
    public virtual void OnCollisionEnter(uint entId) { }
    public virtual void OnCollisionStay(uint entId) { }
    public virtual void OnCollisionExit(uint entId) { }
    public virtual void OnTriggerEnter(uint entId) { }
    public virtual void OnTriggerStay(uint entId) { }
    public virtual void OnTriggerExit(uint entId) { }
    public virtual void OnMouseEnter() { }
    //public virtual void OnMouseClick() { }
    public virtual void OnMouseOver() { }
    public virtual void OnMouseExit() { }

    public MonoBehaviour() {  }
    public MonoBehaviour(uint id) : base(id)
    {
        entityId = id;
        //if (GenericTypeFinder.dictonary.ContainsKey(this.GetType()))
        //{
        //    switch (GenericTypeFinder.dictonary[this.GetType()])
        //    {
        //        case genTypes.Transform:
        //            RecordComponent<Transform>(entityId);
        //            break;
        //        case genTypes.Collider:
        //            RecordComponent<Collider>(entityId);
        //            break;
        //        case genTypes.Camera:
        //            RecordComponent<Camera>(entityId);
        //            break;
        //        case genTypes.Texture:
        //            RecordComponent<Texture>(entityId);
        //            break;
        //        case genTypes.Rigidbody2D:
        //            RecordComponent<Rigidbody2D>(entityId);
        //            break;
        //        case genTypes.Text:
        //            RecordComponent<Text>(entityId);
        //            break;
        //        case genTypes.Audio:
        //            RecordComponent<AudioSource>(entityId);
        //            break;
        //        case genTypes.UI:
        //            RecordComponent<UI>(entityId);
        //            break;
        //        case genTypes.Animation:
        //            RecordComponent<Animation>(entityId);
        //            break;
        //        default:
        //            Console.WriteLine("Type cant be recorded yet");
        //            break;
        //
        //    }
        //
        //}
        //else
        //{
        //    RecordScript(this.GetType(), entityId);
        //    //Debug.Log("REcording here-------------------------------------------------------------------------------------");
        //}

        RecordScript(this.GetType(), entityId);
        gameObject = GameObject.RetrieveGameObject(id);
        gameObject.transform = transform = GetComponent<Transform>();
    }

    //public static void SetHighscore(int value, string name)
    //{
    //    SetHighscore_Engine(value, name);
    //}
    //[MethodImpl(MethodImplOptions.InternalCall)]
    //internal static extern void SetHighscore_Engine(int value, string name);
    //
    //public static int GetHighscore(string name)
    //{
    //    GetHighscore_Engine(out int value, name);
    //    return value;
    //}
    //[MethodImpl(MethodImplOptions.InternalCall)]
    //internal static extern void GetHighscore_Engine(out int value, string name);


    public static void SetSavedData(int value, string name)
    {
        SetSavedData_Engine(value, name);
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void SetSavedData_Engine(int value, string name);

    public static int GetSavedData(string name)
    {
        GetSavedData_Engine(out int value, name);
        return value;
    }

    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void GetSavedData_Engine(out int value, string name);

    /*public T GetComponent<T>() where T : class, IComponent, new()
    {
        if (HasComponent<T>(entityId))
        {
            T component = new T();
            component.entityId = entityId;
            return component;
        }

        return null;
    }

    *//*public T GetComponentWithID<T>(uint id) where T : class, IComponent, new()
    {
        if (HasComponent<T>(id))
        {
            T component = new T();
            component.entityId = id;
            return component;
        }

        return null;
    }*//*

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
    internal static extern bool HasComponent_Camera_Engine(uint entityId);*/
    //-----------------------------------------------------------------------------------------------------------------
    //Destroy
    /*public void Destroy(uint id)
    {
        Destroy_Entity_Engine(id);
    }
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void Destroy_Entity_Engine(uint entityID);*/
    /*public void Destroy<T>(T type = default)
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
    internal static extern void Destroy_Script_Engine(uint entityID, String className);*/

    //-----------------------------------------------------------------------------------------------------------------
    //Enable
    public void Enable<T>(T type) where T : IComponent
    {
        if (type == null)
        {
            Console.WriteLine("Enable Is actually nulll------------------------------------------------------------------------------------------------------------------------------------------------------");
            return;
        }
        if (!GenericTypeFinder.dictonary.ContainsKey(typeof(T)))
        {
            Active_Script_Engine(type.entityId, true, typeof(T).ToString());
            return;
        }

        switch (GenericTypeFinder.dictonary[typeof(T)])
        {
            case genTypes.Transform:
                Active_Transform_Engine(type.entityId, true);
                break;
            case genTypes.Collider:
                Active_Collider_Engine(type.entityId, true);
                break;
            case genTypes.Light:
                Active_Light_Engine(type.entityId, true);
                break;
            case genTypes.Text:
                Active_Text_Engine(type.entityId, true);
                break;
            default:
                Console.WriteLine("Enable not yet done");
                return;

        }
    }




    //-----------------------------------------------------------------------------------------------------------------
    //Disable
    public void Disable<T>(T type) where T : IComponent
    {
        if (type == null)
        {
            Console.WriteLine("disable Is actually nulll------------------------------------------------------------------------------------------------------------------------------------------------------");
            return;
        }
        if (!GenericTypeFinder.dictonary.ContainsKey(typeof(T)))
        {
            Active_Script_Engine(type.entityId, false, typeof(T).ToString());
            return;
        }

        switch (GenericTypeFinder.dictonary[typeof(T)])
        {
            case genTypes.Transform:
                Active_Transform_Engine(type.entityId, false);
                break;
            case genTypes.Collider:
                Active_Collider_Engine(type.entityId, false);
                break;
            case genTypes.Light:
                Active_Light_Engine(type.entityId, false);
                break;
            case genTypes.Text:
                Active_Text_Engine(type.entityId, false);
                break;
            default:
                Console.WriteLine("Disable not yet done");
                return;

        }
    }

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void Active_Transform_Engine(uint entityID, bool active);

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void Active_Collider_Engine(uint entityID, bool active);

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void Active_Light_Engine(uint entityID, bool active);

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void Active_Text_Engine(uint entityID, bool active);

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void Active_Script_Engine(uint entityID, bool active, String className);

    


    //-----------------------------------------------------------------------------------------------------------------
    //Instantiate
    public GameObject Instantiate(Prefab _prefab, Transform transform = null)
    {
        int transformId = -1;
        if (transform != null) transformId = (int)transform.entityId;
        Instantiate_Prefab_Transform_Engine(_prefab.name, transformId, out uint newId);
        return new GameObject(_prefab, newId);
        //return new GameObject(false, newId, _prefab.name);
    }

    public GameObject Instantiate(GameObject _go, Transform transform = null)
    {
        int transformId = -1;
        if (transform != null) transformId = (int)transform.entityId;
        Instantiate_Prefab_Transform_Engine(_go.name, transformId, out uint newId);
        return new GameObject(new Prefab(_go.name), newId);
        //return new GameObject(false, newId, _go.name);
    }
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void Instantiate_Prefab_Transform_Engine(String prefabName, int entityID, out uint id);


    public GameObject Instantiate(Prefab _prefab, Vector3 pos, int layer = 2)
    {
        Instantiate_Prefab_Position_Engine(_prefab.name, pos, layer, out uint newId);
        return new GameObject(_prefab, newId);
        //return new GameObject(false, newId, _prefab.name);
    }
    public GameObject Instantiate(GameObject _go, Vector3 pos, int layer = 2, float angle = 0)
    {
        //Instantiate_Prefab_Position_Engine(_go.name, pos, layer, out uint newId);
        Instantiate_Prefab_Engine(_go.name, pos, angle, new Vector2(1,1), layer, out uint newId);
        return new GameObject(new Prefab(_go.name), newId);
        //return new GameObject(false, newId, _go.name);
    }
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void Instantiate_Prefab_Position_Engine(String prefabName, Vector3 pos, int layer, out uint newId);



    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void Instantiate_Prefab_Engine(String prefabName, Vector3 pos, float angle, Vector2 scale, int layer, out uint newId);

    

    /*public virtual void OnEnable()
    {
        Console.WriteLine("OnEnable");
    }

    public virtual void OnDisable()
    {
        Console.WriteLine("OnDisable");
    }*/
}

