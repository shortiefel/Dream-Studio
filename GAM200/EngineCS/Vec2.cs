/* Start Header**********************************************************************************/
/*
@file    Vec2.cs
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

public struct Vec2
{
    public float x, y;

    public Vec2(float n1, float n2)
    {
        x = n1;
        y = n2;
    }

    public Vec2(Vec2 n)
    {
        x = n.x;
        y = n.y;
    }

    public static Vec2 operator +(Vec2 lhs, Vec2 rhs)
    {
        return new Vec2(lhs.x + rhs.x, lhs.y + rhs.y);
    }

    public static Vec2 operator *(Vec2 lhs, float num)
    {
        return new Vec2(lhs.x * num, lhs.y * num);
    }

    public static Vec2 operator-(Vec2 lhs)
    {
        lhs.x = -lhs.x;
        lhs.y = -lhs.y;
        return lhs;
    }

    public override string ToString()
    {
        return "Vec2: " + x + " " + y;
    }
}