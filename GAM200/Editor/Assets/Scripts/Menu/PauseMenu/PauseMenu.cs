using System;

public class PauseMenu : MonoBehaviour
{
    GameObject resume;
    GameObject howToPlay;
    
    //GameObject options;
    GameObject pauseQuit;
    

    GameObject resumeBtn;
    //GameObject menuBtn;
    //GameObject optionsBtn;
    GameObject howToPlayBtn;
    GameObject pauseQuitBtn;

    GameObject pauseBG;
    GameObject HowToBG;

    GameObject quitBG;
    GameObject areYouSure;
    GameObject quitYes;
    GameObject quitNo;

    Transform settingBtn;

    //Vector2 resumePosition;
    //Vector2 resumeTextPosition;
    //Vector2 htpPosition;
    //Vector2 htpTextPosition;
    //Vector2 quitPosition;
    //Vector2 quitTextPosition;
    //Vector2 bgPosition;
    //
    //Vector2 outsidePosition;

    //bool pauseState;
    GameState gameState;

    UI texture;

    Transform displayArrow;
    Transform displayArrowWhite;


    //Transform timerButton;
    //Transform storeButton;

    //bool stopTime;
    //float stopTimer;

    //ButtonRoad buttonRoad;
    //ButtonStore buttonStore;

    /*public bool GetPause()
    {
        return pauseState;
    }*/

    CombinedUI combinedUI;

    //Transform moneyText;
    //Transform coinSymbol;

    public override void Start()
    {
        //GameObject go3 = GameObject.Find("MoneyText");
        //if (go3 != null)
        //    moneyText = go3.GetComponent<Transform>();
        //
        //coinSymbol = GameObject.Find("CoinBag").GetComponent<Transform>();

        texture = GetComponent<UI>();
        texture.color = new Color(0f, 0f, 0f);

        pauseBG = GameObject.Find("PauseBG");
        //bgPosition = pauseBG.transform.position;
        HowToBG = GameObject.Find("HowToBG");

        resume = GameObject.Find("ResumeText");
        howToPlay = GameObject.Find("HowToText");
        //menuText = GameObject.Find("MenuText");
        //options = GameObject.Find("OptionText");
        pauseQuit = GameObject.Find("QuitText");

        //resumeTextPosition = resume.transform.position;
        //htpTextPosition = howToPlay.transform.position;
        //quitTextPosition = pauseQuit.transform.position;

        resumeBtn = GameObject.Find("ResumeBtn");
        //menuBtn = GameObject.Find("MenuBtn");
        //optionsBtn = GameObject.Find("Optionsbtn");
        howToPlayBtn = GameObject.Find("howToPlayBtn");
        pauseQuitBtn = GameObject.Find("QuitBtn");

        //resumePosition = resumeBtn.transform.position;
        //htpPosition = howToPlayBtn.transform.position;
        //quitPosition = pauseQuitBtn.transform.position;

        quitBG = GameObject.Find("QuitBG");
        areYouSure = GameObject.Find("AreYouSureText");
        quitYes = GameObject.Find("QuitYesBtn");
        quitNo = GameObject.Find("QuitNoBtn");


        settingBtn = GameObject.Find("settingBtn").GetComponent<Transform>();

        //outsidePosition = new Vector2(-200, 0);


        Disable<Transform>(pauseBG.transform);
        Disable<Transform>(HowToBG.transform);

        Disable<Transform>(resume.transform);
        Disable<Transform>(howToPlay.transform);
       // Disable<Transform>(menuText.transform);
        //Disable<Transform>(options.transform);
        Disable<Transform>(pauseQuit.transform);

        Disable<Transform>(resumeBtn.transform);
        //Disable<Transform>(menuBtn.transform);
        //Disable<Transform>(optionsBtn.transform);
        Disable<Transform>(howToPlayBtn.transform);
        Disable<Transform>(pauseQuitBtn.transform);

        Disable<Transform>(quitBG.transform);
        Disable<Transform>(areYouSure.transform);
        Disable<Transform>(quitYes.transform);
        Disable<Transform>(quitNo.transform);

        gameState = GameObject.Find("GameManager").GetComponent<GameState>();

        //GameObject buttonRoadGO = GameObject.Find("ButtonRoad");
        //if (buttonRoadGO != null)
        //    buttonRoad = buttonRoadGO.GetComponent<ButtonRoad>();
        //GameObject buttonStoreGO = GameObject.Find("Storebtn");
        //if (buttonStoreGO != null)
        //    buttonStoreSymbol = buttonStoreGO.GetComponent<Tranform>();


        displayArrow = GameObject.Find("Displaybtn").GetComponent<Transform>();
        displayArrowWhite = GameObject.Find("DisplaybtnWhite").GetComponent<Transform>();

        //GameObject timerButtonGO = GameObject.Find("TimerIcon");
        //if (timerButtonGO != null)
        //    timerButton = timerButtonGO.GetComponent<Transform>();
        //GameObject storeButtonGO = GameObject.Find("Storebtn");
        //if (storeButtonGO != null)
        //    storeButton = storeButtonGO.GetComponent<Transform>();

        GameObject combinedUIGO = GameObject.Find("CombinedUI");
        if (combinedUIGO != null)
            combinedUI = GameObject.Find("CombinedUI").GetComponent<CombinedUI>();


        //stopTime = false;
        //stopTimer = 0f;


        //pauseBG.transform.position = new Vector2(bgPosition.x - 200f, pauseBG.transform.position.y);
        //
        //resume.transform.position = new Vector2(resumeTextPosition.x - 200f, resume.transform.position.y);
        //howToPlay.transform.position = new Vector2(htpTextPosition.x - 200f, howToPlay.transform.position.y);
        //pauseQuit.transform.position = new Vector2(quitTextPosition.x - 200f, pauseQuit.transform.position.y);
        //
        //resumeBtn.transform.position = new Vector2(resumePosition.x - 200f, resumeBtn.transform.position.y);
        //howToPlayBtn.transform.position = new Vector2(htpPosition.x - 200f, howToPlayBtn.transform.position.y);
        //pauseQuitBtn.transform.position = new Vector2(quitPosition.x - 200f, pauseQuitBtn.transform.position.y);
    }

    public void SwitchTabPause(bool type, bool reenable = true)
    {
        if (type)
        {
            //Console.WriteLine("Pausing now");
            Enable<Transform>(pauseBG.transform);

            Enable<Transform>(resume.transform);
            Enable<Transform>(howToPlay.transform);
            //Enable<Transform>(menuText.transform);
            //Enable<Transform>(options.transform);
            Enable<Transform>(pauseQuit.transform);

            Enable<Transform>(resumeBtn.transform);
            //Enable<Transform>(menuBtn.transform);
            //Enable<Transform>(optionsBtn.transform);
            Enable<Transform>(howToPlayBtn.transform);
            Enable<Transform>(pauseQuitBtn.transform);

            Enable<Transform>(pauseQuit.transform);

            Enable<Transform>(settingBtn);
            //Disable<Transform>(moneyText);
            //Disable<Transform>(coinSymbol);
            //Application.SetPause(true);
            //Time.timeScale = 0f;

            //Time.timeScale = 0f;

            if (combinedUI != null)
                combinedUI.CloseAllUIExcept(UIType.Pause);

            Disable<Transform>(displayArrow);
            Disable<Transform>(displayArrowWhite);

        }
        else
        {
            //Console.WriteLine("Unpausing now");
            //Enable<Transform>(moneyText);
            //Enable<Transform>(coinSymbol);
            Disable<Transform>(pauseBG.transform);
            Disable<Transform>(HowToBG.transform);

            Disable<Transform>(resume.transform);
            Disable<Transform>(howToPlay.transform);
            //Disable<Transform>(menuText.transform);
            //Disable<Transform>(options.transform);
            Disable<Transform>(pauseQuit.transform);

            Disable<Transform>(resumeBtn.transform);
            //Disable<Transform>(menuBtn.transform);
            //Disable<Transform>(optionsBtn.transform);
            Disable<Transform>(howToPlayBtn.transform);
            Disable<Transform>(pauseQuitBtn.transform);

            Disable<Transform>(quitBG.transform);
            Disable<Transform>(areYouSure.transform);
            Disable<Transform>(quitYes.transform);
            Disable<Transform>(quitNo.transform);

            Disable<Transform>(settingBtn);

            //Application.SetPause(false);

            if (reenable)
            {
                //Time.timeScale = 1f;

                if (combinedUI != null)
                    combinedUI.EnableAllMasterButton();
            }

            //pauseBG.transform.position = new Vector2(bgPosition.x, pauseBG.transform.position.y);
            //
            //resume.transform.position = new Vector2(resumeTextPosition.x - 200f, resume.transform.position.y);
            //howToPlay.transform.position = new Vector2(htpTextPosition.x - 200f, howToPlay.transform.position.y);
            //pauseQuit.transform.position = new Vector2(quitTextPosition.x - 200f, pauseQuit.transform.position.y);
            //
            //resumeBtn.transform.position = new Vector2(resumePosition.x - 200f, resumeBtn.transform.position.y);
            //howToPlayBtn.transform.position = new Vector2(htpPosition.x - 200f, howToPlayBtn.transform.position.y);
            //pauseQuitBtn.transform.position = new Vector2(quitPosition.x - 200f, pauseQuitBtn.transform.position.y);
        }
    }
    private void PauseAction()
    {
        //gameState.InvertPause();

        if (gameState.AllowPause())
        {
            bool state = !gameState.GetPause();
            gameState.SetPause(state);
            SwitchTabPause(state);
        }

    }

    public override void Update()
    {
        if (!gameState.GetDrawMode())
        {
            if (Input.GetKeyDown(KeyCode.Escape))
            {
                PauseAction();
            }
        }

        //if (stopTime)
        //{
        //    stopTimer += Time.deltaTime;
        //
        //    float newTimer = 5f * stopTimer;
        //
        //    pauseBG.transform.position = new Vector2(Mathf.Lerp(pauseBG.transform.position.x, bgPosition.x, newTimer), pauseBG.transform.position.y);
        //    
        //    resume.transform.position = new Vector2(Mathf.Lerp(resume.transform.position.x, resumeTextPosition.x, newTimer), resume.transform.position.y);
        //    howToPlay.transform.position = new Vector2(Mathf.Lerp(howToPlay.transform.position.x, htpTextPosition.x, newTimer), howToPlay.transform.position.y);
        //    pauseQuit.transform.position = new Vector2(Mathf.Lerp(pauseQuit.transform.position.x, quitTextPosition.x, newTimer), pauseQuit.transform.position.y);
        //    
        //    resumeBtn.transform.position = new Vector2(Mathf.Lerp(resumeBtn.transform.position.x, resumePosition.x, newTimer), resumeBtn.transform.position.y);
        //    howToPlayBtn.transform.position = new Vector2(Mathf.Lerp(howToPlayBtn.transform.position.x, htpPosition.x, newTimer), howToPlayBtn.transform.position.y);
        //    pauseQuitBtn.transform.position = new Vector2(Mathf.Lerp(pauseQuitBtn.transform.position.x, quitPosition.x, newTimer), pauseQuitBtn.transform.position.y);
        //
        //    if (stopTimer > 0.1f)
        //    {
        //        stopTimer = 0f;
        //        stopTime = false;
        //
        //        Disable<Transform>(displayArrow);
        //        Disable<Transform>(displayArrowWhite);
        //
        //        Disable<Transform>(timerButton);
        //        Disable<Transform>(storeButton);
        //
        //        Time.timeScale = 0f;
        //    }
        //}
    }
    public override void OnMouseEnter()
    {
        texture.color = new Color(1f, 1f, 1f);
    }

    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            PauseAction();
        }
    }

    public override void OnMouseExit()
    {
        texture.color = new Color(0f, 0f, 0f);
    }

    internal void ResumeAction()
    {
        PauseAction();
    }

    internal void QuitAction()
    {
        Console.WriteLine("Quit selected");
        Enable<Transform>(quitBG.transform);
        Enable<Transform>(areYouSure.transform);
        Enable<Transform>(quitYes.transform);
        Enable<Transform>(quitNo.transform);
    }

    internal void QuitYesAction()
    {
        Console.WriteLine("Quiting");
        Application.Quit();
    }

    internal void QuitNoAction()
    {
        Console.WriteLine("Quit stopped");
        Disable<Transform>(quitBG.transform);
        Disable<Transform>(areYouSure.transform);
        Disable<Transform>(quitYes.transform);
        Disable<Transform>(quitNo.transform);
    }

    /*// Start is called before the first frame update
    public static bool GameIsPaused = false;
    public GameObject pauseMenuUI;
    private int count = 0;

    // Update is called once per frame
    public override void Start()
    {
        pauseMenuUI.SetActive(true);
        if (Input.GetMouseButtonDown(0))
        {
            PauseUI();

            if (GameIsPaused)
            {
                Resume();
            }
            else
            {
                Pause();
            }
        }
    }

    public override void Update()
    {
        if (Input.GetKey(KeyCode.Escape))
        {
            PauseUI();

            if (GameIsPaused)
            {
                Resume();
                count++;
                Debug.Log("Escape 1  key is being pressed");

            }
            else
            {
                if (GameIsPaused && Input.GetKey(KeyCode.Escape))
                {
                    pauseMenuUI.SetActive(false);
                    Debug.Log("Escape 2 key is being pressed");
                }
                Pause();
                count++;


            }

        }
    }

    public void EndGame()
    { }
    public void PauseUI()
    {
        pauseMenuUI.SetActive(true);
        Time.timeScale = 0f;
        GameIsPaused = true;
    }

    public void Resume()
    {
        pauseMenuUI.SetActive(false);
        Time.timeScale = 1f;
        GameIsPaused = false;
    }

    void Pause()
    {
        pauseMenuUI.SetActive(true);
        Time.timeScale = 0f;
        GameIsPaused = true;
    }

    public void LoadMenu()
    {
        Time.timeScale = 1f;
        Debug.Log("Load Menu");
        SceneManager.LoadScene("MainMenu");
    }

    public void QuitGame()
    {
        Debug.Log("Quit Game");
        Application.Quit();
    }*/

}
