using System;
using System.Collections.Generic;
using System.Linq;

public class Marker : MonoBehaviour
{
    public Vector2 Position { get { return transform.position; } }

    public List<Marker> adjacentMarkers;

    private bool openForConnections;

    public Marker(Vector2 tem)
    {
        transform.position = tem;
    }

    public bool OpenForconnections
    {
        get { return openForConnections; }
    }

    public List<Vector2> GetAdjacentPositions()
    {
        return new List<Vector2>(adjacentMarkers.Select(x => x.Position).ToList());
    }

    public static List<Marker> Vector2ToMarker(List<Vector2> tem)
    {
        List<Marker> lom = new List<Marker>();
        foreach (var i in tem)
        {
            lom.Add(new Marker(i));
        }
        return lom;
    }
}
