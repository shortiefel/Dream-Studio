/* Start Header**********************************************************************************/
/*
@file    Point.cs
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    06/11/2021
\brief
This file has the function definition for Point
This is almost the same as Vector2 but is given a different name to be
used as a point in Grid.
It will be easier to differentiate using Point and Vector2 with this


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

public class Point
{
    public float X { get; set; }
    public float Y { get; set; }

    public Point(float x, float y)
    {
        this.X = x;
        this.Y = y;
    }

    public Point(Vector2Int pos)
    {
        this.X = (float)pos.x;
        this.Y = (float)pos.y;
    }

    public Point(Vector2 pos)
    {
        this.X = pos.x;
        this.Y = pos.y;
    }

    public Point(Point point)
    {
        this.X = point.X;
        this.Y = point.Y;
    }

    public override bool Equals(object obj)
    {
        if (obj == null)
        {
            return false;
        }
        if (obj is Point)
        {
            Point p = obj as Point;
            return this.X == p.X && this.Y == p.Y;
        }
        return false;
    }

    public override int GetHashCode()
    {
        unchecked
        {
            int hash = 6949;
            hash = hash * 7907 + X.GetHashCode();
            hash = hash * 7907 + Y.GetHashCode();
            return hash;
        }
    }

    public override string ToString()
    {
        return "P(" + this.X + ", " + this.Y + ")";
    }
}

