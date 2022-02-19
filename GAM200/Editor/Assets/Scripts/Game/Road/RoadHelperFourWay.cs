/*using System;
using System.Collections.Generic;
using System.Linq;

public class RoadHelperFourWay : RoadHelper
{
    protected List<Marker> carMarkersNew;

    float approximateThresholdCorner;

    Waypoint waypoint;

    public override void Start()
    {
        isCorner = false;
        hasCrosswalks = false;

        approximateThresholdCorner = 0.3f;

        Waypoint wp = GetComponent<Waypoint>();

        List<List<List<Vector2>>> listOfWaypoints = wp.GetWaypoints();
        carMarkersNew = new List<Marker>();

        foreach (var incomingOutgoing in listOfWaypoints)
        {
            foreach (var markerss in incomingOutgoing)
            {
                carMarkersNew.Add(new Marker(markerss));
            }

        }
    }
}*/