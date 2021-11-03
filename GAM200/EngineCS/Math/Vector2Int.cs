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

    public Vector2Int(Vector2Int n)
    {
        x = n.x;
        y = n.y;
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

    public static Vector2Int RoundToInt(Vector2 vc)
    {
        return new Vector2Int((int)vc.x, (int)vc.y);
    }
    public override string ToString()
    {
        return "Vector2Int: " + x + " " + y;
    }
}