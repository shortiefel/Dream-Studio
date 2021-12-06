using System;

public class PlayButton : MonoBehaviour
{
    Text text;
    Texture texture;
    Camera cam;
    public override void Start()
    {
        Console.WriteLine("going in start play");

        text = GetComponent<Text>();
        texture = GameObject.Find("Playbtn").GetComponent<Texture>();
        cam = GameObject.Find("Camera").GetComponent<Camera>();
    }

    public override void OnMouseEnter()
    {
        text.color = new Color(0f, 0f, 0f);
        texture.color = new Color(1f, 1f, 1f);
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

    public override void OnMouseExit()
    {
        text.color = new Color(1f, 1f, 1f);
        texture.color = new Color(0f, 0f, 0f);
    }
}