 using System;
using System.Collections.Generic;
using System.Linq;

public class Marker
{
    public Vector2 Position { set; get; }

    public List<Vector2> adjacentMarkers;

    private bool openForConnections;

    public Marker(List<Vector2> tem)
    {
        adjacentMarkers = new List<Vector2>();
        int index = 0;
        foreach (var i in tem)
        {
            if (index == 0)
            {
                Position = i;
            }
            else
            {
                adjacentMarkers.Add(i);
            }
        }
    }

    public bool OpenForconnections
    {
        get { return openForConnections; }
    }

    public List<Vector2> GetAdjacentPositions()
    {
        return adjacentMarkers;
        //return new List<Vector2>(adjacentMarkers.Select(x => x.Position).ToList());
    }

    public static List<Marker> Vector2ToMarker(List<Vector2> tem)
    {
        List<Marker> lom = new List<Marker>();
        foreach (var i in tem)
        {
            Debug.Log("Position " + i);

            lom.Add(new Marker(i));
        }
        return lom;
    }
}
