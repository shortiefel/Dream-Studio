using System;

public class HighScore : MonoBehaviour
{
    public override void Start()
    {
        int t = GetSavedData("CurrentScore");
        GetComponent<Text>().text = t < 10 ? "0" + t.ToString() : t.ToString();
    }

}


