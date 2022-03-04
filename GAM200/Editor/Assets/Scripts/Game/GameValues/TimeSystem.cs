using System;
using System.Collections;
using System.Collections.Generic;



public class TimeSystem : MonoBehaviour
{

    TimerType tt;
    GameState gameState;

    ButtonTimeClick btc;
    bool type;

    public override void Start()
    {
        if (entityId == GameObject.Find("TimerIcon").GetComponent<Transform>().entityId)
        {
            tt = TimerType.Timer;
        }
        else if (entityId == GameObject.Find("TimerStop").GetComponent<Transform>().entityId)
        {
            tt = TimerType.TimerStop;
        }
        else if (entityId == GameObject.Find("TimerNormal").GetComponent<Transform>().entityId)
        {
            tt = TimerType.TimerNormal;
        }
        else if (entityId == GameObject.Find("TimerForward").GetComponent<Transform>().entityId)
        {
            tt = TimerType.TimerFast;
        }
        else if (entityId == GameObject.Find("TimerIconWhite").GetComponent<Transform>().entityId)
        {
            tt = TimerType.TimerWhite;
        }

        gameState = GameObject.Find("GameManager").GetComponent<GameState>();

    }

    public override void OnMouseOver()
    {
        Debug.Log("I's here");

        if (transform.isActive)
        {
            switch (tt)
            {
                case TimerType.Timer:
                    {
                        if (Input.GetMouseButtonDown(MouseCode.Left))
                        {
                            btc.SwitchTab(type);
                        }

                        break;
                    }

                case TimerType.TimerStop:
                    {
                        if (Input.GetMouseButtonDown(MouseCode.Left))
                        {
                            Time.timeScale = 0f;
                            StopTime();
                        }

                        break;
                    }

                case TimerType.TimerNormal:
                    {
                        if (Input.GetMouseButtonDown(MouseCode.Left))
                        {
                            NormalTime();
                        }

                        break;
                    }

                case TimerType.TimerFast:
                    {
                        if (Input.GetMouseButtonDown(MouseCode.Left))
                        {
                            Time.timeScale = 3f;
                            SpeedUpTime();
                        }

                        break;
                    }
            }
        }
           
    }





    //Btw this is found in the GameManager entity in game scene
    //probably use this -> GameObject.Find("GameManager").GetComponent<TimeSystem>()
    //public override void Update()
    //{

    //    if (Input.GetKeyDown(KeyCode.Q))
    //    {
    //        Time.timeScale = 1f;
    //        NormalTime();
    //    }

    //    //Stop time
    //    if (Input.GetKeyDown(KeyCode.W))
    //    {
    //        Time.timeScale = 0f;
    //        StopTime();
    //    }

    //    //Speed up time
    //    if (Input.GetKeyDown(KeyCode.E))
    //    {
    //        Time.timeScale = 3f;
    //        SpeedUpTime();
    //    }

    public void NormalTime()
    {
        Time.timeScale = 1f;
    }

    public void StopTime()
    {
        Time.timeScale = 0f;
    }

    public void SpeedUpTime()
    {
        Time.timeScale = 1.5f;
    }
}