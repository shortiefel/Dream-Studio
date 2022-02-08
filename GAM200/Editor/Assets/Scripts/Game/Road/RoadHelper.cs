using System;
using System.Collections.Generic;
using System.Linq;

public class RoadHelper : MonoBehaviour
{
    protected List<Marker> carMarkers;

    protected bool isCorner;

    protected bool hasCrosswalks;

    float approximateThresholdCorner;

    private Marker incoming, outgoing;
    public int num;
    Waypoint waypoint;

    public override void Start()
    {
        isCorner = false;
        hasCrosswalks = false;

        approximateThresholdCorner = 0.3f;

        Waypoint wp = GetComponent<Waypoint>();

        List<List<List<Vector2>>> listOfWaypoints = wp.GetWaypoints();
        carMarkers = new List<Marker>();

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
        }
        Debug.Log("Marker position = " + incoming.Position);
    }

    public virtual Marker GetPositionForCarToSpawn(Vector2 nextPathPosition)
    {
        return outgoing;
    }

    public virtual Marker GetPositionForCarToEnd(Vector2 previousPathPosition)
    {
        return incoming;
    }

    protected Marker GetClosestMarkerTo(Vector2 structurePosition, List<Marker> _carMarkers, bool isCorner = false)
    {
        if (isCorner)
        {
            foreach (var marker in _carMarkers)
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
            foreach (var marker in _carMarkers)
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
        if (carMarkers == null) Console.WriteLine("Getting CarMarker    In roadhelper and carmarker is null");
        return new Vector2(0, 0);
        //return GetClosestMarkerTo(currentPosition, carMarkers, false).Position;
    }


    public List<Marker> GetAllCarMarkers()
    {
        return carMarkers;
    }
}
