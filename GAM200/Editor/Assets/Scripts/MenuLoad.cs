
public class MenuLoad : MonoBehaviour
{
    //public override void OnMouseOver()
    public override void Update()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            SceneManager.LoadScene("Intro");
        }
    }
    public static void PlayButton()
    {
        //Invoke("GoToGameIntro", 1);
        LoadGame();
    }
    public static void GameIntroButton()
    {
        //SceneManager.LoadScene(1);
        SceneManager.LoadScene("Intro");
    }
    public static void LoadGame()
    {
        //SceneManager.LoadScene(2);
        SceneManager.LoadScene("NewGame");
    }

    public static void LoadHighScore()
    {
        SceneManager.LoadScene("HighScore");
    }

    public static void LeaveGame()
    {
        Debug.Log("Quit Game");
        Application.Quit();

    }

    public static void MenuButton()
    {
        SceneManager.LoadScene("MainMenu");
    }

}
