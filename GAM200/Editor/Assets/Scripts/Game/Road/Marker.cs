 using System;
using System.Collections.Generic;
using System.Linq;

public class Marker
{
    public Vector2 Position { set; get; }

    public List<Marker> adjacentMarkers;

    private bool openForConnections;

    public Marker(Vector2 tem)
    {
        Position = tem;
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
            Debug.Log("Position " + i);
            new Marker(i);
            //lom.Add(new Marker(i));
        }
        return lom;
    }
}
