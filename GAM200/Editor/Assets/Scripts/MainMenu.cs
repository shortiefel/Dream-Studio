using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class MainMenu : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {

    }
    public void PlayButton()
    {
        //Invoke("GoToGameIntro", 1);
        GoToGameIntro();
    }
    public void GoToGameIntro()
    {
        //SceneManager.LoadScene(1);
        SceneManager.LoadScene("Intro");
    }
    public void GoToGame()
    {
        //SceneManager.LoadScene(2);
        SceneManager.LoadScene("NewGame");
    }

    public void GetHighScore()
    {
        SceneManager.LoadScene("HighScore");
    }

    public void LeaveGame()
    {
        Debug.Log("Quit Game");
        Application.Quit();

    }

    public void MenuButton()
    {
        //SceneManager.LoadScene(0);
        SceneManager.LoadScene("MainMenu");
    }

}
