

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
    GameObject pauseBtn;
    GameObject howToPlayBtn;

    GameObject pauseBG;
    GameObject HowToBG;

    GameObject areYouSure;
    GameObject quitYes;
    GameObject quitNo;

    //bool pauseState;
    GameState gameState;

    UI texture;

    /*public bool GetPause()
    {
        return pauseState;
    }*/

    public override void Start()
    {
        texture = GetComponent<UI>();
        texture.color = new Color(0f, 0f, 0f);

        pauseBG = GameObject.Find("PauseBG");
        HowToBG = GameObject.Find("HowToBG");

        resume = GameObject.Find("ResumeText");
        howToPlay = GameObject.Find("HowToText");
        //menuText = GameObject.Find("MenuText");
        //options = GameObject.Find("OptionText");
        pauseQuit = GameObject.Find("QuitText");

        resumeBtn = GameObject.Find("ResumeBtn");
        //menuBtn = GameObject.Find("MenuBtn");
        //optionsBtn = GameObject.Find("Optionsbtn");
        pauseBtn = GameObject.Find("QuitBtn");
        howToPlayBtn = GameObject.Find("howToPlayBtn");

        areYouSure = GameObject.Find("AreYouSureText");
        quitYes = GameObject.Find("YesText");
        quitNo = GameObject.Find("NoText");
        
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
        Disable<Transform>(pauseBtn.transform);
        Disable<Transform>(howToPlayBtn.transform);

        Disable<Transform>(areYouSure.transform);
        Disable<Transform>(quitYes.transform);
        Disable<Transform>(quitNo.transform);

        gameState = GameObject.Find("GameManager").GetComponent<GameState>();
    }

    private void PauseAction()
    {
        gameState.InvertPause();

        if (gameState.GetPause())
        {
            Console.WriteLine("Pausing now");
            Enable<Transform>(pauseBG.transform);

            Enable<Transform>(resume.transform);
            Enable<Transform>(howToPlay.transform);
            //Enable<Transform>(menuText.transform);
            //Enable<Transform>(options.transform);
            Enable<Transform>(pauseQuit.transform);

            Enable<Transform>(resumeBtn.transform);
            //Enable<Transform>(menuBtn.transform);
            //Enable<Transform>(optionsBtn.transform);
            Enable<Transform>(pauseBtn.transform);
            Enable<Transform>(howToPlayBtn.transform);

            Enable<Transform>(pauseQuit.transform);
            //Application.SetPause(true);
            Time.timeScale = 0f;
        }
        else
        {
            Console.WriteLine("Unpausing now");
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
            Disable<Transform>(pauseBtn.transform);
            Disable<Transform>(howToPlayBtn.transform);

            Disable<Transform>(areYouSure.transform);
            Disable<Transform>(quitYes.transform);
            Disable<Transform>(quitNo.transform);

            //Application.SetPause(false);
            Time.timeScale = 1f;
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
