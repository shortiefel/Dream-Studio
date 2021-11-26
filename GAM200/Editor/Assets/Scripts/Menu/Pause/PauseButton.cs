using System;

public class PauseButton : MonoBehaviour
{
    public override void Start()
    {
        Console.WriteLine("going into pause scene");
    }

    public override void Update()
    {

    }

    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            Console.WriteLine("Pause selected");
        }
    }
}
