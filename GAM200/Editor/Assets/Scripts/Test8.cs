using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


class Test38 : MonoBehaviour
{
    Transform go2;

    public override void OnInit()
    {
        go2 = GetComponent<Transform>();
    }

    public override void OnUpdate()
    {
        //Console.WriteLine("new Update");
        //Console.WriteLine(Input::GetMouse);
        if (Input.IsKeyPressed(KeyCode.J))
        {
            go2.position += -go2.right * Time.dt * 250;
        }

        if (Input.IsKeyPressed(KeyCode.L))
        {
            go2.position += go2.right * Time.dt * 250;
        }

        if (Input.IsKeyPressed(KeyCode.I))
        {
            go2.position += go2.forward * Time.dt * 250;
        }

        if (Input.IsKeyPressed(KeyCode.K))
        {
            go2.position += -go2.forward * Time.dt * 250;
        }

        if (Input.IsKeyPressed(KeyCode.U))
        {
            go2.angle += 250 * Time.dt;
        }

        if (Input.IsKeyPressed(KeyCode.O))
        {
            go2.angle -= 250 * Time.dt;
        }

        if (Input.IsKeyPressed(KeyCode.M))
        {
            Console.WriteLine("Clear");
        }
    }
}

