using System;

public class PlayButton : MonoBehaviour
{
    Text text;
    Texture texture;
    Camera cam;
    private AudioSource btnClick;
    public override void Start()
    {
        Console.WriteLine("going in start play");

        text = GetComponent<Text>();
        texture = GameObject.Find("Playbtn").GetComponent<Texture>();
        cam = GameObject.Find("Camera").GetComponent<Camera>();
        btnClick = GetComponent<AudioSource>();
        text.color = new Color(0f, 0f, 0f);
        texture.color = new Color(1f, 1f, 1f);
    }

    public override void OnMouseEnter()
    {
        text.color = new Color(1f, 1f, 1f);
        texture.color = new Color(1f, 0.5f, 0f);
    }

    public override void OnMouseOver()
    {
        //Console.WriteLine(Input.GetMousePosition());
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            btnClick.Play();
            Console.WriteLine("Play");
            SceneManager.LoadScene("TutorialNew");
        }
    }

    public override void OnMouseExit()
    {
        text.color = new Color(0f, 0f, 0f);
        texture.color = new Color(1f, 1f, 1f);
    }
}