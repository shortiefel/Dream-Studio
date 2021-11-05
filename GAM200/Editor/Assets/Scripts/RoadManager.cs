using System;
using System.Collections;
using System.Collections.Generic;

public class RoadManager : MonoBehaviour
{
    public PlacementManager placementManager;

    public List<Vector2Int> temporaryPlacementPositions = new List<Vector2Int>();
    public List<Vector2Int> roadPositionsToRecheck = new List<Vector2Int>();

    private Vector2Int startPosition;
    private bool placementMode = false;

    public RoadFixer roadFixer;

    //private void Start()
    public override void Start()
    {
        roadFixer = GetComponent<RoadFixer>();
        placementManager = GetComponent<PlacementManager>();
    }

    public void PlaceRoad(Vector2Int position)
    {
        Debug.Log("here");
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
            placementManager.PlaceTemporaryStructure(position, roadFixer.deadEnd, CellType.Road);
            Debug.Log("call function");

        }
        else
        {
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
                placementManager.PlaceTemporaryStructure(temporaryPosition, roadFixer.deadEnd, CellType.Road);
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
        Debug.Log("Something");
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