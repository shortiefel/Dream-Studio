
enum Cycle
{
    Day = 0,
    Night
}
public class GameState : MonoBehaviour
{
    bool pauseState;
    bool drawModeBool;
    int highscore;

    public bool shouldEnd;

    //Text highscoreText;
    Text dayText;
    CameraMovement camMovement;
    ButtonRoad buttonRoad;

    MoneySystem moneySystem;

    PlacementManager placementManager;

    private float dayTimer;
    private float dayCycle;
    private float nightCycle;
    private int dayCounter;

    UI overlayNightTexture;
    float overlayAlpha;

    Cycle cycle;

    ButtonStore store;
    GameObject receipt;

    //bool gameOverBool;

    //float previousTimeScale;

    bool allowPause;

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

        GameObject buttonRoadGO = GameObject.Find("ButtonRoad");
        if (buttonRoadGO != null)
            buttonRoad = buttonRoadGO.GetComponent<ButtonRoad>();

        GameObject moneySystemGO = GameObject.Find("MoneyText");
        if (moneySystemGO != null)
            moneySystem = moneySystemGO.GetComponent<MoneySystem>();

        placementManager = GameObject.Find("PlacementManager").GetComponent<PlacementManager>();

        GameObject buttonStoreGo = GameObject.Find("Storebtn");
        if (buttonStoreGo != null)
            store = buttonStoreGo.GetComponent<ButtonStore>();

        //previousTimeScale = 1f;
        dayCounter = 1;
        dayText = GameObject.Find("DayClock").GetComponent<Text>();
        dayText.text = "Day " +dayCounter.ToString();

        dayTimer = 0f;
        dayCycle = 120f;

        nightCycle = 100f;

        cycle = Cycle.Day;

        overlayAlpha = 0f;
        overlayNightTexture = GameObject.Find("OverlayNight").GetComponent<UI>();

        receipt = GameObject.Find("Receipt");
        if (receipt != null)
        {
            Disable<Transform>(receipt.transform);
        }

        allowPause = true;
    }

    public override void Update()
    {
        //if (highscoreText != null)
        //    highscoreText.text = highscore.ToString();

        if (receipt != null)
        {
            dayTimer += Time.deltaTime;

            if (dayTimer >= nightCycle)
            {
                overlayAlpha += 0.01f;
                if (overlayAlpha > 0.5f) overlayAlpha = 0.7f;
                else
                    overlayNightTexture.alpha = overlayAlpha;

                if (cycle == Cycle.Day)
                    cycle = Cycle.Night;
            }

            if (dayTimer >= dayCycle)
            {
                Enable<Transform>(receipt.transform);
                SetPause(true);
                moneySystem.TaxMoney();
                dayTimer = 0f;
                //dayCounter++;
                //dayText.text = "Day " + dayCounter.ToString();
                //Moved to gameState gameover
            }
        }

        //if (shouldEnd)
        //{
        //    shouldEnd = false;

        //    GameOver();
        //}
        //else
        //{
        //    //if (!gameOverBool)
        //    //{
        //    //    if (highscore >= 80)
        //    //    {
        //    //        shouldEnd = true;
        //    //        gameOverBool = true;
        //    //    }
        //    //}
        //}
        //--------------------------
        //Cheat code
        if (Input.GetKeyDown(KeyCode.L) && Input.GetKey(KeyCode.Shift))
        {
            GameOver();
        }
        if (Input.GetKeyDown(KeyCode.P) && Input.GetKey(KeyCode.Shift))
        {
            IncrementScore();
        }

        if (Input.GetKeyDown(KeyCode.R) && Input.GetKey(KeyCode.Shift))
        {
            Enable<Transform>(receipt.transform);
            SetPause(true);
            moneySystem.TaxMoney();
        }
        //-------------------------
    }

    public void GameOver ()
    {
        //if (camMovement.toZoomLose) return;
        //camMovement.toZoomLose = true;
        dayCounter++;
        dayText.text = "Day " + dayCounter.ToString();

        if (shouldEnd)
        {
            Time.timeScale = 0f;
            TrySetHighscore();

            Time.timeScale = 1f;
            SceneManager.LoadScene("GameOver");
        }
            
    }

    public void SetLoseHouse(Vector2 _pos)
    {
        camMovement.SetTargetPosition(_pos);
    }


    private void IncrementScore()
    {
        highscore++;

        if (highscore == 1)
        {
            store.RevealStore();
        }

        if (highscore == 10)
        {
            buttonRoad.RevealTraffic();
        }

        else if (highscore == 15)
        {
            buttonRoad.RevealERP();
        }
    }

    public void ReachedDestination(BuildingType bt)
    {
        //Debug.Log("Reached destination ");
        switch (bt)
        {
            case BuildingType.Office:
                moneySystem.AddMoney(25, MoneySource.DestOffice);
                break;

            case BuildingType.Hospital:
                moneySystem.AddMoney(25, MoneySource.DestHospital);
                break;

            case BuildingType.Park:
                moneySystem.AddMoney(25, MoneySource.DestPark);
                break;

            case BuildingType.Mall:
                moneySystem.AddMoney(25, MoneySource.DestMall);
                break;
        }
        
        IncrementScore();
    }

    public void MissedDestinationTime(BuildingType bt)
    {
        //highscore--;
        switch (bt)
        {
            case BuildingType.Office:
                moneySystem.MinusMoney(100, MoneySource.DestOffice);
                break;

            case BuildingType.Hospital:
                moneySystem.MinusMoney(100, MoneySource.DestHospital);
                break;

            case BuildingType.Park:
                moneySystem.MinusMoney(100, MoneySource.DestPark);
                break;

            case BuildingType.Mall:
                moneySystem.MinusMoney(100, MoneySource.DestMall);
                break;
        }
        
        Debug.Log("Missed a destination ");
    }

    public void ExpandGrid()
    {
        //Debug.Log("Haoneienri");
        placementManager.placementGrid.Expand();
        camMovement.Expand();

        buttonRoad.SwitchTabRoad(false);
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
        //Debug.Log("TrySetHighscore " + dayCounter + " vs og: " + GetSavedData("HighScore"));
        if (dayCounter > GetSavedData("HighScore"))
        {
            SetSavedData(dayCounter, "HighScore");
        }
        SetSavedData(dayCounter, "CurrentScore");
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

    public bool AllowPause()
    {
        return allowPause;
    }

    public void SetAllowPause(bool type)
    {
        allowPause = type;
    }

    public void SetDrawMode(bool _state)
    {
        drawModeBool = _state;
    }
    public bool GetDrawMode()
    {
        return drawModeBool;
    }

    //public bool ShouldDraw()
    //{
    //    return !pauseState && drawModeBool;
    //}

    //Return true if night
    public bool GetNight()
    {
        return cycle == Cycle.Night;
    }

    public void ResetDay()
    {
        cycle = Cycle.Day;
        overlayAlpha = 0.0f;
        overlayNightTexture.alpha = overlayAlpha;
    }
}