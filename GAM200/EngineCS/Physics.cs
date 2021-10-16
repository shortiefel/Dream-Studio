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

public class Physics
{
    //Leave distance parameter blank to have "infinite" length
    public static bool RayCast(Vec2 pos, Vec2 dir, out float hit, float distance = -1f)
    {
        return RayCast_Engine(pos, dir, out hit, distance);
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern bool RayCast_Engine(Vec2 pos, Vec2 dir, out float hit, float distance);
}

