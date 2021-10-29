/* Start Header**********************************************************************************/
/*
@file    Physics.cs
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    15/10/2021
\brief
This file has the function definition for Physics


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

using System.Runtime.CompilerServices; //For internal calls
using System;

public class Physics
{
    //Leave distance parameter blank to have "infinite" length
    public static bool RayCast(Vector2 pos, Vector2 dir, out float hit, uint ignoreTarget, float distance = -1f)
    {
        //Console.WriteLine();
        return RayCast_Engine(pos, dir, out hit, ignoreTarget, distance);
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern bool RayCast_Engine(Vector2 pos, Vector2 dir, out float hit, uint ignoreTarget, float distance);
}

