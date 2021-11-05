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
    //Creating New GameObject
    public GameObject(bool create = true, uint entity_id = 0) : base(9999)
    {
        if (create)
        {
            CreateEntity_Engine(out uint entId, "");
            entityId = entId;
            transform = new Transform(entityId);
            AddComponent_Transform_Engine(entityId);
        }
        else
        {
            entityId = entity_id;
            transform = GetComponent<Transform>();
        }
    }

    public GameObject(string name) : base(9999)
    {
        CreateEntity_Engine(out uint entId, name);
        entityId = entId;
        
        transform = new Transform(entityId);
        AddComponent_Transform_Engine(entityId);
    }
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void CreateEntity_Engine(out uint entityID, string name);

    //Referencing existing GameObject
    private GameObject(uint entId) : base(entId)
    {
        entityId = entId;
        transform = new Transform(entityId);
    }

    public static GameObject RetrieveGameObject(uint entId)
    {
        return new GameObject(entId);
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

    
    public T AddComponent<T>() where T : IBehaviour, IComponent, new()
    {
        if (AddComponentInternal<T>())
        {
            T component = new T();
            component.entityId = entityId;
            return component;
        }
        return null;
    }

    private bool AddComponentInternal<T>() where T : class, IComponent, new()
    {
        if (!GenericTypeFinder.dictonary.ContainsKey(typeof(T)))
        {
            bool bl = AddComponent_Scripts_Engine(entityId, typeof(T).ToString());
            if (!bl) Debug.Log("Script already exist!");
            return bl;
        }
        switch (GenericTypeFinder.dictonary[typeof(T)])
        {
            case genTypes.Transform:
                bool bl = AddComponent_Transform_Engine(entityId);
                if (!bl) Debug.Log("Transform already exist!");
                return bl;

            case genTypes.Collider:
                bool b2 = AddComponent_Collider_Engine(entityId);
                if (!b2) Debug.Log("Collider already exist!");
                return b2;

            case genTypes.Camera:
                bool b3 = AddComponent_Camera_Engine(entityId);
                if (!b3) Debug.Log("Camera already exist!");
                return b3;

            default:
                return false;
        }
    }
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern bool AddComponent_Scripts_Engine(uint entityId, string name);
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern bool AddComponent_Transform_Engine(uint entityId);
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern bool AddComponent_Collider_Engine(uint entityId);
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern bool AddComponent_Camera_Engine(uint entityId);
}