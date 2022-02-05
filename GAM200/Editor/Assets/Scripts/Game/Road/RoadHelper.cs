using System;
using System.Collections.Generic;
using System.Linq;

public class RoadHelper : MonoBehaviour
{
    protected List<Marker> carMarkers;

    protected bool isCorner;

    protected bool hasCrosswalks;

    float approximateThresholdCorner = 0.3f;

    private Marker incoming, outgoing;
    public int num;
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
                    incoming = carMarkers[0];
                else
                    outgoing = carMarkers[0];
            }

            Console.WriteLine("Incoming/Outgoing End\n\n");
        }

    }

    public virtual Marker GetPositionForCarToSpawn(Vector2 nextPathPosition)
    {
        return outgoing;
    }

    public virtual Marker GetPositionForCarToEnd(Vector2 previousPathPosition)
    {
        return incoming;
    }

    protected Marker GetClosestMarkerTo(Vector2 structurePosition, List<Marker> carMarkers, bool isCorner = false)
    {
        if (isCorner)
        {
            foreach (var marker in carMarkers)
            {
                var direction = marker.Position - structurePosition;
                direction.Normalize();
                if (Mathf.Abs(direction.x) < approximateThresholdCorner || Mathf.Abs(direction.y) < approximateThresholdCorner)
                {
                    return marker;
                }
            }
            return null;
        }
        else
        {
            Marker closestMarker = null;
            float distance = float.MaxValue;
            foreach (var marker in carMarkers)
            {
                var markerDistance = Vector2.Distance(structurePosition, marker.Position);
                if (distance > markerDistance)
                {
                    distance = markerDistance;
                    closestMarker = marker;
                }
            }
            return closestMarker;
        }
    }

    public Vector2 GetClosestCarMarkerPosition(Vector2 currentPosition)
    {
        return GetClosestMarkerTo(currentPosition, carMarkers, false).Position;
    }


    public List<Marker> GetAllCarMarkers()
    {
        return carMarkers;
    }
}
