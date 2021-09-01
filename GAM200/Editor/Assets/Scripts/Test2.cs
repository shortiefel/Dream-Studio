using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class Test2 : MonoBehaviour
{
    //Transform transform;
    public int nothealth;

    Transform go2;

    public override void Init()
    {
        go2 = GetComponent<Transform>();
        //Transform tem = GetTransform();
        //Vec2 pos = go2.GetPosition();
        //Console.WriteLine(pos);

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
        if (Input.IsKeyPressed(KeyCode.Left)) {
            go2.Move(new Vec2(-10, 0));
        }

        if (Input.IsKeyPressed(KeyCode.Right))
        {
            go2.Move(new Vec2(10, 0));
        }

        if (Input.IsKeyPressed(KeyCode.Up))
        {
            go2.Move(new Vec2(0, 10));
        }

        if (Input.IsKeyPressed(KeyCode.Down))
        {
            go2.Move(new Vec2(0, -10));
        }

    }

    public override void OnCollisionEnter()
    {
        Console.WriteLine("Test2222 Collision Enter");
    }

    public override void OnCollisionExit()
    {
        Console.WriteLine("Test2222 Collision Exit");
    }
}

