public enum TimerType
{
    Timer = 1,
    TimerStop,
    TimerNormal,
    TimerFast,
    TimerWhite
}

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
    Vector2 tStopPosition;
    Vector2 tNormalPosition;
    Vector2 tFastPosition;

    UI texture;

    GameState gameState;
    GameManager gameManager;

    TimerType tt;

    TimeSystem timeSystem;

    public bool opening;
    public bool closing;
    float timer;

    float closeYPosition;
    float closeYPosition1;
    float closeYPosition2;

    float speedMultiply;

    public override void Start()
    {
        texture = GetComponent<UI>();

        timeSystem = GameObject.Find("TimerIcon").GetComponent<TimeSystem>();
        gameState = GameObject.Find("GameManager").GetComponent<GameState>();
        gameManager = GameObject.Find("GameManager").GetComponent<GameManager>();

        Timer = GameObject.Find("TimerIcon").GetComponent<Transform>();
        TimerWhite = GameObject.Find("TimerIconWhite").GetComponent<Transform>();

        TimerStop = GameObject.Find("TimerStop").GetComponent<Transform>();
        TimerStop = GameObject.Find("TimerStopWhite").GetComponent<Transform>();
        tStopPosition = TimerStop.position;

        TimerNormal = GameObject.Find("TimerNormal").GetComponent<Transform>();
        TimerNormal = GameObject.Find("TimerNormalWhite").GetComponent<Transform>();
        tNormalPosition = TimerNormal.position;

        TimerFast = GameObject.Find("TimerForward").GetComponent<Transform>();
        TimerFast = GameObject.Find("TimerForwardWhite").GetComponent<Transform>();
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

    public void SwitchTab(bool type)
    {
        if (type)
        {
            opening = true;

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
        TimerStop.position = new Vector2 (tStopPosition.x, (Mathf.Lerp(tStopPosition.y, closeYPosition, timer)));
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

    public void CallFunction(ButtonType _bt, bool _activeType)
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
            switch(tt)
            {
                case TimerType.TimerStop:
                {
                        Enable<Transform>(TimerStopWhite);
                        break;
                }
               case TimerType.TimerNormal:
                {
                        Enable<Transform>(TimerNormalWhite);
                        break;
                }
                case TimerType.TimerFast:
                {
                        Enable<Transform>(TimerFastWhite);
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

}

    
