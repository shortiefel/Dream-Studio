using System;
using System.Collections.Generic;

public class Waypoints : MonoBehaviour
{
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


        List<List<Vector2>> listOfWaypoints = wp.GetWaypoints();

        foreach (var i in listOfWaypoints)
        {
            Console.WriteLine("Current set");
            foreach (var t in i)
            {
                Console.WriteLine(t);
            }

            Console.WriteLine("\nNext Set \n");
        }

    }