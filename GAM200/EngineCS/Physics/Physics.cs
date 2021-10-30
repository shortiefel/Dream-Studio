/* Start Header**********************************************************************************/
/*
@file    Physics2D.cs
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

public class Physics2D
{
    //Leave distance parameter blank to have "infinite" length
    public static RaycastHit2D RayCast(Vector3 pos, Vector2 dir, float distance = Mathf.Infinity, int ignoreTarget = -1)
    {
        RaycastHit2D hit = new RaycastHit2D();
        if (!RayCast_Engine(pos, dir, ignoreTarget, distance, out uint entity_id, out hit.distance, out hit.point))
        {
            hit.collider = null;
            hit.transform = null;
        }
        else
        {
            hit.collider = new Collider(entity_id);
            hit.transform = new Transform(entity_id);
        }
        return hit;
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern bool RayCast_Engine(Vector3 pos, Vector2 dir, int ignoreTarget, float distance, out uint entity_id, out float hitDistance, out Vector2 hitPoint);
}

