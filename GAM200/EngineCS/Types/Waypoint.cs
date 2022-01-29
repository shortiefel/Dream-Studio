/* Start Header**********************************************************************************/
/*
@file    Waypoint.cs
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    29/04/2022
\brief
This file has the function definition for Waypoint


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

using System.Runtime.CompilerServices; //For internal calls
using System.Collections.Generic;


using System;
public class Waypoint : IComponent
{
    //public uint entityId { get; set; }
    public Waypoint() { }
    public Waypoint(uint entity_id) { entityId = entity_id; }

    public List<List<Vector2>> GetWaypoints()
    {
        List<List<Vector2>> listOfWaypoints = new List<List<Vector2>>();

        Vector2[] points = new Vector2[100];
        uint[] order = new uint[10];
        Waypoint_GetWaypoints_Engine(entityId, points, order);

        int p = 0;
        foreach (var i in order)
        {
            if (i == 0) break;
            List<Vector2> tem = new List<Vector2>();
            int start = p;
            while (true) {
                tem.Add(points[p]);
                ++p;
                if (p - start >= i) break;
            }
            listOfWaypoints.Add(tem);
        }

        foreach (var i in listOfWaypoints)
        {
            Console.WriteLine("Current set");
            foreach (var t in i)
            {
                Console.WriteLine(t);
            }

            Console.WriteLine("\nNext Set \n");
        }
        
        return listOfWaypoints;
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void Waypoint_GetWaypoints_Engine(uint entityId, Vector2[] points, uint[] order);


    //public uint GetNumberOfRoute()
    //{
    //    if (entityId == 0) return 0;
    //    Waypoint_GetNumberOfRoute_Engine(entityId, out uint num);
    //    return num;
    //}
    //[MethodImpl(MethodImplOptions.InternalCall)]
    //internal static extern void Waypoint_GetNumberOfRoute_Engine(uint entityID, out uint num);
    //public void Play(string _state)
    //{
    //    SetAnimation_Engine(entityId, _state);
    //}
    //
    //[MethodImpl(MethodImplOptions.InternalCall)]
    //internal static extern void SetAnimation_Engine(uint entityID, string state);
}