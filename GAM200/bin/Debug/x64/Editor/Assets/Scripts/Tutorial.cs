using System;
using System.Collections.Generic;
using System.Linq;


public class Tutorial : MonoBehaviour
{
    public PlacementManager placementManager;
    public StructureManager structureManager;
    public RoadManager roadManager;
    //public ScoreSystem scoreSystem;

    //private Vector2Int randomRoadPosition;
    private Vector2Int roadPosition;
    private Vector2Int roadPosition2;

    //private int scoreToSpawn;
    //int score;
    //float timer;
    //float maxTimer;

    GameState gameState;

    public override void Start()
    {
        placementManager = GameObject.Find("PlacementManager").GetComponent<PlacementManager>();
        structureManager = GameObject.Find("StructureManager").GetComponent<StructureManager>();
        roadManager = GameObject.Find("RoadManager").GetComponent<RoadManager>();
        gameState = GameObject.Find("GameManager").GetComponent<GameState>();

        //scoreToSpawn = 0;

        //timer = 0f;
        //maxTimer = 2.0f;
        //maxTimer = 0.5f;
    }

    public void CheckPosition()
    {
        roadPosition.x = 7;
        roadPosition.y = 4;
        roadPosition2.x = 12;
        roadPosition2.y = 4;

        if (placementManager.GetNeighboursOfTypeFor(roadPosition, CellType.Empty).Count == 4)
        {
            //if (score == scoreToSpawn)
            //{
            //Debug.Log(housePosition.x);
            //Debug.Log(housePosition.y);

            roadManager.PlaceSpawnHouse(roadPosition);
            roadManager.PlaceSpawnDestination(roadPosition2);
        }

    }

    
}
