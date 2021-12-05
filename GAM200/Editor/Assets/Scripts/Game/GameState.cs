
public class GameState : MonoBehaviour
{
    bool pauseState;
    bool drawModeBool;
    int highscore;

    public bool shouldEnd;

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
            shouldEnd = false;
            TrySetHighscore();
            SceneManager.LoadScene("GameOver");
        }
        //--------------------------
        //Cheat code
        if (Input.GetKeyDown(KeyCode.L))
        {
            SceneManager.LoadScene("GameOver");
        }
        if (Input.GetKeyDown(KeyCode.P))
        {
            IncrementScore();
        }
        //-------------------------
    }


    public void IncrementScore()
    {
        highscore++;
    }
    public int GetScore()
    {
        return highscore;
    }

    public void IncrementHighscore()
    {
        highscore++;
    }
    public int GetHighscore()
    {
        return highscore;
    }

    private void TrySetHighscore()
    {
        if (highscore > GetHighscore("HighScore"))
        {
            SetHighscore(highscore, "HighScore");
        }
        SetHighscore(highscore, "CurrentScore");
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