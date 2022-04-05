
public class ButtonTimeClick : MonoBehaviour
{
    bool TimerTypeButton;

    TimerType tt;

    GameState gameState;
    TimeSystem timeSystem;

    bool type;


    public override void Start()
    {
        GameObject timeGO = GameObject.Find("TimerIcon");
        timeSystem = timeGO.GetComponent<TimeSystem>();
        //gameState = GameObject.Find("GameManager").GetComponent<GameState>();

        if (entityId == timeGO.GetComponent<Transform>().entityId)
        {
           // Debug.Log("selected1");
            tt = TimerType.Timer;
            type = true;
           // Debug.Log("selected2");
        }

        //if (entityId == GameObject.Find("TimerIconWhite").GetComponent<Transform>().entityId)
        //{
        //    tt = TimerType.Timer;
        //    type = false;
        //}

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

        //if (transform.isActive)
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
                            type = !type;
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

    public override void OnMouseEnter()
    {
        InputManager.allowBuilding = false;
    }

    public override void OnMouseExit()
    {
        InputManager.allowBuilding = true;
    }

}

    
