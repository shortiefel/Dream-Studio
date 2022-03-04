
public class ButtonTimeClick : MonoBehaviour
{
    bool TimerTypeButton;

    Transform Timer;
    Transform TimerWhite;
    Transform TimerStop;
    Transform TimerNormal;
    Transform TimerFast;
    Transform TimerStopWhite;
    Transform TimerNormalWhite;
    Transform TimerFastWhite;

    // Vector2 timerPosition;
    TimerType tt;

    GameState gameState;
    TimeSystem timeSystem;

    bool type;


    public override void Start()
    {
        Debug.Log("Button Time clixk start");

        timeSystem = GameObject.Find("TimerIcon").GetComponent<TimeSystem>();
        gameState = GameObject.Find("GameManager").GetComponent<GameState>();

        if (entityId == GameObject.Find("TimerIcon").GetComponent<Transform>().entityId)
        {
            tt = TimerType.Timer;
            type = true;
        }
        else if (entityId == GameObject.Find("TimerStop").GetComponent<Transform>().entityId)
        {
            tt = TimerType.TimerStop;
            type = true;
        }
        else if (entityId == GameObject.Find("TimerNormal").GetComponent<Transform>().entityId)
        {
            tt = TimerType.TimerNormal;
            type = true;
        }
        else if (entityId == GameObject.Find("TimerForward").GetComponent<Transform>().entityId)
        {
            tt = TimerType.TimerFast;
            type = true;
        }
        else if (entityId == GameObject.Find("TimerStopWhite").GetComponent<Transform>().entityId)
        {
            tt = TimerType.TimerStop;
            type = false;
        }
        else if (entityId == GameObject.Find("TimerNormalWhite").GetComponent<Transform>().entityId)
        {
            tt = TimerType.TimerNormal;
            type = false;
        }
        else if (entityId == GameObject.Find("TimerForwardWhite").GetComponent<Transform>().entityId)
        {
            tt = TimerType.TimerFast;
            type = false;
        }
        else if (entityId == GameObject.Find("TimerIconWhite").GetComponent<Transform>().entityId)
        {
            tt = TimerType.Timer;
            type = false;
        }
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
                        Debug.Log("peeka");

                        if (Input.GetMouseButtonDown(MouseCode.Left))
                        {
                            timeSystem.SwitchTabTimer(type);
                        }

                        break;
                    }

                case TimerType.TimerStop:
                    {
                        if (Input.GetMouseButtonDown(MouseCode.Left))
                        {
                            timeSystem.CallFunctionTimer(tt, type);
                        }

                        break;
                    }

                case TimerType.TimerNormal:
                    {
                        if (Input.GetMouseButtonDown(MouseCode.Left))
                        {
                            timeSystem.CallFunctionTimer(tt, type);
                        }

                        break;
                    }

                case TimerType.TimerFast:
                    {
                        if (Input.GetMouseButtonDown(MouseCode.Left))
                        {

                            timeSystem.CallFunctionTimer(tt, type);
                        }

                        break;
                    }

                default:

                    break;
            }
        }



    }

    public override void OnEnable()
    {
        Debug.Log("Enabling \n");
    }


}

    
