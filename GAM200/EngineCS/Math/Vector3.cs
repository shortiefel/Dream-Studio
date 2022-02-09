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

public struct Vector3
{
    public float x, y, z;
    public static Vector3 zero = new Vector3(0, 0, 0);
    public Vector3(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    public Vector3(Vector2 t, float _z)
    {
        x = t.x;
        y = t.y;
        z = _z;
    }

    public Vector3(Vector3 n)
    {
        x = n.x;
        y = n.y;
        z = n.z;
    }

    public static Vector3 operator +(Vector3 lhs, Vector3 rhs)
    {
        return new Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
    }

    public static Vector3 operator -(Vector3 lhs, Vector3 rhs)
    {
        return new Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
    }

    public static Vector3 operator *(Vector3 lhs, float num)
    {
        return new Vector3(lhs.x * num, lhs.y * num, lhs.z * num);
    }

    public static Vector3 operator -(Vector3 lhs)
    {
        lhs.x = -lhs.x;
        lhs.y = -lhs.y;
        lhs.z = -lhs.z;
        return lhs;
    }
    public override string ToString()
    {
        return "Vector3: " + x + " " + y + " " + z;
    }
}