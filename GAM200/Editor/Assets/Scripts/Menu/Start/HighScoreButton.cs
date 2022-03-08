using System;

public class HighScoreButton : MonoBehaviour
{
    UI HighScorebtn;

    public override void Start()
    {
        HighScorebtn = GetComponent<UI>();
    }

    public override void OnMouseEnter()
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

    public override void OnMouseExit()
    {

    }
}