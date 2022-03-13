
public class GameState : MonoBehaviour
{
    bool pauseState;
    bool drawModeBool;
    int highscore;

    public bool shouldEnd;

    //Text highscoreText;

    CameraMovement camMovement;
    ButtonRoad buttonRoad;

    MoneySystem moneySystem;

    PlacementManager placementManager;


    //bool gameOverBool;

    //float previousTimeScale;

    public override void Start()
    {
        pauseState = false;
        drawModeBool = false;
        highscore = 0;
        shouldEnd = false;
        //gameOverBool = false;

        //GameObject go1 = GameObject.Find("CounterText");
        //if (go1 != null)
        //    highscoreText = go1.GetComponent<Text>();

        camMovement = GameObject.Find("Camera").GetComponent<CameraMovement>();
        buttonRoad = GameObject.Find("ButtonRoad").GetComponent<ButtonRoad>();

        moneySystem = GameObject.Find("MoneyText").GetComponent<MoneySystem>();

        placementManager = GameObject.Find("PlacementManager").GetComponent<PlacementManager>();

        //previousTimeScale = 1f;
    }

    public override void Update()
    {
        //if (highscoreText != null)
        //    highscoreText.text = highscore.ToString();

        if (shouldEnd)
        {
            shouldEnd = false;

            GameOver();
        }
        else
        {
            //if (!gameOverBool)
            //{
            //    if (highscore >= 80)
            //    {
            //        shouldEnd = true;
            //        gameOverBool = true;
            //    }
            //}
        }
        //--------------------------
        //Cheat code
        //if (Input.GetKeyDown(KeyCode.L))
        //{
        //    GameOver();
        //}
        if (Input.GetKeyDown(KeyCode.P) && Input.GetKey(KeyCode.Shift))
        {
            IncrementScore();
        }
        //-------------------------
    }

    void GameOver ()
    {
        //SceneManager.LoadScene("GameOver");
        if (camMovement.toZoomLose) return;
        camMovement.toZoomLose = true;

        Time.timeScale = 0f;
        TrySetHighscore();
    }

    public void SetLoseHouse(Vector2 _pos)
    {
        camMovement.SetTargetPosition(_pos);
    }


    private void IncrementScore()
    {
        highscore++;

        if (highscore == 10)
        {
            buttonRoad.RevealTraffic();
        }

        else if (highscore == 15)
        {
            buttonRoad.RevealERP();
        }
    }

    public void ReachedDestination()
    {
        Debug.Log("Reached destination ");
        IncrementScore();
    }

    public void MissedDestinationTime()
    {
        //highscore--;
        moneySystem.MinusMoney(100);
        Debug.Log("Missed a destination ");
    }

    public void ExpandGrid()
    {
        placementManager.placementGrid.Expand();
    }

    public int GetScore()
    {
        return highscore;
    }

    //public void IncrementHighscore()
    //{
    //    highscore++;
    //}
    public int GetHighscore()
    {
        return highscore;
    }

    private void TrySetHighscore()
    {
        Debug.Log("TrySetHighscore " + highscore + " vs og: " + GetHighscore("HighScore"));
        if (highscore > GetHighscore("HighScore"))
        {
            SetHighscore(highscore, "HighScore");
        }
        SetHighscore(highscore, "CurrentScore");
    }

    public float GetTimeScaleToRestore()
    {
        return TimeSystem.previousTimeScale;
    }
    public void InvertPause()
    {
        pauseState = !pauseState;

        if (pauseState) Time.timeScale = 0f;
        else Time.timeScale = 1f;
    }

    public void SetPause(bool state)
    {
        pauseState = state;
        if (state) Time.timeScale = 0f;
        else Time.timeScale = TimeSystem.previousTimeScale;
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