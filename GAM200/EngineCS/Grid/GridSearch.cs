using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices; //For internal calls

public class GridSearch
{

    public struct SearchResult
    {
        public List<Point> Path { get; set; }
    }

    public static List<Point> AStarSearch(Grid grid, Point startPosition, Point endPosition, bool isAgent = false)
    {
        /*Vector2Int[] pos = new Vector2Int[100];
        AStarSearch_Engine(pos, out int numOfElement, new Vector2Int(startPosition), new Vector2Int(endPosition), isAgent);
        Console.WriteLine("New path------------------------------------------------------");
        for (int i = 0; i < numOfElement; i++)
        {
            Console.WriteLine(pos[i]);
        }*/

        List<Point> path = new List<Point>();

        List<Point> positionsTocheck = new List<Point>();
        Dictionary<Point, float> costDictionary = new Dictionary<Point, float>();
        Dictionary<Point, float> priorityDictionary = new Dictionary<Point, float>();
        Dictionary<Point, Point> parentsDictionary = new Dictionary<Point, Point>();

        positionsTocheck.Add(startPosition);
        priorityDictionary.Add(startPosition, 0);
        costDictionary.Add(startPosition, 0);
        parentsDictionary.Add(startPosition, null);

        while (positionsTocheck.Count > 0)
        {
            Point current = GetClosestVertex(positionsTocheck, priorityDictionary);
            positionsTocheck.Remove(current);
            if (current.Equals(endPosition))
            {
                path = GeneratePath(parentsDictionary, current);
                Console.WriteLine("Old path");
                foreach (Point pt in path)
                {
                    Console.WriteLine(pt);
                }
                Console.WriteLine("------------------------------------------------------------------------------------------------------------");

                return path;
            }

            foreach (Point neighbour in grid.GetAdjacentCells(current, isAgent))
            {
                float newCost = costDictionary[current] + grid.GetCostOfEnteringCell(neighbour);
                if (!costDictionary.ContainsKey(neighbour) || newCost < costDictionary[neighbour])
                {
                    costDictionary[neighbour] = newCost;

                    float priority = newCost + ManhattanDiscance(endPosition, neighbour);
                    positionsTocheck.Add(neighbour);
                    priorityDictionary[neighbour] = priority;

                    parentsDictionary[neighbour] = current;
                }
            }
        }

        /*Vector2Int[] pos2 = new Vector2Int[100];
        AStarSearch_EngineAStarSearch_Engine(pos2, out int numOfElement2, startPosition, endPosition, isAgent);
        Console.WriteLine("end    New path------------------------------------------------------");
        for (int i = 0; i < numOfElement2; i++)
        {
            Console.WriteLine(pos2[i]);
        }
        Console.WriteLine("end     Old path");
        foreach (Point pt in path)
        {
            Console.WriteLine(pt);
        }
        Console.WriteLine("------------------------------------------------------------------------------------------------------------");*/
        return path;
    }

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void AStarSearch_Engine(Vector2Int[] pos, out int count, Vector2Int startPosition, Vector2Int endPosition, bool isAgent);

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
        Console.WriteLine("Generating path");
        List<Point> path = new List<Point>();
        Console.WriteLine("Generating path middle " + path.Count);
        Point parent = endState;
        Console.WriteLine("Generating path before " + path.Count);
        while (parent != null && parentMap.ContainsKey(parent))
        {
            path.Add(parent);
            parent = parentMap[parent];
        }
        Console.WriteLine("Generating path ending....  " + path.Count);
        return path;
    }
}