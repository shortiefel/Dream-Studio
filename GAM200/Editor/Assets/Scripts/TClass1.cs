using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


public class TClass1 : MonoBehaviour
{
    Transform go2;

    public override void OnInit()
    {
        go2 = GetComponent<Transform>();
        //Transform tem = GetTransform();
        //Vec2 pos = go2.GetPosition();
        //Console.WriteLine(pos);
        //go2.position = new Vec2(0, 0);
        Console.WriteLine(go2.position);
        Console.WriteLine(go2.position);
        //Console.WriteLine(go2);

        //go2.scale = new Vec2(30, 100);
        /*Console.WriteLine(go2.position + new Vec2(10,10));

        go2.position += new Vec2(500, 500);
        Console.WriteLine(go2.position);*/

    }
}

