using System;

public class HighScore : MonoBehaviour
{
    public override void Start()
    {
        GetComponent<Text>().text = GetHighscore("HighScore").ToString();
    }

}


