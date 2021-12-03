using System;

public class QuitButton : MonoBehaviour
{
    public override void OnMouseOver()
    {
        Console.WriteLine("Quit selected");
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            Application.Quit();
        }
    }
}