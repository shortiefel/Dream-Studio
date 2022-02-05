using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class AdjacencyGraph
{
    Dictionary<Vertex, List<Vertex>> adjacencyDictionary;

    public AdjacencyGraph()
    {
        adjacencyDictionary = new Dictionary<Vertex, List<Vertex>>();
    }
    public Vertex AddVertex(Vector2 position)
    {
        if (GetVertexAt(position) != null)
        {
            return null;
        }

        Vertex v = new Vertex(position);
        AddVertex(v);
        return v;

    }

    private void AddVertex(Vertex v)
    {
        if (adjacencyDictionary.ContainsKey(v))
            return;
        adjacencyDictionary.Add(v, new List<Vertex>());
    }

    private Vertex GetVertexAt(Vector2 position)
    {
        return adjacencyDictionary.Keys.FirstOrDefault(x => CompareVertices(position, x.Position));
    }

    private bool CompareVertices(Vector2 position1, Vector2 position2)
    {
        return Vector2.Distance(position1, position2) < 0.0001f;
    }

    public void AddEdge(Vector2 position1, Vector2 position2)
    {
        if (CompareVertices(position1, position2))
        {
            return;
        }
        var v1 = GetVertexAt(position1);
        var v2 = GetVertexAt(position2);
        if (v1 == null)
        {
            v1 = new Vertex(position1);
        }
        if (v2 == null)
        {
            v2 = new Vertex(position2);
        }
        AddEdgeBetween(v1, v2);
        AddEdgeBetween(v2, v1);

    }

    private void AddEdgeBetween(Vertex v1, Vertex v2)
    {
        if (v1 == v2)
        {
            return;
        }
        if (adjacencyDictionary.ContainsKey(v1))
        {
            if (adjacencyDictionary[v1].FirstOrDefault(x => x == v2) == null)
            {
                adjacencyDictionary[v1].Add(v2);
            }
        }
        else
        {
            AddVertex(v1);
            adjacencyDictionary[v1].Add(v2);
        }

    }

    public List<Vertex> GetConnectedVerticesTo(Vertex v1)
    {
        if (adjacencyDictionary.ContainsKey(v1))
        {
            return adjacencyDictionary[v1];
        }
        return null;
    }

    public List<Vertex> GetConnectedVerticesTo(Vector2 position)
    {
        var v1 = GetVertexAt(position);
        if (v1 == null)
            return null;
        return adjacencyDictionary[v1];
    }

    public void ClearGraph()
    {
        adjacencyDictionary.Clear();
    }

    public IEnumerable<Vertex> GetVertices()
    {
        return adjacencyDictionary.Keys;
    }

    public override string ToString()
    {
        StringBuilder builder = new StringBuilder();
        foreach (var vertex in adjacencyDictionary.Keys)
        {
            builder.AppendLine("Vertex " + vertex.ToString() + " neighbours: " + String.Join(", ", adjacencyDictionary[vertex]));
        }
        return builder.ToString();
    }

    public static List<Vector2> AStarSearch(AdjacencyGraph graph, Vector2 startPosition, Vector2 endPosition)
    {
        List<Vector2> path = new List<Vector2>();

        Vertex start = graph.GetVertexAt(startPosition);
        Vertex end = graph.GetVertexAt(endPosition);

        List<Vertex> positionsTocheck = new List<Vertex>();
        Dictionary<Vertex, float> costDictionary = new Dictionary<Vertex, float>();
        Dictionary<Vertex, float> priorityDictionary = new Dictionary<Vertex, float>();
        Dictionary<Vertex, Vertex> parentsDictionary = new Dictionary<Vertex, Vertex>();

        positionsTocheck.Add(start);
        priorityDictionary.Add(start, 0);
        costDictionary.Add(start, 0);
        parentsDictionary.Add(start, null);

        while (positionsTocheck.Count > 0)
        {
            Vertex current = GetClosestVertex(positionsTocheck, priorityDictionary);
            positionsTocheck.Remove(current);
            if (current.Equals(endPosition))
            {
                path = GeneratePath(parentsDictionary, current);
                return path;
            }

            foreach (Vertex neighbour in graph.GetConnectedVerticesTo(current))
            {
                float newCost = costDictionary[current] + 1;
                if (!costDictionary.ContainsKey(neighbour) || newCost < costDictionary[neighbour])
                {
                    costDictionary[neighbour] = newCost;

                    float priority = newCost + ManhattanDiscance(end, neighbour);
                    positionsTocheck.Add(neighbour);
                    priorityDictionary[neighbour] = priority;

                    parentsDictionary[neighbour] = current;
                }
            }
        }
        return path;
    }

    private static Vertex GetClosestVertex(List<Vertex> list, Dictionary<Vertex, float> distanceMap)
    {
        Vertex candidate = list[0];
        foreach (Vertex vertex in list)
        {
            if (distanceMap[vertex] < distanceMap[candidate])
            {
                candidate = vertex;
            }
        }
        return candidate;
    }

    private static float ManhattanDiscance(Vertex endPos, Vertex position)
    {
        return Math.Abs(endPos.Position.x - position.Position.x) + Math.Abs(endPos.Position.y - position.Position.y);
    }

    public static List<Vector2> GeneratePath(Dictionary<Vertex, Vertex> parentMap, Vertex endState)
    {
        List<Vector2> path = new List<Vector2>();
        Vertex parent = endState;
        while (parent != null && parentMap.ContainsKey(parent))
        {
            path.Add(parent.Position);
            parent = parentMap[parent];
        }
        return path;
    }
}
