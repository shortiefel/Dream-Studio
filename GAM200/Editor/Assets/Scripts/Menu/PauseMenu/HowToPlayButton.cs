using System;

public class HowToPlayButton : MonoBehaviour
{
    public override void Start()
    {
        Console.WriteLine("going into howtoplay scene");
    }

    public override void Update()
    {

    }

    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            Console.WriteLine("howtoplay selected");
        }
    }
}