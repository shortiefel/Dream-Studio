using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices; //For internal calls

public class GridSearch
{

    //public struct SearchResult
    //{
    //    public List<Point> path;
    //
    //    public SearchResult(List<Point> _path)
    //    {
    //        path = _path;
    //    }
    //}

    public static List<Vector2> AStarSearch(Grid grid, out Vector2Int housePoint, Vector2Int destPoint, int routeType, ref List<Vector2Int> leftArray, ref List<Vector2Int> rightArray)
    {
        //grid.PrintGridOut();
        //
        Vector2[] pos2 = new Vector2[150];
        Vector2Int[] turnArr = new Vector2Int[50];
        List<Vector2> path = new List<Vector2>();
        AStarSearch_Engine(pos2, out int numOfElement2, turnArr, out int leftArrCount, out int rightArrCount, out housePoint, destPoint, routeType);
        //Console.WriteLine("\n Cs c++    Testing path------------------------------------------------------"); //------------------------To  Remove
        for (int i = 0; i < numOfElement2; i++)
        {
            path.Add(pos2[i]);
        }

        for (int i = 0; i < leftArrCount; i++)
        {
            leftArray.Add(turnArr[i]);
        }

        for (int i = leftArrCount; i < leftArrCount + rightArrCount; i++)
        {
            rightArray.Add(turnArr[i]);
        }

        return path;
    }

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void AStarSearch_Engine(Vector2[] pos, out int count, Vector2Int[] posTurn, out int countleft, out int countright, out Vector2Int housePosition, Vector2Int destPosition, int routeType);

    private static Point GetClosestVertex(List<Point> list, Dictionary<Point, float> distanceMap)
    {
        Point candidate = list[0];
        foreach (Point vertex in list)
        {
            if (distanceMap[vertex] < distanceMap[candidate])
            {
                candidate = vertex;
            }
        }
        return candidate;
    }

    private static float ManhattanDiscance(Point endPos, Point point)
    {
        return Math.Abs(endPos.X - point.X) + Math.Abs(endPos.Y - point.Y);
    }
    /*[MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void SetCellType(int x, int y, int cellType);*/

    private static List<Point> GeneratePath(Dictionary<Point, Point> parentMap, Point endState)
    {
        List<Point> path = new List<Point>();
        Point parent = endState;

        while (parent != null && parentMap.ContainsKey(parent))
        {
            path.Add(parent);
            parent = parentMap[parent];
        }
        return path;
    }
}