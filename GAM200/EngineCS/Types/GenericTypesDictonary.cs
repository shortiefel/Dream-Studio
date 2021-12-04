/* Start Header**********************************************************************************/
/*
@file    GenericTypesDictonary.cs
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    21/08/2021
\brief
This file has the function definition for GenericTypesDictonary


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

using System;
using System.Collections.Generic;

public static class GenericTypeFinder
{
    public static Dictionary<Type, genTypes> dictonary = new Dictionary<Type, genTypes>(){
        { typeof(Transform), genTypes.Transform },
        { typeof(Collider), genTypes.Collider },
        { typeof(Camera), genTypes.Camera },
        { typeof(Rigidbody2D), genTypes.Rigidbody2D },
        { typeof(Texture), genTypes.Texture },
        { typeof(Text), genTypes.Text },
        { typeof(AudioSource), genTypes.Audio },
        { typeof(UI), genTypes.UI },
        { typeof(Animation), genTypes.Animation }
    };
}

public enum genTypes
{
    Transform = 0,
    Collider,
    Camera,
    Rigidbody2D,
    Texture,
    Text,
    Audio,
    UI,
    Animation
}

