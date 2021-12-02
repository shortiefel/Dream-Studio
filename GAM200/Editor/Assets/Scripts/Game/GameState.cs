
public class GameState : MonoBehaviour
{
    bool pauseState;
    bool drawModeBool;
    int highscore;
    bool shouldEnd;

    Text highscoreText;

    public override void Start()
    {
        pauseState = false;
        drawModeBool = false;
        highscore = 0;
        shouldEnd = false;

        highscoreText = GameObject.Find("CounterText").GetComponent<Text>();
    }

    public override void Update()
    {
        highscoreText.text = highscore.ToString();
        if (shouldEnd)
        {
            //SceneManager.LoadScene();
        }
    }

    public void IncrementScore()
    {
        highscore++;
    }
    public int GetScore()
    {
        return highscore;
    }

    public void InvertPause()
    {
        pauseState = !pauseState;
    }
    public bool GetPause()
    {
        return pauseState;
    }

    public void SetDrawMode(bool _state)
    {
        drawModeBool = _state;
    }
    public bool GetDrawMode()
    {
        return drawModeBool;
    }

    public bool ShouldDraw()
    {
        return !pauseState && drawModeBool;
    }
}