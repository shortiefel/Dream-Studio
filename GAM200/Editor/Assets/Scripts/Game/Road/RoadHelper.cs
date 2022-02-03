using System;
using System.Collections.Generic;
using System.Linq;

public class RoadHelper : MonoBehaviour
{
    protected List<Marker> carMarkers;

    protected bool isCorner;

    protected bool hasCrosswalks;

    float approximateThresholdCorner = 0.3f;

    private Marker incomming, outgoing;

    public virtual Marker GetpositioForPedestrianToSpwan(Vector2 structurePosition)
    {
        return GetClosestMarkeTo(structurePosition, carMarkers);
    }

    public virtual Marker GetPositioForCarToSpawn(Vector2 nextPathPosition)
    {
        return outgoing;
    }

    public virtual Marker GetPositioForCarToEnd(Vector2 previousPathPosition)
    {
        return incomming;
    }

    protected Marker GetClosestMarkeTo(Vector2 structurePosition, List<Marker> carMarkers, bool isCorner = false)
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
        return GetClosestMarkeTo(currentPosition, carMarkers, false).Position;
    }


    public List<Marker> GetAllCarMarkers()
    {
        return carMarkers;
    }
}
