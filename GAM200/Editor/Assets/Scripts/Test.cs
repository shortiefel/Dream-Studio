using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

/*public enum TEST
{
    tem = 0,
    tem1,
    tem2
}*/

public class Test : MonoBehaviour
{
    //Transform transform;
    public int health;
    /* public Vec2 vec2Test;
        public TEST testEnum;
        public char testChar;
        public Vec2 newvec2Test;*/
    Transform go2;
    //Collider col1;

    public override void OnInit()
    {
        go2 = GetComponent<Transform>();
        //col1 = GetComponent<Collider>();
        //Console.WriteLine(GetComponent<Collider>().entityId);
        //Transform tem = GetTransform();
        //Vec2 pos = go2.GetPosition();
        //Console.WriteLine(pos);
        //go2.position = new Vec2(0, 0);
        Console.WriteLine("init");

        //Console.WriteLine(go2);

        //go2.scale = new Vec2(30, 100);
        /*Console.WriteLine(go2.position + new Vec2(10,10));

        go2.position += new Vec2(500, 500);
        Console.WriteLine(go2.position);*/
        //Console.WriteLine(col1.entityId);
        Console.WriteLine("Has Component Collider? ");
        Console.WriteLine(HasComponent<Collider>(entityId));
    }


    public override void OnUpdate()
    {
        //Console.WriteLine("new Update");
        //Console.WriteLine(Input::GetMouse);
        if (Input.IsKeyPressed(KeyCode.A))
        {
            go2.position += -go2.right * Time.dt * 250;
        }

        if (Input.IsKeyPressed(KeyCode.D))
        {
            go2.position += go2.right * Time.dt * 250;
        }

        if (Input.IsKeyPressed(KeyCode.W))
        {
            go2.position += go2.forward * Time.dt * 250;
        }

        if (Input.IsKeyPressed(KeyCode.S))
        {
            go2.position += -go2.forward * Time.dt * 250;
        }

        if (Input.IsKeyPressed(KeyCode.Q))
        {
            go2.angle += 250 * Time.dt;
        }

        if (Input.IsKeyPressed(KeyCode.E))
        {
            go2.angle -= 250 * Time.dt;
        }




        if (Input.IsKeyPressed(KeyCode.C))
        {
            //Instantiate_Entity("Box");
            //Console.WriteLine(Input.IsKeyPressed(KeyCode.E));
            //Disable(this);
        }
    }

    public override void OnCollisionEnter()
    {
        //Instantiate_Entity("Box");
        SceneManager.LoadScene("Test3");
        Console.WriteLine("Test Collision Enter");
    }

    public override void OnCollisionExit()
    {
        Console.WriteLine("Test Collision Exit");
    }

    public override void OnTriggerEnter()
    {
        Console.WriteLine("Test Trigger Enter");
    }

    public override void OnTriggerExit()
    {
        Console.WriteLine("Test Trigger Exit");
    }

}


