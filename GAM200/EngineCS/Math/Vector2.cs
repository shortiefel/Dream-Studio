/* Start Header**********************************************************************************/
/*
@file    Vector2.cs
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    21/08/2021
\brief
This file has the function definition for Vec2


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

using System.Runtime.CompilerServices; //For internal calls

public struct Vector2
{
    public float x, y;
    
    public float magnitude
    {
        get
        {
            GetLength_Engine(out float length, new Vector2(x, y));
            return length;
        }
        set
        {
            Vector2 vec = new Vector2(x, y);
            GetNormalised_Engine(out vec);
            vec *= value;
            x = vec.x;
            y = vec.y;
        }
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void GetLength_Engine(out float length, Vector2 vec);

    public void Normalize()
    {
        Vector2 vec = new Vector2(x, y);
        GetNormalised_Engine(out vec);
        x = vec.x;
        y = vec.y;
    }

    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void GetNormalised_Engine(out Vector2 vec);

    public static Vector2 zero = new Vector2(0, 0);

    public Vector2(float n1, float n2)
    {
        x = n1;
        y = n2;
    }

    public Vector2(Vector2 n)
    {
        x = n.x;
        y = n.y;
    }

    public Vector2(Point n)
    {
        x = n.X;
        y = n.Y;
    }

    public Vector2(Vector2Int n)
    {
        x = (float)n.x;
        y = (float)n.y;
    }

    public static float Distance(Vector2 a, Vector2 b)
    {
        GetDistance_Engine(out float outFloat, a, b);
        return outFloat;
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void GetDistance_Engine(out float outFloat, Vector2 a, Vector2 b);

    public static Vector2 operator +(Vector2 lhs, Vector2 rhs)
    {
        return new Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
    }

    public static Vector2 operator *(Vector2 lhs, float num)
    {
        return new Vector2(lhs.x * num, lhs.y * num);
    }

    public static Vector2 operator *(float num, Vector2 lhs)
    {
        return new Vector2(lhs.x * num, lhs.y * num);
    }

    public static Vector2 operator -(Vector2 lhs, Vector2 rhs)
    {

        return new Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
    }

    public static Vector2 operator -(Vector2 lhs)
    {
        lhs.x = -lhs.x;
        lhs.y = -lhs.y;
        return lhs;
    }

    public static float Dot(Vector2 lhs, Vector2 rhs)
    {
        DotProduct_Engine(out float value, lhs, rhs);
        return value;
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void DotProduct_Engine(out float outFloat, Vector2 lhs, Vector2 rhs);

    public static float AngleBetween(Vector2 lhs, Vector2 rhs)
    {
        AngleBetween_Engine(out float value, lhs, rhs);
        return value;
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void AngleBetween_Engine(out float outFloat, Vector2 lhs, Vector2 rhs);


    public static Vector2 QuadraticBezier(Vector2 p0, Vector2 p1, Vector2 p2, float tVal, out float angle)
    {
        QuadraticBezier_Engine(p0, p1, p2, tVal, out Vector2 pt, out angle);
        return pt;
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void QuadraticBezier_Engine(Vector2 p0, Vector2 p1, Vector2 p2, float tVal, out Vector2 pt, out float angle);

    public override string ToString()
    {
        return "Vector2: " + x + " " + y;
    }
}