using System;

public class ResumeButton : MonoBehaviour
{
    public override void Start()
    {
        Console.WriteLine("going into game scene");
    }

    public override void Update()
    {

    }

    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            Console.WriteLine("Resume selected");
        }
    }
}