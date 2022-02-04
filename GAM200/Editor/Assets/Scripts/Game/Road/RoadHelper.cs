﻿using System;
using System.Collections.Generic;
using System.Linq;

public class RoadHelper : MonoBehaviour
{
    protected List<Marker> carMarkers;

    protected bool isCorner;

    protected bool hasCrosswalks;

    float approximateThresholdCorner = 0.3f;

    private Marker incoming, outgoing;

    public override void Start()
    {
        Waypoint wp = GetComponent<Waypoint>();

        //The list hold list of vector2 (each List<Vector2> is a possible path/route the car can take
        //The points added should be with reference to the center 0, 0
        //Order is how the list of points (shown in the inspector) will be cut 
        //The first value currently is 2 so only 2 position is considered as one route
        //The Console.WriteLine below will display how the route are spilt up in the console
        //The numbers in the order should add up to the number of points your have

        //You can view the TestScene.scene to see how to directly add the points and order in or another way is to add it using the inspector

        //TLDR
        //points = all possible waypoint the car can go to
        //order = how to group the points (the number of element = number of route) (the total value of all order should be = number of waypoints)


        //incoming = new Marker();
        //outgoing = new Marker();

        List<List<Vector2>> listOfWaypoints = wp.GetWaypoints();

        foreach (var i in listOfWaypoints)
        {
            //Console.WriteLine("Current set");
            foreach (var t in i)
            {
                Console.WriteLine(t);

                //one waypoint to pass to incoming, one waypoint to pass to outgoing
                //for Deadend only

                //if (t.x == i[0].x)
                //    incoming.Position = t;
                //else
                //    outgoing.Position = t;
                //
                //Console.WriteLine("incoming =" + incoming.Position);
            }

 
                //incoming.Position = i[0];

                //outgoing.Position = i[1];

            //Console.WriteLine("incoming =" + incoming.Position);
            //Console.WriteLine("outgoing =" + outgoing.Position);

            //List<Marker> carMarkers = Marker.Vector2ToMarker(i);
            Marker.Vector2ToMarker(i);

            //Console.WriteLine("\nNext Set \n");
        }

        
    }

    //public virtual Marker GetpositioForPedestrianToSpwan(Vector2 structurePosition)
    //{
    //    return GetClosestMarkerTo(structurePosition, carMarkers);
    //}

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
