using System;
using System.Collections;
using System.Collections.Generic;

public class RoadHelperStraight : RoadHelper
{
    private Marker leftLaneMarker90, rightLaneMarker90;

    //public int num;
    Waypoint waypoint;

    public override void Start()
    {
        Waypoint wp = GetComponent<Waypoint>();

        List<List<List<Vector2>>> listOfWaypoints = wp.GetWaypoints();
        carMarkers = new List<Marker>();

        for (int i = 0; i < listOfWaypoints.Count; i++)
        {
            foreach (var markerss in listOfWaypoints[i])
            {
                carMarkers.Add(new Marker(markerss));

                //if (markerss == incomingOutgoing[0])
                //    incoming = carMarkers[0];
                //else
                //    outgoing = carMarkers[0];

                //Incoming
                if (i == 0)
                {
                    leftLaneMarker90 = carMarkers[0];
                }
                //Outgoing
                else
                {
                    rightLaneMarker90 = carMarkers[0];
                }
            }
        }

    }

    public override Marker GetPositionForCarToSpawn(Vector2 nextPathPosition)
    {
        Console.WriteLine("print spawn marker");
        int angle = (int)transform.angle;
        var direction = nextPathPosition - transform.position;
        return GetCorrectMarker(angle, direction);
    }


    public override Marker GetPositionForCarToEnd(Vector2 previousPathPosition)
    {
        Console.WriteLine("print end marker");
        int angle = (int)transform.angle;
        var direction = transform.position - previousPathPosition;
        Console.WriteLine("angle " + angle);
        Console.WriteLine("direction " + direction);

        Marker testMarker = GetCorrectMarker(angle, direction);
        Console.WriteLine("Straight end marker " + testMarker.Position);
        return testMarker;
    }


    private Marker GetCorrectMarker(int angle, Vector2 directionVector)
    {
        var direction = GetDirection(directionVector);
        if (angle == 0)
        {
            if (direction == Direction.left)
            {
                return rightLaneMarker90;
            }
            else
            {
                return leftLaneMarker90;
            }
        }
        else if (angle == 90)
        {
            if (direction == Direction.up)
            {
                return rightLaneMarker90;
            }
            else
            {
                //Console.WriteLine("HERE");
                return leftLaneMarker90;
            }
        }
        else if (angle == 270)
        {
            if (direction == Direction.left)
            {
                return leftLaneMarker90;
            }
            else
            {
                return rightLaneMarker90;
            }
        }
        else
        {
            if (direction == Direction.up)
            {
                return leftLaneMarker90;
            }
            else
            {
                return rightLaneMarker90;
            }
        }
    }

    public enum Direction
    {
        up,
        down,
        left,
        right
    }

    public Direction GetDirection(Vector2 direction)
    {
        Console.WriteLine("direction check");

        float absValue = Mathf.Abs(direction.y);

        Console.WriteLine("abs y " + absValue);

        if (Mathf.Abs(direction.y) > .5f)
        {
            if (direction.y > 0.5f)
            {
                return Direction.up;
            }
            else
            {
                return Direction.down;
            }
        }
        else
        {
            if (direction.x > 0.5f)
            {
                return Direction.right;
            }
            else
            {
                return Direction.left;
            }
        }
    }
}