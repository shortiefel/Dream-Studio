using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class Skip : MonoBehaviour
{
    public override void Update()
    {
        if (Input.GetKeyDown(KeyCode.O))
        {
            GoToMainMenu();
        }
    }

    public void SkipButton()
    {
        //SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex + 1);
    }

    public void GoToMainMenu()
    {
        SceneManager.LoadScene("MainMenu");
    }
}
