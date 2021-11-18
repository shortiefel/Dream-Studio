using System;

public class PlayButton : MonoBehaviour
{
    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            Debug.Log("Play");
            Console.WriteLine(Input.GetMousePosition());
            //SceneManager.LoadScene("NewGame");
        }
    }
}