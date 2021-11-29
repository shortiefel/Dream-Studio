using System;

public class PlayButton : MonoBehaviour
{
    public override void Start()
    {
        Console.WriteLine("going in start play");
    }

    public override void OnMouseOver()
    {
        //Console.WriteLine(Input.GetMousePosition());
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            Console.WriteLine("Play");
            SceneManager.LoadScene("NewGame");
        }
    }
}