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

using System; //Convert.ChangeType
using System.Runtime.CompilerServices; //For internal calls

public class GameObject : MonoBehaviour
{
    public GameObject()
    {
        CreateEntity_Engine(out uint entId, "");
        entityId = entId;
    }

    public GameObject(string name)
    {
        CreateEntity_Engine(out uint entId, name);
        entityId = entId;
    }
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void CreateEntity_Engine(out uint entityID, string name);

    public T AddComponent<T>() where T : class, IComponent, new()
    {
        switch (GenericTypeFinder.dictonary[typeof(T)])
        {
            case genTypes.Transform:
                return (T)Convert.ChangeType(new Transform(entityId), typeof(T));
            case genTypes.Collider:
                return (T)Convert.ChangeType(new Collider(entityId), typeof(T));
            case genTypes.Camera:
                return (T)Convert.ChangeType(new Camera(entityId), typeof(T));
            default:
                return null;

        }
    }
}

/*
 * GameObject structure = new GameObject(type.ToString());
structure.transform.SetParent(transform);
structure.transform.localPosition = new Vec2(position.x, position.y);
var structureModel = structure.AddComponent<StructureModel>();
structureModel.CreateModel(structurePrefab);
return structureModel;
*/

