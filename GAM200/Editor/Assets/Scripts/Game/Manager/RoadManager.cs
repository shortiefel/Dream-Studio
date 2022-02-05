using System;
using System.Collections;
using System.Collections.Generic;

public class RoadManager : MonoBehaviour
{
    public PlacementManager placementManager;
    public RoadFixer roadFixer;
    public StructureManager structureManager;

    public List<Vector2Int> temporaryPlacementPositions;
    public List<Vector2Int> roadPositionsToRecheck;

    private Vector2Int startPosition;
    private Vector2Int randomDestinationPosition;
    private bool placementMode;

    private AudioSource placeSound;
    private AudioSource removeSound;

    //private GameObject trafficLightGO;
    //private GameObject erpGO;
    private TrafficLightManager trafficLightManager;
    private ERPManager erpManager;

    //private void Start()
    public override void Start()
    {
        roadFixer = GetComponent<RoadFixer>();
        placementManager = GameObject.Find("PlacementManager").GetComponent<PlacementManager>();
        structureManager = GameObject.Find("StructureManager").GetComponent<StructureManager>();
        temporaryPlacementPositions = new List<Vector2Int>();
        roadPositionsToRecheck = new List<Vector2Int>();

        placementMode = false;

        placeSound = GameObject.Find("DrawRoad").GetComponent<AudioSource>();
        removeSound = GameObject.Find("RemoveRoad").GetComponent<AudioSource>();


        //trafficLightGO = new GameObject(new Prefab("TrafficLight"));
        //erpGO = new GameObject(new Prefab("ERP"));

        trafficLightManager = GameObject.Find("TrafficManager").GetComponent<TrafficLightManager>();
        erpManager = GameObject.Find("ERPManager").GetComponent<ERPManager>();
    }

    public void PlaceSpawnHouse(Vector2Int position)
    {
        if (placementManager.CheckIfPositionInBound(position) == false)
            return;
        if (placementManager.CheckIfPositionIsFree(position) == false)
            return;

        temporaryPlacementPositions.Clear();
        roadPositionsToRecheck.Clear();

        startPosition = position;
        //Debug.Log(position);

        temporaryPlacementPositions.Add(position);

        int random = Random.Range(0, 3);
        int structureRotate = 0;
        int roadRotate = 0;

        int randomX = position.x;
        int randomY = position.y;

        if (random == 0)
        {
            structureRotate = 0;
            roadRotate = 180;
            randomDestinationPosition.x = randomX;
            randomDestinationPosition.y = randomY + 1;
        }
        else if (random == 1)
        {
            structureRotate = 90;
            roadRotate = 270;
            randomDestinationPosition.x = randomX - 1;
            randomDestinationPosition.y = randomY;
        }
        else if (random == 2)
        {
            structureRotate = 180;
            roadRotate = 0;
            randomDestinationPosition.x = randomX;
            randomDestinationPosition.y = randomY - 1;
        }
        else if (random == 3)
        {
            structureRotate = 270;
            roadRotate = 90;
            randomDestinationPosition.x = randomX + 1;
            randomDestinationPosition.y = randomY;
        }

        placementManager.PlaceTemporaryStructure(position, roadFixer.deadEnd, CellType.Road, 1, false, roadRotate);
        structureManager.PlaceHouse(randomDestinationPosition, structureRotate);

        placementManager.AddtemporaryStructuresToStructureDictionary();
        temporaryPlacementPositions.Clear();
        //startPosition = Vector2Int.zero;

        //foreach (var positionsToFix in roadPositionsToRecheck)
        //{
        //    roadFixer.FixRoadAtPosition(placementManager, positionsToFix);
        //}

        //roadPositionsToRecheck.Clear();

        //temporaryPlacementPositions = placementManager.GetPathBetween(startPosition, position);

        //foreach (var temporaryPosition in temporaryPlacementPositions)
        //{
        //    if (placementManager.CheckIfPositionIsFree(temporaryPosition) == false)
        //    {
        //        roadPositionsToRecheck.Add(temporaryPosition);
        //        continue;
        //    }
        //    placementManager.PlaceTemporaryStructure(temporaryPosition, roadFixer.deadEnd, CellType.Road, 1);
        //}

        FixRoadPrefabs();
    }

    public void PlaceSpawnDestination(Vector2Int position)
    {
        if (placementManager.CheckIfPositionInBound(position) == false)
            return;
        if (placementManager.CheckIfPositionIsFree(position) == false)
            return;

        temporaryPlacementPositions.Clear();
        roadPositionsToRecheck.Clear();

        startPosition = position;
        //Debug.Log(position);

        temporaryPlacementPositions.Add(position);

        int random = Random.Range(0, 3);
        int structureRotate = 0;
        int roadRotate = 0;

        int randomX = position.x;
        int randomY = position.y;

        if (random == 0)
        {
            structureRotate = 0;
            roadRotate = 180;
            randomDestinationPosition.x = randomX;
            randomDestinationPosition.y = randomY + 1;
        }
        else if (random == 1)
        {
            structureRotate = 90;
            roadRotate = 270;
            randomDestinationPosition.x = randomX - 1;
            randomDestinationPosition.y = randomY;
        }
        else if (random == 2)
        {
            structureRotate = 180;
            roadRotate = 0;
            randomDestinationPosition.x = randomX;
            randomDestinationPosition.y = randomY - 1;
        }
        else if (random == 3)
        {
            structureRotate = 270;
            roadRotate = 90;
            randomDestinationPosition.x = randomX + 1;
            randomDestinationPosition.y = randomY;
        }

        placementManager.PlaceTemporaryStructure(position, roadFixer.deadEnd, CellType.Road, 1, false, roadRotate);
        structureManager.PlaceSpecial(randomDestinationPosition, structureRotate);

        placementManager.AddtemporaryStructuresToStructureDictionary();
        temporaryPlacementPositions.Clear();
        //startPosition = Vector2Int.zero;

        //foreach (var positionsToFix in roadPositionsToRecheck)
        //{
        //    roadFixer.FixRoadAtPosition(placementManager, positionsToFix);
        //}

        //roadPositionsToRecheck.Clear();

        //temporaryPlacementPositions = placementManager.GetPathBetween(startPosition, position);

        //foreach (var temporaryPosition in temporaryPlacementPositions)
        //{
        //    if (placementManager.CheckIfPositionIsFree(temporaryPosition) == false)
        //    {
        //        roadPositionsToRecheck.Add(temporaryPosition);
        //        continue;
        //    }
        //    placementManager.PlaceTemporaryStructure(temporaryPosition, roadFixer.deadEnd, CellType.Road, 1);
        //}

        FixRoadPrefabs();
    }

    public void PlaceRoad(Vector2Int position)
    {
        //Debug.Log("here");
        if (placementManager.CheckIfPositionInBound(position) == false)
            return;
        if (placementManager.CheckIfPositionIsFree(position) == false)
            return;
        //if (placementMode == false)
        //{
            temporaryPlacementPositions.Clear();
            roadPositionsToRecheck.Clear();

            //placementMode = true;
            startPosition = position;
            Debug.Log(position + " -----------------\n");

            temporaryPlacementPositions.Add(position);
            placementManager.PlaceTemporaryStructure(position, roadFixer.deadEnd, CellType.Road, 1);
            //Console.WriteLine("call function");

        //}
        //else
        //{
        //    //Console.WriteLine("call function2222222222");
        //    placementManager.RemoveAllTemporaryStructures();
        //    temporaryPlacementPositions.Clear();

        //    foreach (var positionsToFix in roadPositionsToRecheck)
        //    {
        //        roadFixer.FixRoadAtPosition(placementManager, positionsToFix);
        //    }

        //    roadPositionsToRecheck.Clear();

        //    temporaryPlacementPositions = placementManager.GetPathBetween(startPosition, position);

        //    foreach (var temporaryPosition in temporaryPlacementPositions)
        //    {
        //        if (placementManager.CheckIfPositionIsFree(temporaryPosition) == false)
        //        {
        //            roadPositionsToRecheck.Add(temporaryPosition);
        //            continue;
        //        }
        //        placementManager.PlaceTemporaryStructure(temporaryPosition, roadFixer.deadEnd, CellType.Road, 1);
        //    }
        //}

        FixRoadPrefabs();

    }

    public void FinishPlacingRoad()
    {
        //Debug.Log("Something");
        placementMode = false;
        placementManager.AddtemporaryStructuresToStructureDictionary();
        if (temporaryPlacementPositions.Count > 0)
        {
            //AudioPlayer.instance.PlayPlacementSound();
        }
        temporaryPlacementPositions.Clear();
        startPosition = Vector2Int.zero;

        placeSound.Play();
    }

    public void RemoveRoad(Vector2Int position)
    {

        if (placementManager.CheckIfPositionInBound(position) == false)
            return;

        if (trafficLightManager != null)
            trafficLightManager.RequestRemovingTrafficLight(position);
        if (erpManager != null)
            erpManager.RequestRemovingERP(position); 

        if (placementManager.CheckIfPositionIsFree(position) == false)
        {
            if (placementManager.CheckIfPositionIsOfType(position, CellType.Road))
            {
                //temporaryPlacementPositions.Clear();
                //roadPositionsToRecheck.Clear();
                placementManager.RemoveCurrentGrid(position);
                temporaryPlacementPositions.Add(position);
                //placementMode = false;
                removeSound.Play();
            }
        }

        FixRoadPrefabs();
    }

    public void FinishRemovingRoad()
    {
        //Debug.Log("Something");
        placementMode = false;
        placementManager.AddtemporaryStructuresToStructureDictionary();
        temporaryPlacementPositions.Clear();

        removeSound.Play();
    }

    private void FixRoadPrefabs()
    {
        foreach (var temporaryPosition in temporaryPlacementPositions)
        {
            roadFixer.FixRoadAtPosition(placementManager, temporaryPosition);
            var neighbours = placementManager.GetNeighboursOfTypeFor(temporaryPosition, CellType.Road);
            foreach (var roadposition in neighbours)
            {
                if (roadPositionsToRecheck.Contains(roadposition) == false)
                {
                    roadPositionsToRecheck.Add(roadposition);
                    Debug.Log(roadposition);
                }
            }
        }
        foreach (var positionToFix in roadPositionsToRecheck)
        {
            roadFixer.FixRoadAtPosition(placementManager, positionToFix);
        }
    }

    public void PlaceTrafficLight(Vector2Int position)
    {
        if(!placementManager.CheckIfPositionInBound(position))
            return;
        if(trafficLightManager != null)
            trafficLightManager.RequestPlacingTrafficLight(position);
    }

    public void PlaceERP(Vector2Int position)
    {
        if (!placementManager.CheckIfPositionInBound(position))
            return;
        if (erpManager != null)
            erpManager.RequestPlacingERP(position);
    }
}