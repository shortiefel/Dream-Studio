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

    //private void Start()
    public override void Start()
    {
        roadFixer = GetComponent<RoadFixer>();
        placementManager = GameObject.Find("PlacementManager").GetComponent<PlacementManager>();
        structureManager = GameObject.Find("StructureManager").GetComponent<StructureManager>();
        temporaryPlacementPositions = new List<Vector2Int>();
        roadPositionsToRecheck = new List<Vector2Int>();

        placementMode = false;
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

        var spawnRoad = Instantiate(roadFixer.deadEnd, transform);

        int random = Random.Range(0, 3);
        int rotate = 0;

        int randomX = position.x;
        int randomY = position.y;

        if (random == 0)
        {
            rotate = 0;
            randomDestinationPosition.x = randomX;
            randomDestinationPosition.y = randomY + 1;
        }
        else if (random == 1)
        {
            rotate = 90;
            randomDestinationPosition.x = randomX - 1;
            randomDestinationPosition.y = randomY;
        }
        else if (random == 2)
        {
            rotate = 180;
            randomDestinationPosition.x = randomX;
            randomDestinationPosition.y = randomY - 1;
        }
        else if (random == 3)
        {
            rotate = 270;
            randomDestinationPosition.x = randomX + 1;
            randomDestinationPosition.y = randomY;
        }

        float rotation = rotate;

        spawnRoad.transform.angle = rotation;

        placementManager.PlaceTemporaryStructure(position, spawnRoad, CellType.Road, 1);
        structureManager.PlaceHouse(randomDestinationPosition);

        placementManager.AddtemporaryStructuresToStructureDictionary();
        temporaryPlacementPositions.Clear();
        startPosition = Vector2Int.zero;
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

        var spawnRoad = Instantiate(roadFixer.deadEnd, transform);

        int random = Random.Range(0, 3);
        int rotate = 0;

        int randomX = position.x;
        int randomY = position.y;

        if (random == 0)
        {
            rotate = 0;
            randomDestinationPosition.x = randomX;
            randomDestinationPosition.y = randomY + 1;
        }
        else if (random == 1)
        {
            rotate = 90;
            randomDestinationPosition.x = randomX - 1;
            randomDestinationPosition.y = randomY;
        }
        else if (random == 2)
        {
            rotate = 180;
            randomDestinationPosition.x = randomX;
            randomDestinationPosition.y = randomY - 1;
        }
        else if (random == 3)
        {
            rotate = 270;
            randomDestinationPosition.x = randomX + 1;
            randomDestinationPosition.y = randomY;
        }

        float rotation = rotate;

        spawnRoad.transform.angle = rotation;

        placementManager.PlaceTemporaryStructure(position, spawnRoad, CellType.Road, 1);
        structureManager.PlaceSpecial(randomDestinationPosition);

        placementManager.AddtemporaryStructuresToStructureDictionary();
        temporaryPlacementPositions.Clear();
        startPosition = Vector2Int.zero;
    }

    public void PlaceRoad(Vector2Int position)
    {
        //Debug.Log("here");
        if (placementManager.CheckIfPositionInBound(position) == false)
            return;
        if (placementManager.CheckIfPositionIsFree(position) == false)
            return;
        if (placementMode == false)
        {
            temporaryPlacementPositions.Clear();
            roadPositionsToRecheck.Clear();

            placementMode = true;
            startPosition = position;
            Debug.Log(position);

            temporaryPlacementPositions.Add(position);
            placementManager.PlaceTemporaryStructure(position, roadFixer.deadEnd, CellType.Road, 1);
            //Console.WriteLine("call function");

        }
        else
        {
            //Console.WriteLine("call function2222222222");
            placementManager.RemoveAllTemporaryStructures();
            temporaryPlacementPositions.Clear();

            foreach (var positionsToFix in roadPositionsToRecheck)
            {
                roadFixer.FixRoadAtPosition(placementManager, positionsToFix);
            }

            roadPositionsToRecheck.Clear();

            temporaryPlacementPositions = placementManager.GetPathBetween(startPosition, position);

            foreach (var temporaryPosition in temporaryPlacementPositions)
            {
                if (placementManager.CheckIfPositionIsFree(temporaryPosition) == false)
                {
                    roadPositionsToRecheck.Add(temporaryPosition);
                    continue;
                }
                placementManager.PlaceTemporaryStructure(temporaryPosition, roadFixer.deadEnd, CellType.Road, 1);
            }
        }

        FixRoadPrefabs();

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
    }
}