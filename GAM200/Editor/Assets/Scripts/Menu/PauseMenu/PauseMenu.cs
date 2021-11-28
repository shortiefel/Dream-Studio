

using System;

public class PauseMenu : MonoBehaviour
{
    GameObject resume;
    GameObject howToPlay;
    //GameObject options;
    GameObject pauseQuit;
    GameObject areYouSure;
    GameObject quitYes;
    GameObject quitNo;

    bool pauseState;

    public override void Start()
    {
        resume = GameObject.Find("ResumeText");
        howToPlay = GameObject.Find("HowToText");
        //ob = GameObject.Find("OptionText");
        pauseQuit = GameObject.Find("QuitText");

        areYouSure = GameObject.Find("AreYouSureText");
        quitYes = GameObject.Find("YesText");
        quitNo = GameObject.Find("NoText");

        pauseState = false;
    }

    private void PauseAction()
    {
        pauseState = !pauseState;

        if(pauseState)
        {
            Console.WriteLine("Pausing now");
            Enable<Transform>(resume.transform);
            Enable<Transform>(howToPlay.transform);
            Enable<Transform>(pauseQuit.transform);

            //Application.SetPause(true);
            Time.timeScale = 0f;
        }
        else
        {
            Console.WriteLine("Unpausing now");
            Disable<Transform>(resume.transform);
            Disable<Transform>(howToPlay.transform);
            Disable<Transform>(pauseQuit.transform);

            Disable<Transform>(areYouSure.transform);
            Disable<Transform>(quitYes.transform);
            Disable<Transform>(quitNo.transform);

            //Application.SetPause(false);
            Time.timeScale = 1f;
        }



    }

    public override void Update()
    {
        if(Input.GetKeyDown(KeyCode.Escape))
        {
            PauseAction();
        }
    }

    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            PauseAction();
        }
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
