using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class Test : MonoBehaviour
{
    //Transform transform;
    public int health = 10;

    public override void Init()
    {
        //gameObject.transform = new Transform(new Vec2(100, 200), new Vec2(30, 70));
        Console.WriteLine(gameObject.transform.position);
        //gameObject.transform.position = new Vec2(500, -100);

        /*GameObject go2 = new GameObject();
        go2.entityId = 1;
        go2.transform = new Transform(new Vec2(500, 200), new Vec2(100, 20));*/
        //Console.WriteLine(this.GetType());

        Transform t = GetComponent<Transform>();
        //gameObject.CheckString();
        Console.WriteLine(t);
        //gameObject.transform.position = mew Vec2(400, 100);

    }

    public void ShowHealth()
    {
        Console.WriteLine("Health: " + health);
    }

    public override void OnEnable() 
    {
        Console.WriteLine("new enable");
    }
}

