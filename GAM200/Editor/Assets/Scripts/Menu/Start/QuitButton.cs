using System;

public class QuitButton : MonoBehaviour
{
    Text text;
    Texture texture;

    public override void Start()
    {
        Console.WriteLine("going in start play");

        text = GetComponent<Text>();
        texture = GameObject.Find("Quitbtn").GetComponent<Texture>();
    }

    public override void OnMouseEnter()
    {
        text.color = new Color(0f, 0f, 0f);
        texture.color = new Color(1f, 1f, 1f);
    }

    public override void OnMouseOver()
    {
        //Console.WriteLine("Quit selected");
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            Application.Quit();
        }
    }

    public override void OnMouseExit()
    {
        text.color = new Color(1f, 1f, 1f);
        texture.color = new Color(0f, 0f, 0f);
    }
}