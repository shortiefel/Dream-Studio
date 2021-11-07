using System.Collections;
using System.Collections.Generic;

public class NotificationTimer : MonoBehaviour
{
    public float timeRemaining = 10;
    public bool timerIsRunning = false;

    /*public GameOverControl gameOverUI;
    public bool activate = false;

    public ScoreSystem scoreSystem;*/


    public override void Start()
    {
        // Starts the timer automatically
        timerIsRunning = true;
    }

    public override void Update()
    {
        //if (timerIsRunning)
        //{
        //    if (timeRemaining > 0)
        //    {
        //        timeRemaining -= Time.deltaTime;
        //    }
        //    else
        //    {
        //        Debug.Log("Opps, you're out of luck, you have run out of time from one of your house!");
        //        timeRemaining = 0;
        //        timerIsRunning = false;

        //        // set game object UI active
        //        //gameOverUI.PauseAllActivities();
        //        //gameOverUI.SetGameUI();
        //        SceneManager.LoadScene("GameOver");

        //        // add score????????????????????????????????????????????????????
        //        scoreSystem.AddScore();
        //        scoreSystem.UpdateHighScore();

        //        // set gameobject to not active
        //        gameObject.SetActive(false);
        //    }
        //}
    }
}
