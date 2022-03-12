
public class ButtonTimeClick : MonoBehaviour
{
    bool TimerTypeButton;

    // Vector2 timerPosition;
    TimerType tt;

    GameState gameState;
    TimeSystem timeSystem;

    bool type;


    public override void Start()
    {
        timeSystem = GameObject.Find("TimerIcon").GetComponent<TimeSystem>();
        //gameState = GameObject.Find("GameManager").GetComponent<GameState>();

        if (entityId == GameObject.Find("TimerIcon").GetComponent<Transform>().entityId)
        {
           // Debug.Log("selected1");
            tt = TimerType.Timer;
            type = true;
           // Debug.Log("selected2");
        }

        if (entityId == GameObject.Find("TimerIconWhite").GetComponent<Transform>().entityId)
        {
            tt = TimerType.Timer;
            type = false;
        }

        if (entityId == GameObject.Find("TimerStop").GetComponent<Transform>().entityId)
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
        //else if (entityId == GameObject.Find("TimerStopWhite").GetComponent<Transform>().entityId)
        //{
        //    tt = TimerType.TimerStop;
        //    type = false;
        //}
        //else if (entityId == GameObject.Find("TimerNormalWhite").GetComponent<Transform>().entityId)
        //{
        //    tt = TimerType.TimerNormal;
        //    type = false;
        //}
        //else if (entityId == GameObject.Find("TimerForwardWhite").GetComponent<Transform>().entityId)
        //{
        //    tt = TimerType.TimerFast;
        //    type = false;
        //}
      
    }



    public override void OnMouseOver()
    {
        //Debug.Log("I's here");

        if (transform.isActive)
        {
            switch (tt)
            {
                case TimerType.Timer:
                    {
                        //Debug.Log("in timer");
                        if (Input.GetMouseButtonDown(MouseCode.Left))
                        {
                            //Debug.Log("Click in timer");
                           // Debug.Log("Entity " + entityId + " " + transform.isActive);
                            timeSystem.SwitchTabTimer(type);
                           // Debug.Log("out");
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

    //public override void OnEnable()
    //{
    //    Debug.Log("Enabling \n");
    //}


}

    
