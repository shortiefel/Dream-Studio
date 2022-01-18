/* Start Header**********************************************************************************/
/*
@file    Vec3.cs
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    30/10/2021
\brief
This file has the function definition for Vec3


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

public struct Vector3Int
{
    public int x, y, z;
    public static Vector3Int zero = new Vector3Int(0, 0, 0);
    public Vector3Int(int _x, int _y, int _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    public Vector3Int(Vector3Int n)
    {
        x = n.x;
        y = n.y;
        z = n.z;
    }

    public static Vector3Int operator +(Vector3Int lhs, Vector3Int rhs)
    {
        return new Vector3Int(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
    }

    public static Vector3Int operator *(Vector3Int lhs, int num)
    {
        return new Vector3Int(lhs.x * num, lhs.y * num, lhs.z * num);
    }

    public static Vector3Int operator -(Vector3Int lhs)
    {
        lhs.x = -lhs.x;
        lhs.y = -lhs.y;
        lhs.z = -lhs.z;
        return lhs;
    }

    public static Vector3Int RoundToInt(Vector3 vc)
    {
        float cx = vc.x < 0 ? -vc.x : vc.x;
        float cy = vc.y < 0 ? -vc.y : vc.y;
        float cz = vc.z < 0 ? -vc.z : vc.z;
        int x = (int)cx;
        int y = (int)cy;
        int z = (int)cz;
        x = cx < (x + 0.5) ? x : x + 1;
        y = cy < (y + 0.5) ? y : y + 1;
        z = cz < (z + 0.5) ? z : z + 1;
        x = vc.x < 0 ? -x : x;
        y = vc.y < 0 ? -y : y;
        z = vc.z < 0 ? -z : z;
        return new Vector3Int(x, y, z);
    }

    public override string ToString()
    {
        return "Vector3Int: " + x + " " + y + " " + z;
    }
}