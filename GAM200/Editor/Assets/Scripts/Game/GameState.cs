﻿
public class GameState : MonoBehaviour
{
    bool pauseState;
    bool drawModeBool;
    int highscore;

    public bool shouldEnd;

    Text highscoreText;

    CameraMovement camMovement;

    public override void Start()
    {
        pauseState = false;
        drawModeBool = false;
        highscore = 0;
        shouldEnd = false;

        highscoreText = GameObject.Find("CounterText").GetComponent<Text>();

        camMovement = GameObject.Find("Camera").GetComponent<CameraMovement>();
    }

    public override void Update()
    {
        highscoreText.text = highscore.ToString();
        if (shouldEnd)
        {
            shouldEnd = false;

            GameOver();
        }
        //--------------------------
        //Cheat code
        if (Input.GetKeyDown(KeyCode.L))
        {
            GameOver();
        }
        if (Input.GetKeyDown(KeyCode.P))
        {
            IncrementScore();
        }
        //-------------------------
    }

    void GameOver ()
    {
        //SceneManager.LoadScene("GameOver");
        if (camMovement.toZoom) return;
        camMovement.toZoom = true;

        Time.timeScale = 0f;
        TrySetHighscore();
    }

    public void SetLoseHouse(Vector2 _pos)
    {
        camMovement.SetTargetPosition(_pos);
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