using System;
using System.Collections;
using System.Collections.Generic;

public enum TimerType
{
    Timer = 1,
    TimerStop,
    TimerNormal,
    TimerFast,
    TimerWhite
}


public class TimeSystem : MonoBehaviour
{ 

    Transform Timer;
    Transform TimerWhite;
    Transform TimerStop;
    Transform TimerNormal;
    Transform TimerFast;
    Transform TimerStopWhite;
    Transform TimerNormalWhite;
    Transform TimerFastWhite;

    Vector2 tStopPosition;
    Vector2 tNormalPosition;
    Vector2 tFastPosition;

    public bool opening;
    public bool closing;
    float timer;

    float closeYPosition;
    float closeYPosition1;
    float closeYPosition2;

    float speedMultiply;


    //UI texture;
    GameManager gameManager;
    GameState gameState;

    TimeSystem timeSystem;


    public override void Start()
    {
        //texture = GetComponent<UI>();

        timeSystem = GameObject.Find("TimerIcon").GetComponent<TimeSystem>();

        gameState = GameObject.Find("GameManager").GetComponent<GameState>();
        gameManager = GameObject.Find("GameManager").GetComponent<GameManager>();

        Timer = GameObject.Find("TimerIcon").GetComponent<Transform>();
        TimerWhite = GameObject.Find("TimerIconWhite").GetComponent<Transform>();

        TimerStop = GameObject.Find("TimerStop").GetComponent<Transform>();
        TimerStopWhite = GameObject.Find("TimerStopWhite").GetComponent<Transform>();
        tStopPosition = TimerStop.position;

        TimerNormal = GameObject.Find("TimerNormal").GetComponent<Transform>();
        TimerNormalWhite = GameObject.Find("TimerNormalWhite").GetComponent<Transform>();
        tNormalPosition = TimerNormal.position;

        TimerFast = GameObject.Find("TimerForward").GetComponent<Transform>();
        TimerFastWhite = GameObject.Find("TimerForwardWhite").GetComponent<Transform>();
        tFastPosition = TimerFast.position;

        Enable<Transform>(Timer);
        Disable<Transform>(TimerStop);
        Disable<Transform>(TimerNormal);
        Disable<Transform>(TimerFast);
        Disable<Transform>(TimerWhite);
        Disable<Transform>(TimerStopWhite);
        Disable<Transform>(TimerNormalWhite);
        Disable<Transform>(TimerFastWhite);



        opening = false;
        closing = false;
        timer = 0f;
        closeYPosition = 34f;
        closeYPosition1 = 27f;
        closeYPosition2 = 20.8f;
        speedMultiply = 5f;


        TimerStop.position = new Vector2(tStopPosition.x, closeYPosition);
        TimerStopWhite.position = new Vector2(tStopPosition.x, closeYPosition);
        TimerNormal.position = new Vector2(tNormalPosition.x, closeYPosition1);
        TimerNormalWhite.position = new Vector2(tStopPosition.x, closeYPosition1);
        TimerFast.position = new Vector2(tFastPosition.x, closeYPosition2);
        TimerFastWhite.position = new Vector2(tFastPosition.x, closeYPosition2);

    }

    public void SwitchTabTimer(bool type)
    {
        Debug.Log("in switch tab"); 

        if (type)
        {
            opening = true;
            Debug.Log("in open");
            Disable<Transform>(Timer);
            Enable<Transform>(TimerStop);
            Enable<Transform>(TimerNormal);
            Enable<Transform>(TimerFast);
            Enable<Transform>(TimerFastWhite);



        }
        else
        {

            closing = true;

            Enable<Transform>(Timer);
            Disable<Transform>(TimerFastWhite);
            Disable<Transform>(TimerStop);
            Disable<Transform>(TimerNormal);
            Disable<Transform>(TimerFast);
        }
    }

    private void CloseTabs()
    {
        TimerStop.position = new Vector2(tStopPosition.x, (Mathf.Lerp(tStopPosition.y, closeYPosition, timer)));
        TimerStopWhite.position = new Vector2(tStopPosition.x, (Mathf.Lerp(tStopPosition.y, closeYPosition, timer)));

        TimerNormal.position = new Vector2(tStopPosition.x, (Mathf.Lerp(tStopPosition.y, closeYPosition1, timer)));
        TimerNormalWhite.position = new Vector2(tStopPosition.x, (Mathf.Lerp(tStopPosition.y, closeYPosition2, timer)));

        TimerFast.position = new Vector2(tStopPosition.x, (Mathf.Lerp(tStopPosition.y, closeYPosition2, timer)));
        TimerFastWhite.position = new Vector2(tStopPosition.x, (Mathf.Lerp(tStopPosition.y, closeYPosition2, timer)));

        timer += speedMultiply * Time.deltaTime;
        if (timer > 0.8f)
        {
            timer = 0f;
            closing = false;
        }
    }

    private void OpenTabs()
    {
        TimerStop.position = new Vector2(tStopPosition.x, (Mathf.Lerp(tStopPosition.y, closeYPosition, timer)));
        TimerStopWhite.position = new Vector2(tStopPosition.x, (Mathf.Lerp(tStopPosition.y, closeYPosition, timer)));

        TimerNormal.position = new Vector2(tStopPosition.x, (Mathf.Lerp(tStopPosition.y, closeYPosition1, timer)));
        TimerNormalWhite.position = new Vector2(tStopPosition.x, (Mathf.Lerp(tStopPosition.y, closeYPosition2, timer)));

        TimerFast.position = new Vector2(tStopPosition.x, (Mathf.Lerp(tStopPosition.y, closeYPosition2, timer)));
        TimerFastWhite.position = new Vector2(tStopPosition.x, (Mathf.Lerp(tStopPosition.y, closeYPosition2, timer)));

        timer += speedMultiply * Time.deltaTime;
        if (timer > 0.8f)
        {
            timer = 0f;
            opening = false;
        }
    }

    public void CallFunctionTimer(TimerType _tt, bool _activeType)
    {
        Disable<Transform>(TimerStop);
        Disable<Transform>(TimerNormal);
        Disable<Transform>(TimerFast);
        Disable<Transform>(TimerWhite);
        Disable<Transform>(TimerStopWhite);
        Disable<Transform>(TimerNormalWhite);
        Disable<Transform>(TimerFastWhite);


        if (_activeType)
        {
            switch (_tt)
            {
                case TimerType.TimerStop:
                    {
                        Enable<Transform>(TimerStopWhite);
                        Time.timeScale = 0f;
                        StopTime();

                        Disable<Transform>(TimerStop);
                        break;
                    }
                case TimerType.TimerNormal:
                    {
                        Enable<Transform>(TimerNormalWhite);
                        NormalTime();
                        Disable<Transform>(TimerNormal);
                        break;
                    }
                case TimerType.TimerFast:
                    {
                        Enable<Transform>(TimerFastWhite);
                        Time.timeScale = 3f;
                        SpeedUpTime();
                        Disable<Transform>(TimerFast);
                        break;
                    }
            }
        }
    }


    public override void Update()
    {
        if (opening)
            OpenTabs();
        if (closing)
            CloseTabs();
    }

    
  
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