using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


class Test3 : MonoBehaviour
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
    }
}

