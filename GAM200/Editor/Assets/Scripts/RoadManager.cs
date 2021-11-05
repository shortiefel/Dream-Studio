using System;
using System.Collections;
using System.Collections.Generic;

public class RoadManager : MonoBehaviour
{

    private static List<Vector2Int> temporaryPlacementPositions = new List<Vector2Int>();
    private static List<Vector2Int> roadPositionsToRecheck = new List<Vector2Int>();

    private static Vector2Int startPosition;
    private static bool placementMode = false;

    PlacementManager placementManager;
    RoadFixer roadFixer;
    RoadManager roadManager;

    //private void Start()
    public override void Start()
    {
        roadManager = GetComponent<RoadManager>();
        placementManager = GameObject.Find("PlacementManager").GetComponent<PlacementManager>();
        roadFixer = GetComponent<RoadFixer>();
    }

    public void PlaceRoad(Vector2Int position)
    {
        Debug.Log("here");
        if (PlacementManager.CheckIfPositionInBound(position) == false)
            return;
        if (PlacementManager.CheckIfPositionIsFree(position) == false)
            return;
        if (placementMode == false)
        {
            temporaryPlacementPositions.Clear();
            roadPositionsToRecheck.Clear();

            placementMode = true;
            startPosition = position;
            Debug.Log(position);

            temporaryPlacementPositions.Add(position);
            placementManager.PlaceTemporaryStructure(position, RoadFixer.deadEnd, CellType.Road);
            Debug.Log("call function");

        }
        else
        {
            placementManager.RemoveAllTemporaryStructures();
            temporaryPlacementPositions.Clear();

            foreach (var positionsToFix in roadPositionsToRecheck)
            {
                RoadFixer.FixRoadAtPosition(placementManager, positionsToFix);
            }

            roadPositionsToRecheck.Clear();

            temporaryPlacementPositions = placementManager.GetPathBetween(startPosition, position);

            foreach (var temporaryPosition in temporaryPlacementPositions)
            {
                if (PlacementManager.CheckIfPositionIsFree(temporaryPosition) == false)
                {
                    roadPositionsToRecheck.Add(temporaryPosition);
                    continue;
                }
                placementManager.PlaceTemporaryStructure(temporaryPosition, RoadFixer.deadEnd, CellType.Road);
            }
        }

        roadManager.FixRoadPrefabs();

    }

    private void FixRoadPrefabs()
    {
        foreach (var temporaryPosition in temporaryPlacementPositions)
        {
            RoadFixer.FixRoadAtPosition(placementManager, temporaryPosition);
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
            RoadFixer.FixRoadAtPosition(placementManager, positionToFix);
        }
    }

    public void FinishPlacingRoad()
    {
        placementMode = false;
        PlacementManager.AddtemporaryStructuresToStructureDictionary();
        if (temporaryPlacementPositions.Count > 0)
        {
            //AudioPlayer.instance.PlayPlacementSound();
        }
        temporaryPlacementPositions.Clear();
        startPosition = Vector2Int.zero;
    }
}