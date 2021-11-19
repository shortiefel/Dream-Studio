using System;

public class PlayButton : MonoBehaviour
{
    /*public override void Start()
    {
        Console.WriteLine("going in start play");
    }*/

    public override void Update()
    {
        //Console.WriteLine(Input.GetMousePosition());
    }

    public override void OnMouseOver()
    {
        Console.WriteLine(Input.GetMousePosition());
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            Debug.Log("Play");
            
            //SceneManager.LoadScene("NewGame");
        }
    }
}