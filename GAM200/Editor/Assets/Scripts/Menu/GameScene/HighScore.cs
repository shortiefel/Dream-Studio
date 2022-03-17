using System;

public class HighScore : MonoBehaviour
{
    public override void Start()
    {
        GetComponent<Text>().text = GetSavedData("HighScore").ToString();
    }

}


