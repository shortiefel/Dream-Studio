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


    //public static RaycastHit2D[] RayCastGroup(Vector3 pos, Vector2 dir, int count, float distance = Mathf.Infinity, int ignoreTarget = -1)
    public static RaycastHit2DGroup RayCastGroup(Vector3 pos, Vector2 dir, float distance = Mathf.Infinity, int ignoreTarget = -1)
    {
        RaycastHit2DGroup rayCastGroup = new RaycastHit2DGroup();
        RaycastHit2D[] hitArray = new RaycastHit2D[10];
        uint[] entArr = new uint[10];
        float[] disArr = new float[10];
        Vector2[] pointArr = new Vector2[10];

        //if (!RayCast_Engine(pos, dir, ignoreTarget, distance, out uint entity_id, out hit.distance, out hit.point))
        if (!RayCastGroup_Engine(pos, dir, ignoreTarget, distance, out rayCastGroup.count, entArr, rayCastGroup.distance, rayCastGroup.point))
        {
            hitArray[0].collider = null;
            hitArray[0].transform = null;
        }
        else
        {
            for (int i = 0; i < rayCastGroup.count; i++)
            {
                //hitArray[i].collider = new Collider(entArr[i]);
                //hitArray[i].transform = new Transform(entArr[i]);
                //hitArray[i].distance = disArr[i];
                //hitArray[i].point = pointArr[i];

                rayCastGroup.collider[i] = new Collider(entArr[i]);
                rayCastGroup.transform[i] = new Transform(entArr[i]);
                //hitArray[i].distance = disArr[i];
                //hitArray[i].point = pointArr[i];

            }
        }

        return rayCastGroup;
    }

    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern bool RayCastGroup_Engine(Vector3 pos, Vector2 dir, int ignoreTarget, float distance, out int count, uint[] entityArray, float[] hitDisArray, Vector2[] hitPointArray);
    //internal static extern bool RayCast_Engine(Vector3 pos, Vector2 dir, int ignoreTarget, float distance, out int count, out uint entity_id, out float hitDistance, out Vector2 hitPoint);
}

