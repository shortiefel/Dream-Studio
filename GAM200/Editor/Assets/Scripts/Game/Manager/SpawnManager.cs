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

        Vector2Int roadPosition = SpawnRandomRoad();
        Vector2Int roadPosition2 = SpawnRandomRoad();

        //roadPosition = new Vector2Int(1, 1);
        //roadPosition2 = new Vector2Int(7, 3);
        //
        //spawnState = SpawnState.BuildUp;
        //
        structureManager.PlaceHouse(roadPosition, 0);
        structureManager.PlaceSpecial(roadPosition2, 0);

        //-------------------------------
        //placementManager.placementGrid.Expand();
        //
        //Vector2Int roadPositionT = new Vector2Int(7, 0);
        //structureManager.PlaceHouse(roadPositionT, 0);
        //roadPositionT = new Vector2Int(9, 4);
        //structureManager.PlaceHouse(roadPositionT, 0);
        //
        //roadPositionT = new Vector2Int(7, 7);
        //structureManager.PlaceSpecial(roadPositionT, 0);
        //roadPositionT = new Vector2Int(4, 4);
        //structureManager.PlaceSpecial(roadPositionT, 0);
        //while (true)
        //{
        //
        //    if (placementManager.placementGrid.GetAllHouses().Count >= 2 && placementManager.placementGrid.GetAllSpecialStructure().Count >= 5)
        //    {
        //        break;
        //    }
        //    //Debug.Log("Failed full spawn");
        //
        //    if (placementManager.placementGrid.GetAllHouses().Count < 3)
        //    {
        //        //Debug.Log("Spawn Fix House");
        //        roadPosition = SpawnRandomRoad();
        //        structureManager.PlaceHouse(roadPosition, 0);
        //    }
        //
        //    if (placementManager.placementGrid.GetAllSpecialStructure().Count < 6)
        //    {
        //        roadPosition2 = SpawnRandomRoad();
        //        structureManager.PlaceSpecial(roadPosition2, 0);
        //    }
        //}
        //-------------------------------

        //Check if have 1 house and 1 destination to start off
        while (true)
        {

            if (placementManager.placementGrid.GetAllHouses().Count != 0 && placementManager.placementGrid.GetAllSpecialStructure().Count != 0)
            {
                break;
            }
            //Debug.Log("Failed full spawn");

            if (placementManager.placementGrid.GetAllHouses().Count == 0)
            {
                //Debug.Log("Spawn Fix House");
                roadPosition = SpawnRandomRoad();
                structureManager.PlaceHouse(roadPosition, 0);
            }

            if (placementManager.placementGrid.GetAllSpecialStructure().Count == 0)
            {
                roadPosition2 = SpawnRandomRoad();
                structureManager.PlaceSpecial(roadPosition2, 0);
            }
        }

        //scoreToSpawn = 1000;
        //spawnRequestType = SpawnRequestType.House;

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
        /*int width = placementManager.width;
        int height = placementManager.height;

        int randomX = Random.Range(1, width - 2);
        int randomY = Random.Range(1, height - 2);

        randomRoadPosition.x = randomX;
        randomRoadPosition.y = randomY;

        return randomRoadPosition;*/

        Vector2Int startPoint = placementManager.placementGrid.GetStartPoint();
        Vector2Int endPoint = placementManager.placementGrid.GetGridSize() + startPoint;

        int randomX = Random.Range(startPoint.x + 1, endPoint.x - 2);
        int randomY = Random.Range(startPoint.y + 1, endPoint.y - 2);

        randomRoadPosition.x = randomX;
        randomRoadPosition.y = randomY;

        return randomRoadPosition;
    }

    //private Vector2Int SpawnRandomHouse(Vector2Int roadPosition)
    //{
    //    //float roadRotation = roadManager.rotate;

    //    //use boolean

    //    //Debug.Log(roadRotation);

    //    //int randomX = UnityEngine.Random.Range(roadPosition.x - 1, roadPosition.x + 1);
    //    ////int randomX = UnityEngine.Random.Range(0, 2) == 0 ? roadPosition.x - 1 : roadPosition.x + 1;
    //    ////int randomY = UnityEngine.Random.Range(roadPosition.y - 1, roadPosition.y + 1);
    //    ////int randomY = UnityEngine.Random.Range(0, 2) == 0 ? roadPosition.y - 1 : roadPosition.y + 1;
    //    //int randomY = roadPosition.y;

    //    //if (randomX == roadPosition.x)
    //    //{
    //    //    randomY = UnityEngine.Random.Range(0, 1) == 0 ? roadPosition.y - 1 : roadPosition.y + 1;
    //    //}
    //    //else if (randomX == roadPosition.x - 1)
    //    //{
    //    //    randomY = roadPosition.y;
    //    //}
    //    //else if (randomX == roadPosition.x + 1)
    //    //{
    //    //    randomY = roadPosition.y;
    //    //}

    //    //randomHousePosition.x = randomX;
    //    //randomHousePosition.y = randomY;

    //    int randomX = roadPosition.x;
    //    int randomY = roadPosition.y;

    //    //if (roadRotation == 0)
    //    //{
    //    //    randomHousePosition.x = randomX;
    //    //    randomHousePosition.y = randomY + 1;
    //    //}
    //    //else if (roadRotation == 90)
    //    //{
    //    //    randomHousePosition.x = randomX - 1;
    //    //    randomHousePosition.y = randomY;
    //    //}
    //    //else if (roadRotation == 180)
    //    //{
    //    //    randomHousePosition.x = randomX;
    //    //    randomHousePosition.y = randomY - 1;
    //    //}
    //    //else if (roadRotation == 270)
    //    //{
    //    //    randomHousePosition.x = randomX + 1;
    //    //    randomHousePosition.y = randomY;
    //    //}


    //    return randomHousePosition;
    //}

    //Spawn Houses and destinations
    public bool CheckPosition(SpawnRequestType srt = SpawnRequestType.Both)
    {
        Vector2Int roadPosition = SpawnRandomRoad();
        //Vector2Int housePosition = SpawnRandomHouse(roadPosition);
        Vector2Int roadPosition2 = SpawnRandomRoad();
        //Debug.Log("Randomised position is " + roadPosition);
        //Debug.Log("Randomised position is " + roadPosition2);
        //if (placementManager.GetNeighboursOfTypeFor(roadPosition, CellType.Empty).Count == 4)
        //{
        //if (score == scoreToSpawn)
        //{
        //Debug.Log(housePosition.x);
        //Debug.Log(housePosition.y);
        switch (srt) {
            case SpawnRequestType.Both:
                return structureManager.PlaceHouse(roadPosition, 0) && structureManager.PlaceSpecial(roadPosition2, 0);

            case SpawnRequestType.House:
                //spawnRequestType = SpawnRequestType.Destination;
                return structureManager.PlaceHouse(roadPosition, 0);

            case SpawnRequestType.Destination:
                //spawnRequestType = SpawnRequestType.House;
                return structureManager.PlaceSpecial(roadPosition2, 0);
        }

        //If cant find just end, as there is a chance of infinite loop
        return true;
                //structureManager.PlaceHouse(housePosition);
                //scoreToSpawn += 5;
            //}
        //}

    }

    //public override void Update()
    //{
    //    timer += Time.deltaTime;
    //    if (timer > maxTimer)
    //    {

    //        CheckPosition();
    //        Debug.Log("hous espawner");

    //        timer = 0f;
    //    }
    //}

    public override void Update()
    {
        if (Input.GetKeyDown(KeyCode.N) && Input.GetKey(KeyCode.Shift))
        {
            CheckPosition();
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

        if (Input.GetKey(KeyCode.R)) return;
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
