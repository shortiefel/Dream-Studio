using System;
using System.Collections;
using System.Collections.Generic;

public enum SpawnRequestType
{
    Both = 0,
    House,
    Destination
}

enum SpawnState
{
    Peak = 0,
    Relax,
    BuildUp
}
public class SpawnManager : MonoBehaviour
{
    public PlacementManager placementManager;
    public StructureManager structureManager;
    public RoadManager roadManager;
    //public ScoreSystem scoreSystem;

    private Vector2Int randomRoadPosition;

    private float spawnTimer;
    private float spawnTimerMax;

    private float spawnTimerPeak;
    private float spawnTimerRelax;

    private float stateChangeTimer;
    private float stateChangeMax;
    SpawnState spawnState;

    //int score;
    //float timer;
    //float maxTimer;

    GameState gameState;

    //SpawnRequestType spawnRequestType;
    SpawnRequestType[] spawnRequestOrder;
    int spawnRequestIndex;
    int noOfSpawnRequestOrder;

    int attemptLoopCount;

    float dt;

    //ButtonRoad buttonRoad;
    bool testTobeDeletedBool = false;
    public override void Start()
    {
        placementManager = GameObject.Find("PlacementManager").GetComponent<PlacementManager>();
        structureManager = GameObject.Find("StructureManager").GetComponent<StructureManager>();
        roadManager = GameObject.Find("RoadManager").GetComponent<RoadManager>();
        gameState = GameObject.Find("GameManager").GetComponent<GameState>();

        spawnTimer = 0f;
        spawnTimerMax = spawnTimerRelax = 15f;
        spawnTimerPeak = 5f;

        stateChangeTimer = 0f;
        stateChangeMax = 20f;

        spawnState = SpawnState.BuildUp;

        Vector2Int roadPosition = SpawnRandomRoad();
        //Vector2Int roadPosition2 = SpawnRandomRoad(); //For random destination spawn

        structureManager.PlaceHouse(roadPosition, 0);
        //structureManager.PlaceSpecial(roadPosition2, 0); //For random destination spawn


        //Check if have 1 house and 1 destination to start off
        while (true)
        {

            //if (placementManager.placementGrid.GetAllHouses().Count != 0 && placementManager.placementGrid.GetAllSpecialStructure().Count != 0) //For random destination spawn
            if (placementManager.placementGrid.GetAllHouses().Count != 0) //For Controlled destination spawn
            {
                break;
            }

            if (placementManager.placementGrid.GetAllHouses().Count == 0)
            {
                roadPosition = SpawnRandomRoad();
                structureManager.PlaceHouse(roadPosition, 0);
            }

            //For random destination spawn
            //if (placementManager.placementGrid.GetAllSpecialStructure().Count == 0)
            //{
            //    roadPosition2 = SpawnRandomRoad();
            //    structureManager.PlaceSpecial(roadPosition2, 0);
            //}
        }

        noOfSpawnRequestOrder = 3;
        spawnRequestOrder = new SpawnRequestType[noOfSpawnRequestOrder];
        spawnRequestOrder[0] = SpawnRequestType.Destination;
        spawnRequestOrder[1] = SpawnRequestType.House;
        spawnRequestOrder[2] = SpawnRequestType.Destination;
        spawnRequestIndex = 0;

        attemptLoopCount = 0;
    }

    private Vector2Int SpawnRandomRoad()
    {

        Vector2Int startPoint = placementManager.placementGrid.GetStartPoint();
        Vector2Int endPoint = placementManager.placementGrid.GetGridSize() + startPoint;

        int randomX = Random.Range(startPoint.x + 1, endPoint.x - 2);
        int randomY = Random.Range(startPoint.y + 1, endPoint.y - 2);

        randomRoadPosition.x = randomX;
        randomRoadPosition.y = randomY;

        return randomRoadPosition;
    }


    //Spawn Houses and destinations
    public bool CheckPosition(SpawnRequestType srt = SpawnRequestType.Both)
    {
        Vector2Int roadPosition = SpawnRandomRoad();
        Vector2Int roadPosition2 = SpawnRandomRoad();
     
        switch (srt) {
            case SpawnRequestType.Both:
                return structureManager.PlaceHouse(roadPosition, 0) && structureManager.PlaceSpecial(roadPosition2, 0);

            case SpawnRequestType.House:
                return structureManager.PlaceHouse(roadPosition, 0);

            case SpawnRequestType.Destination:
                return structureManager.PlaceSpecial(roadPosition2, 0);
        }

        //If cant find just end, as there is a chance of infinite loop
        return true;


    }

    public override void Update()
    {
        if (Input.GetKeyDown(KeyCode.N) && Input.GetKey(KeyCode.Shift))
        {
            CheckPosition(SpawnRequestType.Destination);
        }

        if (Input.GetKeyDown(KeyCode.J) && Input.GetKey(KeyCode.Shift))
        {
            CheckPosition(SpawnRequestType.House);
        }

        dt = Time.deltaTime;

        stateChangeTimer += dt;
        if (stateChangeTimer > stateChangeMax)
        {
            stateChangeTimer = 0f;
            SwapSpawnState();
        }

        if (spawnState == SpawnState.BuildUp)
        {
            spawnTimerMax -= dt;
            if (spawnTimerMax < spawnTimerPeak)
            {
                spawnTimerMax = spawnTimerPeak;
            }
        }

        if (Input.GetKeyDown(KeyCode.X))
        {
            testTobeDeletedBool = !testTobeDeletedBool;
            if (testTobeDeletedBool) Debug.Log("Spawn Disable");
            else if (!testTobeDeletedBool) Debug.Log("Spawn Enable");
        }
        if (!testTobeDeletedBool)
           spawnTimer += dt;
        if (spawnTimer > spawnTimerMax)
        {
            if (CheckPosition(spawnRequestOrder[spawnRequestIndex]))
            {
                ++spawnRequestIndex;
                spawnRequestIndex = spawnRequestIndex % noOfSpawnRequestOrder;
                //Debug.Log("Next index is " + spawnRequestIndex);
                spawnTimer = 0f;
                attemptLoopCount = 0;
            }
            else
            {
                ++attemptLoopCount;

                if (attemptLoopCount > 10)
                {
                    //Debug.Log("Expand grid");
                    //placementManager.placementGrid.Expand();
                    gameState.ExpandGrid();

                    attemptLoopCount = 0;
                }
            }
        }

        //Debug.Log(spawnState + " state change from " + stateChangeTimer + " til " + stateChangeMax + " Spawn " + spawnTimer + " til " + spawnTimerMax);
        //if (score == scoreToSpawn)
        //{
        //    //if(score == 10)
        //    //{
        //    //    buttonRoad.RevealTraffic();
        //    //}
        //    //
        //    //else if (score == 15)
        //    //{
        //    //    buttonRoad.RevealERP();
        //    //}
        //
        //    CheckPosition();
        //    //if (checkForNoSpawn)
        //    //{
        //    //    while (checkForNoSpawn)
        //    //    {
        //    //        if (placementManager.placementGrid.GetAllHouses().Count != 0 && placementManager.placementGrid.GetAllSpecialStructure().Count != 0)
        //    //        {
        //    //            checkForNoSpawn = false;
        //    //            break;
        //    //        }
        //    //
        //    //        Vector2Int roadPosition = SpawnRandomRoad();
        //    //        //Vector2Int housePosition = SpawnRandomHouse(roadPosition);
        //    //        Vector2Int roadPosition2 = SpawnRandomRoad();
        //    //
        //    //        if (placementManager.GetNeighboursOfTypeFor(roadPosition, CellType.Empty).Count == 4)
        //    //        {
        //    //            roadManager.PlaceSpawnHouse(roadPosition);
        //    //            roadManager.PlaceSpawnDestination(roadPosition2);
        //    //        }
        //    //        
        //    //    }
        //    //}
        //}
    }

    void SwapSpawnState()
    {
        switch (spawnState)
        {
            case SpawnState.BuildUp:
                {
                    spawnTimerMax = spawnTimerPeak;
                    spawnState = SpawnState.Peak;
                    //Debug.Log("SpawnManager SpawnState: BuildUp change to Peak");
                    break;
                }
            case SpawnState.Peak:
                {
                    spawnTimerMax = spawnTimerRelax;
                    spawnState = SpawnState.Relax;
                    //Debug.Log("SpawnManager SpawnState: Peak change to Relax");
                    break;
                }
            case SpawnState.Relax:
                {
                    spawnState = SpawnState.BuildUp;
                    //Debug.Log("SpawnManager SpawnState: Relax change to BuildUp");
                    break;
                }
        }
    }
}
