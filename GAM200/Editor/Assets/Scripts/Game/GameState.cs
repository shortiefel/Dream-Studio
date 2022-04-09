
enum Cycle
{
    Day = 0,
    Night
}
public class GameState : MonoBehaviour
{
    bool pauseState;
    //bool drawModeBool;
    int highscore;

    public bool shouldEnd;

    //Text highscoreText;
    Text dayText;
    CameraMovement camMovement;
    ButtonRoadTab buttonRoad;

    MoneySystem moneySystem;

    PlacementManager placementManager;

    public float dayTimer;
    private float dayCycle;
    private float nightCycle;
    private int dayCounter;

    Texture overlayNightUI;
    float overlayAlpha;

    Cycle cycle;

    UI TimerIcon;
    //ButtonStore store;
    GameObject receipt;
    Text clockTimer;
    Text AmPm;
    Text moneyText;
    Text dayClock;


    //bool gameOverBool;

    //float previousTimeScale;

    bool allowPause;

    static public int addMoneyValue;
    static public int minusMoneyValue;

    public override void Start()
    {
        pauseState = false;
        //drawModeBool = false;
        highscore = 0;
        shouldEnd = false;
        //gameOverBool = false;

        //GameObject go1 = GameObject.Find("CounterText");
        //if (go1 != null)
        //    highscoreText = go1.GetComponent<Text>();

        camMovement = GameObject.Find("Camera").GetComponent<CameraMovement>();
        clockTimer = GameObject.Find("Clock").GetComponent<Text>();
        AmPm = GameObject.Find("AMPM").GetComponent<Text>();
        moneyText = GameObject.Find("MoneyText").GetComponent<Text>();
        dayClock = GameObject.Find("DayClock").GetComponent<Text>();

        //GameObject overlayNightGo = GameObject.Find("OverlayNight");
        //if (overlayNightGo != null)
        //    overlayNight = overlayNightGo.GetComponent<Transform>();
        TimerIcon = GameObject.Find("TimerIcon").GetComponent<UI>();

        GameObject buttonRoadGO = GameObject.Find("DisplayRoadBtn");
        if (buttonRoadGO != null)
            buttonRoad = buttonRoadGO.GetComponent<ButtonRoadTab>();

        GameObject moneySystemGO = GameObject.Find("MoneyText");
        if (moneySystemGO != null)
            moneySystem = moneySystemGO.GetComponent<MoneySystem>();

        placementManager = GameObject.Find("PlacementManager").GetComponent<PlacementManager>();

        //GameObject buttonStoreGo = GameObject.Find("Storebtn");
        //if (buttonStoreGo != null)
        //    store = buttonStoreGo.GetComponent<ButtonStore>();

        //previousTimeScale = 1f;
        dayCounter = 1;
        dayText = GameObject.Find("DayClock").GetComponent<Text>();
        dayText.text = "Day " +dayCounter.ToString();

        dayTimer = 0f;
        dayCycle = 144f;

        nightCycle = 72f;
        //nightCycle = 10f;

        cycle = Cycle.Day;

        overlayAlpha = 0f;
        overlayNightUI = GameObject.Find("OverlayNight").GetComponent<Texture>();
        overlayNightUI.alpha = 0;


        receipt = GameObject.Find("Receipt");
        if (receipt != null)
        {
            Disable<Transform>(receipt.transform);
        }

        allowPause = true;

        addMoneyValue = 25;
        minusMoneyValue = 100;
    }

    public override void Update()
    {
        //if (highscoreText != null)
        //    highscoreText.text = highscore.ToString();
        //Debug.Log(allowPause);
        if (receipt != null)
        {
            dayTimer += Time.deltaTime;

            if (dayTimer >= nightCycle)
            {
                TimerIcon.ChangeTexture("Game/UI/Clock_Night");
                clockTimer.color = new Color(1f, 1f, 1f);
                AmPm.color = new Color(1f, 1f, 1f);
                moneyText.color = new Color(1f, 1f, 1f);
                dayClock.color = new Color(1f, 1f, 1f);
                overlayAlpha += 0.01f;
                if (overlayAlpha > 0.6f) overlayAlpha = 0.6f;
                else
                    overlayNightUI.alpha = overlayAlpha;

                if (cycle == Cycle.Day)
                    cycle = Cycle.Night;
            }

            if (dayTimer >= dayCycle)
            {
                Enable<Transform>(receipt.transform);
                SetPause(true);
                moneySystem.TaxMoney();
                dayTimer = 0f;
                TimerIcon.ChangeTexture("Game/UI/Clock_Day");
                clockTimer.color = new Color(0f, 0f, 0f);
                AmPm.color = new Color(0f, 0f, 0f);
                moneyText.color = new Color(0f, 0f, 0f);
                dayClock.color = new Color(0f, 0f, 0f);
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

    public bool GameOver ()
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

            return true;
        }

        return false;
    }

    public void SetLoseHouse(Vector2 _pos)
    {
        camMovement.SetTargetPosition(_pos);
    }


    private void IncrementScore()
    {
        highscore++;

        //if (highscore == 1)
        //{
        //    store.RevealStore();
        //    SetAllowPause(false);
        //}

        if (highscore == 10)
        {
            buttonRoad.RevealTraffic();
            SetAllowPause(false);
        }

        else if (highscore == 15)
        {
            buttonRoad.RevealERP();
            SetAllowPause(false);
        }
    }

    public void ReachedDestination(BuildingType bt)
    {
        //Debug.Log("Reached destination ");
        switch (bt)
        {
            case BuildingType.Office:
                //moneySystem.AddMoney(addMoneyValue, MoneySource.DestOffice);
                MoneySystem.AddMoney(addMoneyValue, MoneySource.Ignore);
                break;

            case BuildingType.Hospital:
                //moneySystem.AddMoney(addMoneyValue, MoneySource.DestHospital);
                MoneySystem.AddMoney(addMoneyValue, MoneySource.Ignore);
                break;

            case BuildingType.Park:
                //moneySystem.AddMoney(addMoneyValue, MoneySource.DestPark);
                MoneySystem.AddMoney(addMoneyValue, MoneySource.Ignore);
                break;

            case BuildingType.Mall:
                //moneySystem.AddMoney(addMoneyValue, MoneySource.DestMall);
                MoneySystem.AddMoney(addMoneyValue, MoneySource.Ignore);
                break;

            case BuildingType.PoliceStation:
                //moneySystem.AddMoney(addMoneyValue, MoneySource.DestPolice);
                MoneySystem.AddMoney(addMoneyValue, MoneySource.Ignore);
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
                //moneySystem.MinusMoney(minusMoneyValue, MoneySource.DestOffice);
                MoneySystem.MinusMoney(minusMoneyValue, MoneySource.Ignore);
                break;

            case BuildingType.Hospital:
                //moneySystem.MinusMoney(minusMoneyValue, MoneySource.DestHospital);
                MoneySystem.MinusMoney(minusMoneyValue, MoneySource.Ignore);
                break;

            case BuildingType.Park:
                //moneySystem.MinusMoney(minusMoneyValue, MoneySource.DestPark);
                MoneySystem.MinusMoney(minusMoneyValue, MoneySource.Ignore);
                break;

            case BuildingType.Mall:
                //moneySystem.MinusMoney(minusMoneyValue, MoneySource.DestMall);
                MoneySystem.MinusMoney(minusMoneyValue, MoneySource.Ignore);
                break;

            case BuildingType.PoliceStation:
                //moneySystem.MinusMoney(minusMoneyValue, MoneySource.DestPolice);
                MoneySystem.MinusMoney(minusMoneyValue, MoneySource.Ignore);
                break;
        }
        
        Debug.Log("Missed a destination ");
    }

    public void ExpandGrid()
    {
        //Debug.Log("Haoneienri");
        placementManager.placementGrid.Expand();
        camMovement.Expand();
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

    //public float GetTimeScaleToRestore()
    //{
    //    return TimeSystem.previousTimeScale;
    //}
    //public void InvertPause()
    //{
    //    pauseState = !pauseState;
    //
    //    if (pauseState) Time.timeScale = 0f;
    //    else Time.timeScale = 1f;
    //}

    public void SetPause(bool state)
    {
        pauseState = state;
        if (state) TimeSystem.PauseTime();
        else TimeSystem.ResumeTime();
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

    //public void SetDrawMode(bool _state)
    //{
    //    drawModeBool = _state;
    //}
    //public bool GetDrawMode()
    //{
    //    return drawModeBool;
    //}

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
        overlayNightUI.alpha = overlayAlpha;
    }

    public int getDayCounter()
    {
        return dayCounter;
    }
}