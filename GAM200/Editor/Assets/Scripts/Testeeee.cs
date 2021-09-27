using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class TrailTest3 : MonoBehaviour
{
    //Transform transform;
    Transform go2;

    public override void OnInit()
    {
        go2 = GetComponent<Transform>();
        // objTrans1 = GetComponentWithID<Transform>(0); //DOesnt work for replay since number is hardcoded, entity value doesnt reset
        //Transform tem = GetTransform();
        //Vec2 pos = go2.GetPosition();
        //Console.WriteLine(pos);

        //Console.WriteLine(go2);
        //go2.position = new Vec2(-104.378f, 138.301f);
        //go2.scale = new Vec2(30, 100);
        /*Console.WriteLine(go2.position + new Vec2(10,10));

        go2.position += new Vec2(500, 500);
        Console.WriteLine(go2.position);*/

        Console.WriteLine("TrailTest3 fdfdfdf");
    }


    public override void OnUpdate()
    {


        //objTrans1.position = go2.position;

        //Console.WriteLine(go2.position);
        //Console.WriteLine(go2.position);
        if (Input.IsKeyPressed(KeyCode.J)) {
            go2.Move(new Vec2(-200 * Time.dt, 0));
        }

        if (Input.IsKeyPressed(KeyCode.L))
        {
            go2.Move(new Vec2(200 * Time.dt, 0));
        }

        if (Input.IsKeyPressed(KeyCode.I))
        {
            go2.Move(new Vec2(0, 200 * Time.dt));
        }

        if (Input.IsKeyPressed(KeyCode.K))
        {
            go2.Move(new Vec2(0, -200 * Time.dt));
        }

        if (Input.IsKeyPressed(KeyCode.U))
        {
            go2.angle += 50 * Time.dt;
        }

        if (Input.IsKeyPressed(KeyCode.O))
        {
            go2.angle -= 50 * Time.dt;
        }

        if (Input.IsKeyPressed(KeyCode.M))
        {
            Enable(this);
        }

        if (Input.IsKeyPressed(KeyCode.V))
        {
            //Instantiate_Entity("Box2");
            //Console.WriteLine(Input.IsKeyPressed(KeyCode.E));
            //Disable(this);
        }
    }

    /*public override void OnCollisionEnter()
    {
        Instantiate_Entity("Box2");
    }*/
    /*
    public override void OnCollisionExit()
    {
        Console.WriteLine("Test2222 Collision Exit");
    }

    public override void OnTriggerEnter()
    {
        Console.WriteLine("Test2222 Trigger Enter");
    }

    public override void OnTriggerExit()
    {
        Console.WriteLine("Test2222 Trigger Exit");
    }*/
}

