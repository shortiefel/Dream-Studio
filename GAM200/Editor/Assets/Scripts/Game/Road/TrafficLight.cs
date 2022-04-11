﻿using System;
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

    static public DirectionState directionState = DirectionState.Up;
    static public DirectionState nextState;

    private int carCounter;

    //private Texture texture;

    static public float timer = 0f;
    static public float switchTimer = 2f;

    static public float inBetweenTimer;

    //private float secondaryTimer;

    private TrafficLightManager tlm;

    bool reqeusting = false;

    public TrafficColliderCheck leftCollider;
    public TrafficColliderCheck rightCollider;
    public TrafficColliderCheck upCollider;
    public TrafficColliderCheck downCollider;

    bool spawnCheck = true;
    List<uint> spawnCheckCollide;

    static public bool changeState = false;

    public override void Start()
    {
        //Debug.Log("Making new start -----------------------------------");
        //directionState = DirectionState.Horizontal;
        //directionState 
        //transform.angle = 90;

        if (directionState == DirectionState.Left || directionState == DirectionState.Right)
            transform.angle = 0;
        else
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
            //Debug.Log("Reqeust switch");
            reqeusting = true;
        }
    }

    static public void SwapState()
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

        //directionState = DirectionState.None;
        changeState = true;
        
        //Debug.Log("After " + directionState + " " + entityId);
    }

    public override void Update()
    {
        //Debug.Log(inBetweenTimer + " " + directionState);
        if (inBetweenTimer >= 1.4f)
        //if (inBetweenTimer >= 1.5f || carCounter == 0)
        //if (carCounter == 0)
        {
            //toState = state = !state;
            //state = !state;
            //if (state)
            //    transform.angle = 0;
            ////texture.color = new Color(1, 0, 0, 1);
            //else
            //    transform.angle = 90;

            if (nextState == DirectionState.Left || nextState == DirectionState.Right)
                transform.angle = 0;
            else
                transform.angle = 90;
        }
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

