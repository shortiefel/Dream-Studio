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
        carMarkers = new List<Marker>();
        incomingMarkers = new List<Marker>();
        outgoingMarkers = new List<Marker>();

        for (int i = 0; i < listOfWaypoints.Count; i++)
        {
            foreach (var markerss in listOfWaypoints[i])
            {
                Marker mark = new Marker(markerss);
                carMarkers.Add(mark);

                if (mark.OpenForconnections == true)
                {
                    //Incoming
                    if (i == 0)
                    {
                        incomingMarkers.Add(mark);
                    }
                    //Outgoing
                    else
                    {
                        outgoingMarkers.Add(mark);
                    }
                }
                
            }

        }
        Debug.Log("Marker position = " + incomingMarkers[0].Position);

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
