using System;

public class QuitButton : MonoBehaviour
{
    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            Console.WriteLine("Quit selected");
            Application.Quit();
        }
    }
}