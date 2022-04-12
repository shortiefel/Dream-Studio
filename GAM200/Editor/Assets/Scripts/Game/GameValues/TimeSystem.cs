using System;
using System.Collections;
using System.Collections.Generic;

public enum TimerType
{
    Timer = 1,
    TimerStop,
    TimerNormal,
    TimerFast,
    None
}


public class TimeSystem : MonoBehaviour
{ 

    Transform Timer;
    //Transform TimerWhite;
    Transform TimerStop;
    Transform TimerNormal;
    Transform TimerFast;
    Transform TimerStopWhite;
    Transform TimerNormalWhite;
    Transform TimerFastWhite;

    Transform dayText;
    Transform clockTimer;
    Transform AmPm;

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

    static float timeScale;


    //UI texture;
    GameManager gameManager;
    //GameState gameState;

    //TimeSystem timeSystem;

    public static float previousTimeScale;

    public bool isOn = false;

    //private static bool pauseOrUnpause = false;
    public override void Start()
    {
        previousTimeScale = 1f;
        //texture = GetComponent<UI>();

        //timeSystem = GameObject.Find("TimerIcon").GetComponent<TimeSystem>();

        //gameState = GameObject.Find("GameManager").GetComponent<GameState>();
        gameManager = GameObject.Find("GameManager").GetComponent<GameManager>();

        Timer = GameObject.Find("TimerIcon").GetComponent<Transform>();
        //TimerWhite = GameObject.Find("TimerIconWhite").GetComponent<Transform>();

        TimerStop = GameObject.Find("TimerStop").GetComponent<Transform>();
        TimerStopWhite = GameObject.Find("TimerStopWhite").GetComponent<Transform>();
        tStopPosition = TimerStop.position;

        TimerNormal = GameObject.Find("TimerNormal").GetComponent<Transform>();
        TimerNormalWhite = GameObject.Find("TimerNormalWhite").GetComponent<Transform>();
        tNormalPosition = TimerNormal.position;

        TimerFast = GameObject.Find("TimerForward").GetComponent<Transform>();
        TimerFastWhite = GameObject.Find("TimerForwardWhite").GetComponent<Transform>();
        tFastPosition = TimerFast.position;

        dayText = GameObject.Find("DayClock").GetComponent<Transform>();
        clockTimer = GameObject.Find("Clock").GetComponent<Transform>();
        AmPm = GameObject.Find("AMPM").GetComponent<Transform>();

        Enable<Transform>(Timer);
        Disable<Transform>(TimerStop);
        Disable<Transform>(TimerNormal);
        Disable<Transform>(TimerFast);
        //Disable<Transform>(TimerWhite);
        Disable<Transform>(TimerStopWhite);
        Disable<Transform>(TimerNormalWhite);
        Disable<Transform>(TimerFastWhite);

        opening = false;
        closing = false;
        timer = 0f;
        closeYPosition = 28f;
        closeYPosition1 = 18f;
        closeYPosition2 = 8f;
        speedMultiply = 5f;


        TimerStop.position = new Vector2(tStopPosition.x, closeYPosition);
        TimerStopWhite.position = new Vector2(tStopPosition.x, closeYPosition);
        TimerNormal.position = new Vector2(tNormalPosition.x, closeYPosition1);
        TimerNormalWhite.position = new Vector2(tNormalPosition.x, closeYPosition1);
        TimerFast.position = new Vector2(tFastPosition.x, closeYPosition2);
        TimerFastWhite.position = new Vector2(tFastPosition.x, closeYPosition2);

        timeScale = 1f;
        Time.timeScale = timeScale;
    }

    public void SwitchTabTimer(bool type, bool reenable = true)
    {
        //Debug.Log("in switch tab"); 

        if (type)
        {
            opening = true;
            //Debug.Log("in open");
            //Disable<Transform>(Timer);
            //Enable<Transform>(TimerWhite);

            //EnableAllNormal();

            if (timeScale == 0f)
                Enable<Transform>(TimerStopWhite);
            else
                Enable<Transform>(TimerStop);

            if (timeScale == 1f)
                Enable<Transform>(TimerNormalWhite);

            else
                Enable<Transform>(TimerNormal);

            if (timeScale == 1.5f)
                Enable<Transform>(TimerFastWhite);
            else
                Enable<Transform>(TimerFast);

            isOn = true;
        }
        else
        {
            ResetAll();

            //Debug.Log("in close");
            closing = true;
            //Disable<Transform>(TimerWhite);
            //if (reenable)
            //    Enable<Transform>(Timer);

            isOn = false;
        }
    }

    private void CloseTabs()
    {
        TimerStop.position = new Vector2(tStopPosition.x, (Mathf.Lerp(tStopPosition.y, closeYPosition, timer)));
        TimerStopWhite.position = new Vector2(tStopPosition.x, (Mathf.Lerp(tStopPosition.y, closeYPosition, timer)));

        TimerNormal.position = new Vector2(tStopPosition.x, (Mathf.Lerp(tStopPosition.y, closeYPosition1, timer)));
        TimerNormalWhite.position = new Vector2(tStopPosition.x, (Mathf.Lerp(tStopPosition.y, closeYPosition1, timer)));

        TimerFast.position = new Vector2(tStopPosition.x, (Mathf.Lerp(tStopPosition.y, closeYPosition2, timer)));
        TimerFastWhite.position = new Vector2(tStopPosition.x, (Mathf.Lerp(tStopPosition.y, closeYPosition2, timer)));

        timer += speedMultiply * Time.unscaledDeltaTime;
        //Debug.Log("C Timer " + timer + " delta time " + Time.fixedDeltaTime);
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
        TimerNormalWhite.position = new Vector2(tStopPosition.x, (Mathf.Lerp(tStopPosition.y, closeYPosition1, timer)));

        TimerFast.position = new Vector2(tStopPosition.x, (Mathf.Lerp(tStopPosition.y, closeYPosition2, timer)));
        TimerFastWhite.position = new Vector2(tStopPosition.x, (Mathf.Lerp(tStopPosition.y, closeYPosition2, timer)));

        timer += speedMultiply * Time.unscaledDeltaTime;
        //Debug.Log("O Timer " + timer + " delta time " + Time.fixedDeltaTime);

        if (timer > 0.8f)
        {
            timer = 0f;
            opening = false;
        }
    }

    public void CallFunctionTimer(TimerType _tt, bool _activeType)
    {
        DisableAll();

        if (_activeType)
        {
            switch (_tt)
            {
                case TimerType.TimerStop:
                    {
                        Enable<Transform>(TimerStopWhite);
                        StopTime();

                        EnableAllNormalExcept(TimerType.TimerStop);
                        break;
                    }
                case TimerType.TimerNormal:
                    {
                        Enable<Transform>(TimerNormalWhite);
                        NormalTime();

                        EnableAllNormalExcept(TimerType.TimerNormal);
                        break;
                    }
                case TimerType.TimerFast:
                    {
                        Enable<Transform>(TimerFastWhite);
                        SpeedUpTime();

                        EnableAllNormalExcept(TimerType.TimerFast);
                        break;
                    }
            }
        }
        //else
        //{
        //    EnableAllNormal();
        //}
    }


    public override void Update()
    {
        if (opening)
            OpenTabs();
        if (closing)
            CloseTabs();
    }

    public void EnableAllNormalExcept(TimerType tt = TimerType.None)
    {
        if (tt != TimerType.TimerStop)
            Enable<Transform>(TimerStop);
        if (tt != TimerType.TimerNormal)
            Enable<Transform>(TimerNormal);
        if (tt != TimerType.TimerFast)
            Enable<Transform>(TimerFast);
    }

    public void DisableAllNormal()
    {
        Disable<Transform>(TimerFast);
        Disable<Transform>(TimerStop);
        Disable<Transform>(TimerNormal);
    }

    public void EnableAllWhite()
    {
        Enable<Transform>(TimerFastWhite);
        Enable<Transform>(TimerStopWhite);
        Enable<Transform>(TimerNormalWhite);
    }

    public void DisableAllWhite()
    {
        Disable<Transform>(TimerFastWhite);
        Disable<Transform>(TimerStopWhite);
        Disable<Transform>(TimerNormalWhite);
    }

    public void ResetAll()
    {
        DisableAllNormal();
        DisableAllWhite();

        gameManager.ClearInputActions();
    }

    public void FullClose()
    {
        ResetAll();

        Disable<Transform>(dayText);
        Disable<Transform>(clockTimer);
        Disable<Transform>(AmPm);
    }

    public void FullOpen()
    {
        Enable<Transform>(dayText);
        Enable<Transform>(clockTimer);
        Enable<Transform>(AmPm);

        if (isOn)
            SwitchTabTimer(true);
    }

    public void DisableAll()
    {
        DisableAllNormal();
        DisableAllWhite();
    }

    static public void NormalTime()
    {
        timeScale = 1f;
        previousTimeScale = timeScale;
        Time.timeScale = timeScale;
    }

    static public void StopTime()
    {
        timeScale = 0f;
        previousTimeScale = timeScale;
        Time.timeScale = timeScale;
    }

    static public void SpeedUpTime()
    {
        timeScale = 1.5f;
        previousTimeScale = timeScale;
        Time.timeScale = timeScale;
    }

    static public void ResumeTime()
    {
        Time.timeScale = timeScale;
    }

    static public void PauseTime()
    {
        Time.timeScale = 0f;
    }
}