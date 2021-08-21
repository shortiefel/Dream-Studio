using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class mySampleClass
{
    public mySampleClass()
    {
        // This is the no parameter constructor method.  
        // First Constructor  
    }
    public mySampleClass(int Age)
    {
        // This is the constructor with one parameter.  
        // Second Constructor  
    }
    public mySampleClass(int Age, string Name)
    {
        // This is the constructor with two parameters.  
        // Third Constructor  
    }
}

public class Test : MonoBehaviour
{
    public int health = 10;

    public Test()
    {
        health = 5;
        Console.WriteLine("Test constructor!");
    }

    public override void Init()
    {
        health--;
        Console.WriteLine("init Test!");
    }

    public override void Update()
    {
        
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

