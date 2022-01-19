using System;
using System.Collections.Generic;
using System.Linq;

public class Marker
{
    public Vector2 Position { get => transform.position; }

    public List<Marker> adjacentMarkers;

    private bool openForConnections;

    public bool OpenForconnections
    {
        get { return openForConnections; }
    }

    public List<Vector2> GetAdjacentPositions()
    {
        return new List<Vector2>(adjacentMarkers.Select(x => x.Position).ToList());
    }
}
