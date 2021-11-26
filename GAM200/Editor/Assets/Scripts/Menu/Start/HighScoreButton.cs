using System;

public class HighScoreButton : MonoBehaviour
{
    public override void Start()
    {
        Console.WriteLine("going into highscore scene");
    }

    public override void Update()
    {

    }

    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            Console.WriteLine("Highscore selected");
            SceneManager.LoadScene("HighScore");
        }
    }
}