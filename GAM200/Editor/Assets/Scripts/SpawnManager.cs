using System;
using System.Collections;
using System.Collections.Generic;

public class SpawnManager : MonoBehaviour
{
    public PlacementManager placementManager;
    public StructureManager structureManager;
    public RoadManager roadManager;
    //public ScoreSystem scoreSystem;

    private Vector2Int randomRoadPosition;

    private int scoreToSpawn;
    int score;
    //float timer;
    //float maxTimer;

    GameState gameState;

    

    ButtonRoad buttonRoad;

    public override void Start()
    {
        placementManager = GameObject.Find("PlacementManager").GetComponent<PlacementManager>();
        structureManager = GameObject.Find("StructureManager").GetComponent<StructureManager>();
        roadManager = GameObject.Find("RoadManager").GetComponent<RoadManager>();
        gameState = GameObject.Find("GameManager").GetComponent<GameState>();

        scoreToSpawn = 0;
        buttonRoad = GameObject.Find("ButtonRoad").GetComponent<ButtonRoad>();


        bool checkForNoSpawn = true;
        while (checkForNoSpawn)
        {
            Vector2Int roadPosition = SpawnRandomRoad();
            Vector2Int roadPosition2 = SpawnRandomRoad();

            structureManager.PlaceHouse(roadPosition, 0);
            structureManager.PlaceSpecial(roadPosition2, 0);
 
            if (placementManager.placementGrid.GetAllHouses().Count != 0 && placementManager.placementGrid.GetAllSpecialStructure().Count != 0)
            {

                checkForNoSpawn = false;
                scoreToSpawn += 5;
                break;
            }
        }
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

    public void CheckPosition()
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

            structureManager.PlaceHouse(roadPosition, 0);
            structureManager.PlaceSpecial(roadPosition2, 0);

                //structureManager.PlaceHouse(housePosition);
                scoreToSpawn += 5;
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
        if (Input.GetKeyDown(KeyCode.N))
        {
            CheckPosition();
        }
        score = gameState.GetScore();
        if (score == scoreToSpawn)
        {
            if(score == 10)
            {
                buttonRoad.RevealTraffic();
            }

            else if (score == 15)
            {
                buttonRoad.RevealERP();
            }

            CheckPosition();
            //if (checkForNoSpawn)
            //{
            //    while (checkForNoSpawn)
            //    {
            //        if (placementManager.placementGrid.GetAllHouses().Count != 0 && placementManager.placementGrid.GetAllSpecialStructure().Count != 0)
            //        {
            //            checkForNoSpawn = false;
            //            break;
            //        }
            //
            //        Vector2Int roadPosition = SpawnRandomRoad();
            //        //Vector2Int housePosition = SpawnRandomHouse(roadPosition);
            //        Vector2Int roadPosition2 = SpawnRandomRoad();
            //
            //        if (placementManager.GetNeighboursOfTypeFor(roadPosition, CellType.Empty).Count == 4)
            //        {
            //            roadManager.PlaceSpawnHouse(roadPosition);
            //            roadManager.PlaceSpawnDestination(roadPosition2);
            //        }
            //        
            //    }
            //}
        }
    }
}
