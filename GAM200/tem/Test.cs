using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


public class Test : MonoBehaviour
{
    public int health = 10;
    public Test()
    {
        health = 5;
    }
    public void Damage()
    {
        health--;
        Console.WriteLine("is damaging!");
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

