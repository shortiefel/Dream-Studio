using System;

public class CurrentScore : MonoBehaviour
{
    public override void Start()
    {
        GetComponent<Text>().text = GetSavedData("CurrentScore").ToString();
        SetSavedData(0, "CurrentScore");
    }

}


