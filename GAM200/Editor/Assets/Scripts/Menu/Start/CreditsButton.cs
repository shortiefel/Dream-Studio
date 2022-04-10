using System;

public class CreditsButton : MonoBehaviour
{
    Text text;
    Texture texture;
    private AudioSource btnClick;
    public override void Start()
    {
        text = GetComponent<Text>();
        texture = GameObject.Find("Creditsbtn").GetComponent<Texture>();
        text.color = new Color(0f, 0f, 0f);
        texture.color = new Color(1f, 1f, 1f);
        btnClick = GetComponent<AudioSource>();
    }

    public override void OnMouseEnter()
    {
        btnClick.Play();
        text.color = new Color(1f, 1f, 1f);
        texture.color = new Color(1f, 0.5f, 0f);
    }

    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            Console.WriteLine("Credit selected");
            SceneManager.LoadScene("Credits");
        }
    }

    public override void OnMouseExit()
    {
        text.color = new Color(0f, 0f, 0f);
        texture.color = new Color(1f, 1f, 1f);
    }
}