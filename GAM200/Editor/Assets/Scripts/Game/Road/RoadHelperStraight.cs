using System;
using System.Collections;
using System.Collections.Generic;

public class RoadHelperStraight : RoadHelper
{
    private Marker leftLaneMarker90, rightLaneMarker90;

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

                //one waypoint to pass to leftLaneMarker90, one waypoint to pass to rightLaneMarker90
                //for straight road only

                if (t.x == i[0].x)
                    rightLaneMarker90.Position = t;

                if (t.x == i[0].x)
                    leftLaneMarker90.Position = t;
            }
            List<Marker> carMarkers = Marker.Vector2ToMarker(i);

            //Console.WriteLine("\nNext Set \n");
        }
    }

    public override Marker GetPositionForCarToSpawn(Vector2 nextPathPosition)
    {
        int angle = (int)transform.angle;
        var direction = nextPathPosition - transform.position;
        return GetCorrectMarker(angle, direction);
    }


    public override Marker GetPositionForCarToEnd(Vector2 previousPathPosition)
    {
        int angle = (int)transform.angle;
        var direction = transform.position - previousPathPosition;
        return GetCorrectMarker(angle, direction);
    }


    private Marker GetCorrectMarker(int angle, Vector2 directionVector)
    {
        var direction = GetDirection(directionVector);
        if (angle == 0)
        {
            if (direction == Directon.left)
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
            if (direction == Directon.up)
            {
                return rightLaneMarker90;
            }
            else
            {
                return leftLaneMarker90;
            }
        }
        else if (angle == 270)
        {
            if (direction == Directon.left)
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
            if (direction == Directon.up)
            {
                return leftLaneMarker90;
            }
            else
            {
                return rightLaneMarker90;
            }
        }
    }

    public enum Directon
    {
        up,
        down,
        left,
        right
    }

    public Directon GetDirection(Vector2 direction)
    {
        if (Mathf.Abs(direction.y) > .5f)
        {
            if (direction.y > 0.5f)
            {
                return Directon.up;
            }
            else
            {
                return Directon.down;
            }
        }
        else
        {
            if (direction.x > 0.5f)
            {
                return Directon.right;
            }
            else
            {
                return Directon.left;
            }
        }
    }
}