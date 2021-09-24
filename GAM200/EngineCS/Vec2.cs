using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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