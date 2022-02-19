/* Start Header**********************************************************************************/
/*
@file    Vector2Int.cs
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    30/10/2021
\brief
This file has the function definition for Vector2Int


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

public struct Vector2Int
{
    public int x, y;
    public static Vector2Int zero = new Vector2Int(0, 0);

    public Vector2Int(int n1, int n2)
    {
        x = n1;
        y = n2;
    }

    public Vector2Int(Vector2 n)
    {
        x = (int)n.x;
        y = (int)n.y;
    }

    public Vector2Int(Vector2Int n)
    {
        x = n.x;
        y = n.y;
    }
    public Vector2Int(Point n)
    {
        x = (int)n.X;
        y = (int)n.Y;
    }

    public static implicit operator Vector2(Vector2Int val)
    {
        Vector2 value = new Vector2(val);
        return value;
    }

    public static Vector2Int operator +(Vector2Int lhs, Vector2Int rhs)
    {
        return new Vector2Int(lhs.x + rhs.x, lhs.y + rhs.y);
    }

    public static Vector2Int operator *(Vector2Int lhs, int num)
    {
        return new Vector2Int(lhs.x * num, lhs.y * num);
    }

    public static Vector2Int operator -(Vector2Int lhs)
    {
        lhs.x = -lhs.x;
        lhs.y = -lhs.y;
        return lhs;
    }

    public static bool operator ==(Vector2Int lhs, Vector2Int rhs)
    {
        return (lhs.x == rhs.x && lhs.y == rhs.y);
    }

    public static bool operator !=(Vector2Int lhs, Vector2Int rhs)
    {
        return !(lhs.x == rhs.x && lhs.y == rhs.y);
    }

    public static Vector2Int RoundToInt(Vector2 vc)
    {
        float cx = vc.x < 0 ? -vc.x : vc.x;
        float cy = vc.y < 0 ? -vc.y : vc.y;
        int x = (int)cx;
        int y = (int)cy;
        x = cx < (x + 0.5) ? x : x + 1;
        y = cy < (y + 0.5) ? y : y + 1;
        x = vc.x < 0 ? -x : x;
        y = vc.y < 0 ? -y : y;
        return new Vector2Int(x, y);
    }
    public override string ToString()
    {
        return "Vector2Int: " + x + " " + y;
    }

    public override bool Equals(object obj)
    {
        return obj is Vector2Int @int &&
               x == @int.x &&
               y == @int.y;
    }

    public override int GetHashCode()
    {
        int hashCode = 1502939027;
        hashCode = hashCode * -1521134295 + x.GetHashCode();
        hashCode = hashCode * -1521134295 + y.GetHashCode();
        return hashCode;
    }
}