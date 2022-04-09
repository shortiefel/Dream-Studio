using System;
using System.Collections.Generic;

public enum DirectionState
{
    Horizontal,
    HorizontalLeft,
    Vertical,
    VerticalLeft,
    Up,
    Down,
    Left,
    Right,
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

    bool reqeusting = false;

    public TrafficColliderCheck leftCollider;
    public TrafficColliderCheck rightCollider;
    public TrafficColliderCheck upCollider;
    public TrafficColliderCheck downCollider;

    bool spawnCheck = true;
    List<uint> spawnCheckCollide;

    public override void Start()
    {
        //Debug.Log("Making new start -----------------------------------");
        //directionState = DirectionState.Horizontal;
        directionState = DirectionState.Up;
        transform.angle = 90;

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
        //transform.angle = 0;
        carCounter = 0;

        timer = 0f;
        switchTimer = 2f;

        inBetweenTimer = 0f;

        Vector2 transPos = transform.position;
        leftCollider = Instantiate(new Prefab("TrafficColliderCheck"), new Vector3(transPos.x - 0.55f, transPos.y + 0.19f, 0f)).GetComponent<TrafficColliderCheck>();
        rightCollider = Instantiate(new Prefab("TrafficColliderCheck"), new Vector3(transPos.x + 0.55f, transPos.y - 0.19f, 0f)).GetComponent<TrafficColliderCheck>();
        upCollider = Instantiate(new Prefab("TrafficColliderCheck"), new Vector3(transPos.x + 0.19f, transPos.y + 0.55f, 0f)).GetComponent<TrafficColliderCheck>();
        downCollider = Instantiate(new Prefab("TrafficColliderCheck"), new Vector3(transPos.x - 0.19f, transPos.y - 0.55f, 0f)).GetComponent<TrafficColliderCheck>();

        spawnCheckCollide = new List<uint>();
    }

    //public void RequestSwap(bool inState)
    //{
    //    if (state != inState)
    //        toState = inState;
    //}

    public void RequestChange(DirectionState requestDirec)
    {
        if (!reqeusting && carCounter == 0)
        {
            timer = 0f;
            nextState = requestDirec;
            directionState = DirectionState.None;
            Debug.Log("Reqeust switch");
            reqeusting = true;
        }
    }

    private void SwapState()
    {

        //if (directionState == DirectionState.Horizontal) nextState = DirectionState.Vertical;
        //else if (directionState == DirectionState.Vertical) nextState = DirectionState.Horizontal;

        if (directionState == DirectionState.Up) nextState = DirectionState.Left;
        else if (directionState == DirectionState.Left) nextState = DirectionState.Down;
        else if (directionState == DirectionState.Down) nextState = DirectionState.Right;
        else if (directionState == DirectionState.Right) nextState = DirectionState.Up;

        //if (directionState == DirectionState.Horizontal) nextState = DirectionState.HorizontalLeft;
        //else if (directionState == DirectionState.HorizontalLeft) nextState = DirectionState.Vertical;
        //else if (directionState == DirectionState.Vertical) nextState = DirectionState.VerticalLeft;
        //else if (directionState == DirectionState.VerticalLeft) nextState = DirectionState.Horizontal;

        directionState = DirectionState.None;

        
        //Debug.Log("After " + directionState + " " + entityId);
    }

    public override void Update()
    {
        //if (carCounter == 0)
        //    Debug.Log(carCounter);
        float deltaTime = Time.deltaTime;
        //Console.WriteLine("State " + directionState);
        //if (Input.GetKeyDown(KeyCode.V))
        //    SwapState();
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
            //if (carCounter == 0 && timer >= switchTimer * 1.5f)
            timer = 0f;
            SwapState();
        }
        //Debug.Log(nextState);
        //Put traffic light in a state where cars are not allowed to go for both direction
        if (directionState == DirectionState.None)
        {
            inBetweenTimer += deltaTime;
            //if (inBetweenTimer >= 0.5f)
            if (inBetweenTimer >= 1.5f || carCounter == 0)
            //if (carCounter == 0)
            {
                //toState = state = !state;
                //state = !state;
                //if (state)
                //    transform.angle = 0;
                ////texture.color = new Color(1, 0, 0, 1);
                //else
                //    transform.angle = 90;

                directionState = nextState;
                //if (nextState == DirectionState.Horizontal || nextState == DirectionState.HorizontalLeft)
                if (nextState == DirectionState.Left || nextState == DirectionState.Right)
                    transform.angle = 0;
                else
                    transform.angle = 90;
                inBetweenTimer = 0f;
            }

            //reqeusting = false;
        }
        //if (Input.GetKeyDown(KeyCode.C))
        //{
        //    SwapState();
        //}
    }

    //True = just spawn and ignore traffic light 
    //False = look at traffic light state
    public bool CheckIfJustSpawn(uint toCheck)
    {
        if (spawnCheck && spawnCheckCollide.Contains(toCheck))
        {
            spawnCheckCollide.Remove(toCheck);
            if (spawnCheckCollide.Count == 0) spawnCheck = false;
            return true;
        }
        return false;
    }

    public override void OnTriggerEnter(uint entId)
    {
        ++carCounter;
        //Debug.Log("The id is " + id);
        if (spawnCheck) spawnCheckCollide.Add(entId);
    }

    public override void OnTriggerExit(uint entId)
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

