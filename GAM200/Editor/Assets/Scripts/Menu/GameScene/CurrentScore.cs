using System;

public class CurrentScore : MonoBehaviour
{
    public override void Start()
    {
        GetComponent<Text>().text = GetHighscore("CurrentScore").ToString();
        SetHighscore(0, "CurrentScore");
    }

}


