using System;
using System.Collections.Generic;

public static class GenericTypeFinder
{
    public static Dictionary<Type, genTypes> dictonary = new Dictionary<Type, genTypes>(){
        { typeof(Transform), genTypes.Transform },
        { typeof(Collider), genTypes.Collider }
    };
}

public enum genTypes
{
    Transform = 0,
    Collider,
    RigidBody
}

