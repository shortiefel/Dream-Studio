
using System.Collections.Generic;
using System;

public class Test2 : MonoBehaviour
{
    //public int num;
    //Waypoint waypoint;

    public override void Start()
    {
        //waypoint = GetComponent<Waypoint>();
        //
        //List<List<List<Vector2>>> wp = waypoint.GetWaypoints();
        //Console.WriteLine("\n\n\n");
        //foreach (var first in wp) //List<List<Vector2>> in List<List<List<Vector2>>>
        //{
        //    Console.WriteLine("Incoming/Outgoing start\n");
        //
        //
        //    foreach (var second in first) //List<Vector2> in List<List<Vector2>>
        //    {
        //
        //        Console.WriteLine("Marker set start: (First position is position of marker and subsequent are adjacent)");
        //        foreach (var third in second) //Vector2 in List<Vector2>
        //        {
        //            Console.WriteLine(third);
        //        }
        //
        //        Console.WriteLine("Marker set end\n");
        //    }
        //
        //    Console.WriteLine("Incoming/Outgoing End\n\n");
        //}

    }

    public override void Update()
    {
        //if (Input.GetMouseButtonDown(MouseCode.Left)){
        //    Console.WriteLine("Inside-------");
        //}
        if (Input.GetKey(KeyCode.W))
        {
            transform.position += new Vector2(0f, 1f);
        }
        
        if (Input.GetKey(KeyCode.S))
        {
            transform.position += new Vector2(0f, -1f);
        }

    }
}
