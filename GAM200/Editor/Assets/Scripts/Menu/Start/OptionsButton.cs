using System;

public class MenuOptionsButton : MonoBehaviour
{
    Text text;
    Texture texture;

    public override void Start()
    {
        Console.WriteLine("going into options scene");

        text = GetComponent<Text>();
        texture = GameObject.Find("MenuOptionsBtn").GetComponent<Texture>();
        if (texture == null)
            Debug.Log("hello");
        else
            Debug.Log("goodbye");
    }

    public override void OnMouseEnter()
    {
        text.color = new Color(0f, 0f, 0f);
        texture.color = new Color(1f, 1f, 1f);
    }

    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            Console.WriteLine("Options selected");
            SceneManager.LoadScene("Options");
        }
    }

    public override void OnMouseExit()
    {
        text.color = new Color(1f, 1f, 1f);
        texture.color = new Color(0f, 0f, 0f);
    }
}