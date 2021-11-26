using System;
public class PauseQuitButton : MonoBehaviour
{
    public override void Start()
    {
        Console.WriteLine("going into Quit scene");
    }

    public override void Update()
    {

    }

    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            Console.WriteLine("Quit selected");
        }
    }
}