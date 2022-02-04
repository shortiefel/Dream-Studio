using System;
using System.Collections.Generic;
using System.Linq;

class RoadHelperMultiple : RoadHelper
{
    protected List<Marker> incomingMarkers, outgoingMarkers;

    public override void Start()
    {
        Waypoint wp = GetComponent<Waypoint>();

        List<List<Vector2>> listOfWaypoints = wp.GetWaypoints();

        foreach (var i in listOfWaypoints)
        {
            //Console.WriteLine("Current set");
            foreach (var t in i)
            {
                //Console.WriteLine(t);

                //one  set of waypoint to pass to incomingMarkers, one waypoint to pass to outgoingMarkers
                //for corner, three-way, four-way
            }
            List<Marker> carMarkers = Marker.Vector2ToMarker(i);

            if (i == listOfWaypoints[0])
                incomingMarkers = carMarkers;
            else
                outgoingMarkers = carMarkers;

            //Console.WriteLine("\nNext Set \n");
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
