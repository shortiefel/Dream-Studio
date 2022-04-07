using System;

public class HighScore : MonoBehaviour
{
    private AudioSource Victory;
    public override void Start()
    {
        Victory = GetComponent<AudioSource>();
        int t = GetSavedData("CurrentScore");
        GetComponent<Text>().text = t < 10 ? "0" + t.ToString() : t.ToString();
    }
    public override void Update()
    {
        Victory.Play();
    }
}


