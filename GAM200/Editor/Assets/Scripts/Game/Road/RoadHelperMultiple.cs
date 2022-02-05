using System;
using System.Collections.Generic;
using System.Linq;

class RoadHelperMultiple : RoadHelper
{
    protected List<Marker> incomingMarkers, outgoingMarkers;

    //public int num;
    Waypoint waypoint;

    public override void Start()
    {
        Waypoint wp = GetComponent<Waypoint>();

        List<List<List<Vector2>>> listOfWaypoints = wp.GetWaypoints();
        List<Marker> carMarkers = new List<Marker>();

        foreach (var incomingOutgoing in listOfWaypoints)
        {
            foreach (var markerss in incomingOutgoing)
            {
                carMarkers.Add(new Marker(markerss));

                if (markerss == incomingOutgoing[0])
                    incomingMarkers = carMarkers;
                else
                    outgoingMarkers = carMarkers;
            }

            Console.WriteLine("Incoming/Outgoing End\n\n");
        }

    }

    public override Marker GetPositionForCarToSpawn(Vector2 nextPathPosition)
    {
        return GetClosestMarkerTo(nextPathPosition, outgoingMarkers);
    }

    public override Marker GetPositionForCarToEnd(Vector2 previousPathPosition)
    {
        return GetClosestMarkerTo(previousPathPosition, incomingMarkers);
    }
}
