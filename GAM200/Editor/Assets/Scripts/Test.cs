﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public enum TEST
{
    tem = 0,
    tem1,
    tem2
}

public class Test : MonoBehaviour
{
    //Transform transform;
    public int health;
    public Vec2 vec2Test;
    public TEST testEnum;
    public char testChar;
    public Vec2 newvec2Test;
    Transform go2;

    public override void Init()
    {
        go2 = GetComponent<Transform>();
        //Transform tem = GetTransform();
        //Vec2 pos = go2.GetPosition();
        //Console.WriteLine(pos);
        go2.position = new Vec2(200, -300);
        Console.WriteLine(go2.position);
        //Console.WriteLine(go2);

        //go2.scale = new Vec2(30, 100);
        /*Console.WriteLine(go2.position + new Vec2(10,10));

        go2.position += new Vec2(500, 500);
        Console.WriteLine(go2.position);*/


    }


    public override void Update()
    {
        //Console.WriteLine("new Update");
        //Console.WriteLine(Input::GetMouse);
        if (Input.IsKeyPressed(KeyCode.A)) {
            go2.Move(new Vec2(10, 0));
        }

        if (Input.IsKeyPressed(KeyCode.B))
        {
            Console.WriteLine("change Update");
        }

    }
}
