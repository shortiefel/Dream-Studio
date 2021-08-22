using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class Test : MonoBehaviour
{
    //Transform transform;
    public int health = 10;

    /*public Test()
    {
        health = 5;
        Console.WriteLine("Test constructor!");
    }*/

    public void ShowHealth()
    {
        Console.WriteLine("Health: " + health);
    }

    public override void OnEnable() 
    {
        Console.WriteLine("new enable");
    }
}

