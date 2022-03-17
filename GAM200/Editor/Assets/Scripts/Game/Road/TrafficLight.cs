using System;

public enum DirectionState
{
    Horizontal,
    Vertical,
    None
}

public class TrafficLight : MonoBehaviour
{
    //True for left and right
    //False for top and bottom
    public bool state;
    //private bool toState;

    public DirectionState directionState;
    public DirectionState nextState;

    private int carCounter;

    //private Texture texture;

    private float timer;
    private float switchTimer;

    private float inBetweenTimer;

    //private float secondaryTimer;

    private TrafficLightManager tlm;

    public override void Start()
    {
        //Debug.Log("Making new start -----------------------------------");
        directionState = DirectionState.Horizontal;

        GameObject go = GameObject.Find("TrafficManager");
        if (go != null)
            tlm = go.GetComponent<TrafficLightManager>();
        if (tlm != null)
        {
            //Debug.Log("Not null");
            tlm.RegisterTrafficLight(Vector2Int.RoundToInt(transform.position), entityId);
        }

        //state = toState = true;
        state = true;
        //texture = gameObject.GetComponent<Texture>();
        //texture.color = new Color(1, 0, 0, 1);
        transform.angle = 0;
        carCounter = 0;

        timer = 0f;
        switchTimer = 5f;

        inBetweenTimer = 0f;
    }

    //public void RequestSwap(bool inState)
    //{
    //    if (state != inState)
    //        toState = inState;
    //}

    //public DirectionState GetTrafficLightState()
    //{
    //    if (Input.GetKey(KeyCode.B))
    //        Debug.Log(directionState + " Getting from " + entityId);
    //    return directionState;
    //}

    private void SwapState()
    {
        //toState = state = !state;
        //if (state)
        //    transform.angle = 0;
        ////texture.color = new Color(1, 0, 0, 1);
        //else
        //    transform.angle = 90;
        //texture.color = new Color(0, 1, 0, 1);
        //Debug.Log("Change State " + directionState);
        //Test

        //directionState = nextState;
        if (directionState == DirectionState.Horizontal) nextState = DirectionState.Vertical;
        else if (directionState == DirectionState.Vertical) nextState = DirectionState.Horizontal;
        directionState = DirectionState.None;

        
        //Debug.Log("After " + directionState + " " + entityId);
    }

    public override void Update()
    {
        float deltaTime = Time.deltaTime;
        //Console.WriteLine("State " + directionState);
        if (Input.GetKeyDown(KeyCode.V))
            SwapState();
        timer += deltaTime;
        if (timer >= switchTimer)
        {
            //secondaryTimer += Time.deltaTime;
            //
            //if (secondaryTimer > 0.2f)
            //{
            //    timer = 0f;
            //    secondaryTimer = 0f;
            //    SwapState();
            //    Console.WriteLine("Secondary timer activated ");
            //
            //}
            //Might have problem where car move too fast and enter but doesnt move
            //Check timer to 1.5 of switchTimer to prevent infinite waiting to change direction
            if (carCounter == 0 || timer >= switchTimer * 1.5f)
            {
                timer = 0f;
                SwapState();
            }
        }

        //Put traffic light in a state where cars are not allowed to go for both direction
        if (directionState == DirectionState.None)
        {
            inBetweenTimer += deltaTime;
            if (inBetweenTimer >= 0.5f)
            {
                //toState = state = !state;
                state = !state;
                if (state)
                    transform.angle = 0;
                //texture.color = new Color(1, 0, 0, 1);
                else
                    transform.angle = 90;

                directionState = nextState;
                inBetweenTimer = 0f;
            }
        }
        //if (Input.GetKeyDown(KeyCode.C))
        //{
        //    SwapState();
        //}
    }

    public override void OnTriggerEnter(Transform trans)
    {
        ++carCounter;
        //Debug.Log("The id is " + id);
    }

    public override void OnTriggerExit(Transform trans)
    {

        --carCounter;
    }

    //public override void OnDestroy()
    //{
    //    Debug.Log("Traffic light destroy");
    //    if (tlm != null)
    //        tlm.RemoveTrafficLight(Vector2Int.RoundToInt(transform.position));
    //}
}

