using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class MenuLoad : MonoBehaviour
{
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
