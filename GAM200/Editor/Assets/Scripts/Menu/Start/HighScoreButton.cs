using System;

public class HighScoreButton : MonoBehaviour
{
    Text text;
    Texture texture;

    public override void Start()
    {
        Console.WriteLine("going into highscore scene");

        text = GetComponent<Text>();
        texture = GameObject.Find("HighScorebtn").GetComponent<Texture>();
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
            Console.WriteLine("Highscore selected");
            SceneManager.LoadScene("HighScore");
        }
    }

    public override void OnMouseExit()
    {
        text.color = new Color(1f, 1f, 1f);
        texture.color = new Color(0f, 0f, 0f);
    }
}