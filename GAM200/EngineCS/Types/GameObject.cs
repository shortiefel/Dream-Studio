/*
@file    GameObject.cs
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    31/10/2021
\brief
This file has the function definition for GameObject


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

using System.Runtime.CompilerServices; //For internal calls

public class GameObject : IBehaviour
{
    public Transform transform;
    public string name;
    //Creating New GameObject
    public GameObject(bool create = true, uint entity_id = 9999, string _name = null) : base(entity_id)
    {
        name = _name;
        //if (create)
        {
            CreateEntity_Engine(out uint entId, "");
            entityId = entId;
            transform = new Transform(entityId);
            RecordComponent<Transform>(entityId);
            AddComponent<Transform>();

        }
        //else
        //{
        //    entityId = entity_id;
        //    transform = GetComponent<Transform>();
        //}
    }

    //public GameObject(string name) : base(9999)
    //{
    //    CreateEntity_Engine(out uint entId, name);
    //    entityId = entId;
    //    
    //    transform = new Transform(entityId);
    //    RecordComponent<Transform>(entityId);
    //
    //    AddComponent_Transform_Engine(entityId);
    //}
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void CreateEntity_Engine(out uint entityID, string name);
    //--------------------------------------------------------------------

    //Referencing existing GameObject
    private GameObject(uint entId) : base(entId)
    {
        entityId = entId;
        transform = new Transform(entityId);
        RecordComponent<Transform>(entityId);
    }

    public static GameObject RetrieveGameObject(uint entId)
    {
        return new GameObject(entId);
    }


    public GameObject(Prefab _prefab, uint entity_id = 9999) : base(entity_id)
    {
        name = _prefab.name;
        
        entityId = entity_id;
        transform = GetComponent<Transform>();
    }


    public static GameObject Find(string name)
    {
        FindEntity_Engine(out int entityId, name);
        if (entityId < 0)
        {
            Debug.Log("Warning: GameObject with name(" + name + ") cannot be found");
            return null;
        }
        return new GameObject((uint)entityId);
    }
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void FindEntity_Engine(out int entityID, string name);

    
    private enum AddCompState
    {
        Added,
        Found,
        Failed
    }
    //public T AddComponent<T>() where T : IBehaviour, IComponent, new()
    //public T AddComponent<T>() where T : IComponent, new()
    //{
    //    //switch (AddComponentInternal<T>())
    //    //{
    //    //    case AddCompState.Added:
    //    //    case AddCompState.Found:
    //    //        if (GenericTypeFinder.dictonary.ContainsKey(typeof(T)))
    //    //            RecordComponent<T>(entityId);
    //    //        else
    //    //            RecordScript(typeof(T), entityId);
    //    //
    //    //        /*T component = new T();
    //    //        component.entityId = entityId;
    //    //        return component;*/
    //    //        return dictonaryOfTypes[typeof(T)][entityId] as T;
    //    //
    //    //    //case AddCompState.Found:
    //    //    //return dictonaryOfTypes[typeof(T)][entityId] as T;
    //    //
    //    //    case AddCompState.Failed:
    //    //        return null;
    //    //}
    //    //return null;
    //    if (HasComponent<T>(entityId))
    //    {
    //        Debug.Log("Warning: Entity already have (" + typeof(T).ToString() + ")");
    //        return dictonaryOfTypes[typeof(T)][entityId] as T;
    //    }
    //
    //    if (!GenericTypeFinder.dictonary.ContainsKey(typeof(T)))
    //    {
    //        bool bl = AddComponent_Scripts_Engine(entityId, typeof(T).ToString());
    //        RecordScript(typeof(T), entityId);
    //        return dictonaryOfTypes[typeof(T)][entityId] as T;
    //    }
    //
    //    if (AddComponentInternalTem<T>(entityId))
    //    {
    //        RecordComponent<T>(entityId);
    //        return dictonaryOfTypes[typeof(T)][entityId] as T;
    //    }
    //    
    //    return null;
    //}
    //[MethodImplAttribute(MethodImplOptions.InternalCall)]
    //internal static extern bool AddComponent_Scripts_Engine(uint entityId, string name);

    //private AddCompState AddComponentInternal<T>() where T : IComponent, new()
    //{
    //    if (!GenericTypeFinder.dictonary.ContainsKey(typeof(T)))
    //    {
    //        bool bl = AddComponent_Scripts_Engine(entityId, typeof(T).ToString());
    //        if (!bl)
    //        {
    //            Debug.Log("Script already exist!");
    //            return AddCompState.Found;
    //        }
    //        return AddCompState.Added;
    //    }
    //
    //    Debug.Log("Coming in here");
    //    if (AddComponentInternalTem<T>(entityId)) return AddCompState.Added;
    //    return AddCompState.Failed;
    //    //return AddCompState.Failed;
    //    //switch (GenericTypeFinder.dictonary[typeof(T)])
    //    //{
    //    //    case genTypes.Transform:
    //    //        bool bl = AddComponent_Transform_Engine(entityId);
    //    //        if (!bl) {
    //    //            //Debug.Log("Transform already exist!"); 
    //    //            return AddCompState.Found;
    //    //        }
    //    //        return AddCompState.Added;
    //    //
    //    //    case genTypes.Collider:
    //    //        bool b2 = AddComponent_Collider_Engine(entityId);
    //    //        if (!b2) {
    //    //            //Debug.Log("Collider already exist!");
    //    //            return AddCompState.Found;
    //    //        }
    //    //        return AddCompState.Added;
    //    //
    //    //    case genTypes.Camera:
    //    //        bool b3 = AddComponent_Camera_Engine(entityId);
    //    //        if (!b3) {
    //    //            //Debug.Log("Camera already exist!");
    //    //            return AddCompState.Found;
    //    //        }
    //    //        return AddCompState.Added;
    //    //
    //    //    default:
    //    //        Debug.Log("Cant add this type in!");
    //    //        return AddCompState.Failed;
    //    //}
    //}
    //[MethodImplAttribute(MethodImplOptions.InternalCall)]
    //internal static extern bool AddComponent_Scripts_Engine(uint entityId, string name);
    //[MethodImplAttribute(MethodImplOptions.InternalCall)]
    //internal static extern bool AddComponent_Transform_Engine(uint entityId);
    //[MethodImplAttribute(MethodImplOptions.InternalCall)]
    //internal static extern bool AddComponent_Collider_Engine(uint entityId);
    //[MethodImplAttribute(MethodImplOptions.InternalCall)]
    //internal static extern bool AddComponent_Camera_Engine(uint entityId);



    public void SetActive(bool state)
    {
        SetActive_GameObject_Engine(entityId, state);
    }
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void SetActive_GameObject_Engine(uint entityId, bool state);
}