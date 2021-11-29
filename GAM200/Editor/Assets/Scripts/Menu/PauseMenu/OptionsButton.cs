using System;

public class OptionsButton : MonoBehaviour
{
    public override void Start()
    {
        Console.WriteLine("going into Options scene");
    }

    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            Console.WriteLine("Options selected");
        }
    }
}