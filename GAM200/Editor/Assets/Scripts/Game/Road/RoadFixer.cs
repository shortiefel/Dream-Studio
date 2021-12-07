using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

public class RoadFixer : MonoBehaviour
{
    public GameObject deadEnd, roadStraight, corner, threeWay, fourWay;

    public override void Awake()
    {
        deadEnd = new GameObject(new Prefab("EndRoad"));
        roadStraight = new GameObject(new Prefab("StraightRoad"));
        corner = new GameObject(new Prefab("CurveRoad"));
        threeWay = new GameObject(new Prefab("ThreeWayRoad"));
        fourWay = new GameObject(new Prefab("FourWayRoad"));
    }
    public void FixRoadAtPosition(PlacementManager placementManager, Vector2Int temporaryPosition)
    {
        //[right, up, left, down]
        var result = placementManager.GetNeighbourTypesFor(temporaryPosition);
        int roadCount = 0;
        int houseCount = 0;
        int destinationCount = 0;
        //roadCount = result.Where(x => x == CellType.Road).Count();
        foreach (CellType x in result)
        {
            if (x == CellType.Road)
            {
                roadCount++;
                Debug.Log(roadCount);
            }
            else if (x == CellType.Structure)
            {
                houseCount++;
                Debug.Log(houseCount);
            }
            else if (x == CellType.SpecialStructure)
            {
                destinationCount++;
                Debug.Log(destinationCount);
            }
        }
        if ((roadCount == 0  && houseCount == 0 && destinationCount == 0) || (roadCount == 1 && houseCount == 0 && destinationCount == 0) ||
            (roadCount == 0 && houseCount == 1 && destinationCount == 0) || (roadCount == 0 && houseCount == 0 && destinationCount == 1))
        {
            CreateDeadEnd(placementManager, result, temporaryPosition);
        }
        else if ((roadCount == 2 && houseCount == 0 && destinationCount == 0) || (houseCount == 2 && roadCount == 0 && destinationCount == 0) || 
            (destinationCount == 2 && houseCount == 0 && roadCount == 0) || (roadCount == 1 && houseCount == 1) || 
            (roadCount == 1 && destinationCount == 1) || (houseCount == 1 && destinationCount == 1))
        {
            if (CreateStraightRoad(placementManager, result, temporaryPosition))
                return;
            CreateCorner(placementManager, result, temporaryPosition);
        }
        else if ((roadCount == 3 && houseCount == 0 && destinationCount == 0) || (roadCount == 2 && houseCount == 1) || 
            (roadCount == 2 && destinationCount == 1) ||
            (roadCount == 1 && houseCount == 2) || (roadCount == 1 && destinationCount == 2) || 
            (roadCount == 1 && houseCount == 1 && destinationCount == 1) || (houseCount == 2 && destinationCount == 1) ||
            (houseCount == 1 && destinationCount == 2) || (houseCount == 3 && roadCount == 0 && destinationCount == 0) || 
            (destinationCount == 3 && houseCount == 0 && roadCount == 0))
        {
            Create3Way(placementManager, result, temporaryPosition);
        }
        else
        {
            Create4Way(placementManager, result, temporaryPosition);
        }
    }

    private void Create4Way(PlacementManager placementManager, CellType[] result, Vector2Int temporaryPosition)
    {
        placementManager.ModifyStructureModel(temporaryPosition, fourWay, 0);
    }

    //[left, up, right, down]
    private void Create3Way(PlacementManager placementManager, CellType[] result, Vector2Int temporaryPosition)
    {
        if ((result[1] == CellType.Road && result[2] == CellType.Road && result[3] == CellType.Road) ||
            (result[1] == CellType.Structure && result[2] == CellType.Structure && result[3] == CellType.Structure) ||
            (result[1] == CellType.SpecialStructure && result[2] == CellType.SpecialStructure && result[3] == CellType.SpecialStructure) ||
            (result[1] == CellType.Road && result[2] == CellType.Road && result[3] == CellType.Structure) ||
            (result[1] == CellType.Road && result[2] == CellType.Structure && result[3] == CellType.Road) ||
            (result[1] == CellType.Structure && result[2] == CellType.Road && result[3] == CellType.Road) ||
            (result[1] == CellType.Road && result[2] == CellType.Road && result[3] == CellType.SpecialStructure) ||
            (result[1] == CellType.Road && result[2] == CellType.SpecialStructure && result[3] == CellType.Road) ||
            (result[1] == CellType.SpecialStructure && result[2] == CellType.Road && result[3] == CellType.Road) ||
            (result[1] == CellType.Road && result[2] == CellType.Structure && result[3] == CellType.Structure) ||
            (result[1] == CellType.Structure && result[2] == CellType.Road && result[3] == CellType.Structure) ||
            (result[1] == CellType.Structure && result[2] == CellType.Structure && result[3] == CellType.Road) ||
            (result[1] == CellType.Road && result[2] == CellType.SpecialStructure && result[3] == CellType.SpecialStructure) ||
            (result[1] == CellType.SpecialStructure && result[2] == CellType.SpecialStructure && result[3] == CellType.Road) ||
            (result[1] == CellType.SpecialStructure && result[2] == CellType.Road && result[3] == CellType.SpecialStructure) ||
            (result[1] == CellType.Road && result[2] == CellType.Structure && result[3] == CellType.SpecialStructure) ||
            (result[1] == CellType.Road && result[2] == CellType.SpecialStructure && result[3] == CellType.Structure) ||
            (result[1] == CellType.Structure && result[2] == CellType.Road && result[3] == CellType.SpecialStructure) ||
            (result[1] == CellType.Structure && result[2] == CellType.SpecialStructure && result[3] == CellType.Road) ||
            (result[1] == CellType.SpecialStructure && result[2] == CellType.Road && result[3] == CellType.Structure) ||
            (result[1] == CellType.SpecialStructure && result[2] == CellType.Structure && result[3] == CellType.Road))
        {
            placementManager.ModifyStructureModel(temporaryPosition, threeWay, 90);
        }
        else if ((result[2] == CellType.Road && result[3] == CellType.Road && result[0] == CellType.Road) ||
            (result[2] == CellType.Structure && result[3] == CellType.Structure && result[0] == CellType.Structure) ||
            (result[2] == CellType.SpecialStructure && result[2] == CellType.SpecialStructure && result[0] == CellType.SpecialStructure) ||
            (result[2] == CellType.Road && result[3] == CellType.Road && result[0] == CellType.Structure) ||
            (result[2] == CellType.Road && result[3] == CellType.Structure && result[0] == CellType.Road) ||
            (result[2] == CellType.Structure && result[3] == CellType.Road && result[0] == CellType.Road) ||
            (result[2] == CellType.Road && result[3] == CellType.Road && result[0] == CellType.SpecialStructure) ||
            (result[2] == CellType.Road && result[3] == CellType.SpecialStructure && result[0] == CellType.Road) ||
            (result[2] == CellType.SpecialStructure && result[3] == CellType.Road && result[0] == CellType.Road) ||
            (result[2] == CellType.Road && result[3] == CellType.Structure && result[0] == CellType.Structure) ||
            (result[2] == CellType.Structure && result[3] == CellType.Road && result[0] == CellType.Structure) ||
            (result[2] == CellType.Structure && result[3] == CellType.Structure && result[0] == CellType.Road) ||
            (result[2] == CellType.Road && result[3] == CellType.SpecialStructure && result[0] == CellType.SpecialStructure) ||
            (result[2] == CellType.SpecialStructure && result[3] == CellType.SpecialStructure && result[0] == CellType.Road) ||
            (result[2] == CellType.SpecialStructure && result[3] == CellType.SpecialStructure && result[0] == CellType.Road) ||
            (result[2] == CellType.Road && result[3] == CellType.Structure && result[0] == CellType.SpecialStructure) ||
            (result[2] == CellType.Road && result[3] == CellType.SpecialStructure && result[0] == CellType.Structure) ||
            (result[2] == CellType.Structure && result[3] == CellType.Road && result[0] == CellType.SpecialStructure) ||
            (result[2] == CellType.Structure && result[3] == CellType.SpecialStructure && result[0] == CellType.Road) ||
            (result[2] == CellType.SpecialStructure && result[3] == CellType.Road && result[0] == CellType.Structure) ||
            (result[2] == CellType.SpecialStructure && result[3] == CellType.Structure && result[0] == CellType.Road))
        {
            placementManager.ModifyStructureModel(temporaryPosition, threeWay, 0);
        }
        else if ((result[3] == CellType.Road && result[0] == CellType.Road && result[1] == CellType.Road) ||
            (result[3] == CellType.Structure && result[0] == CellType.Structure && result[1] == CellType.Structure) ||
            (result[3] == CellType.SpecialStructure && result[0] == CellType.SpecialStructure && result[1] == CellType.SpecialStructure) ||
            (result[3] == CellType.Road && result[0] == CellType.Road && result[1] == CellType.Structure) ||
            (result[3] == CellType.Road && result[0] == CellType.Structure && result[1] == CellType.Road) ||
            (result[3] == CellType.Structure && result[0] == CellType.Road && result[1] == CellType.Road) ||
            (result[3] == CellType.Road && result[0] == CellType.Road && result[1] == CellType.SpecialStructure) ||
            (result[3] == CellType.Road && result[0] == CellType.SpecialStructure && result[1] == CellType.Road) ||
            (result[3] == CellType.SpecialStructure && result[0] == CellType.Road && result[1] == CellType.Road) ||
            (result[3] == CellType.Road && result[0] == CellType.Structure && result[1] == CellType.Structure) ||
            (result[3] == CellType.Structure && result[0] == CellType.Road && result[1] == CellType.Structure) ||
            (result[3] == CellType.Structure && result[0] == CellType.Structure && result[1] == CellType.Road) ||
            (result[3] == CellType.Road && result[0] == CellType.SpecialStructure && result[1] == CellType.SpecialStructure) ||
            (result[3] == CellType.SpecialStructure && result[0] == CellType.SpecialStructure && result[1] == CellType.Road) ||
            (result[3] == CellType.SpecialStructure && result[0] == CellType.SpecialStructure && result[1] == CellType.Road) ||
            (result[3] == CellType.Road && result[0] == CellType.Structure && result[1] == CellType.SpecialStructure) ||
            (result[3] == CellType.Road && result[0] == CellType.SpecialStructure && result[1] == CellType.Structure) ||
            (result[3] == CellType.Structure && result[0] == CellType.Road && result[1] == CellType.SpecialStructure) ||
            (result[3] == CellType.Structure && result[0] == CellType.SpecialStructure && result[1] == CellType.Road) ||
            (result[3] == CellType.SpecialStructure && result[0] == CellType.Road && result[1] == CellType.Structure) ||
            (result[3] == CellType.SpecialStructure && result[0] == CellType.Structure && result[1] == CellType.Road))
        {
            placementManager.ModifyStructureModel(temporaryPosition, threeWay, 270);
        }
        else if ((result[0] == CellType.Road && result[1] == CellType.Road && result[2] == CellType.Road) ||
            (result[0] == CellType.Structure && result[1] == CellType.Structure && result[2] == CellType.Structure) ||
            (result[0] == CellType.SpecialStructure && result[1] == CellType.SpecialStructure && result[2] == CellType.SpecialStructure) ||
            (result[0] == CellType.Road && result[1] == CellType.Road && result[2] == CellType.Structure) ||
            (result[0] == CellType.Road && result[1] == CellType.Structure && result[2] == CellType.Road) ||
            (result[0] == CellType.Structure && result[1] == CellType.Road && result[2] == CellType.Road) ||
            (result[0] == CellType.Road && result[1] == CellType.Road && result[2] == CellType.SpecialStructure) ||
            (result[0] == CellType.Road && result[1] == CellType.SpecialStructure && result[2] == CellType.Road) ||
            (result[0] == CellType.SpecialStructure && result[1] == CellType.Road && result[2] == CellType.Road) ||
            (result[0] == CellType.Road && result[1] == CellType.Structure && result[2] == CellType.Structure) ||
            (result[0] == CellType.Structure && result[1] == CellType.Road && result[2] == CellType.Structure) ||
            (result[0] == CellType.Structure && result[1] == CellType.Structure && result[2] == CellType.Road) ||
            (result[0] == CellType.Road && result[1] == CellType.SpecialStructure && result[2] == CellType.SpecialStructure) ||
            (result[0] == CellType.SpecialStructure && result[1] == CellType.SpecialStructure && result[2] == CellType.Road) ||
            (result[0] == CellType.SpecialStructure && result[1] == CellType.SpecialStructure && result[2] == CellType.Road) ||
            (result[0] == CellType.Road && result[1] == CellType.Structure && result[2] == CellType.SpecialStructure) ||
            (result[0] == CellType.Road && result[1] == CellType.SpecialStructure && result[2] == CellType.Structure) ||
            (result[0] == CellType.Structure && result[1] == CellType.Road && result[2] == CellType.SpecialStructure) ||
            (result[0] == CellType.Structure && result[1] == CellType.SpecialStructure && result[2] == CellType.Road) ||
            (result[0] == CellType.SpecialStructure && result[1] == CellType.Road && result[2] == CellType.Structure) ||
            (result[0] == CellType.SpecialStructure && result[1] == CellType.Structure && result[2] == CellType.Road))
        {
            placementManager.ModifyStructureModel(temporaryPosition, threeWay, 180);
        }

    }

    //[left, up, right, down]
    private void CreateCorner(PlacementManager placementManager, CellType[] result, Vector2Int temporaryPosition)
    {
        if ((result[1] == CellType.Road && result[2] == CellType.Road) ||
            (result[1] == CellType.Road && result[2] == CellType.Structure) ||
            (result[1] == CellType.Road && result[2] == CellType.SpecialStructure) ||
            (result[1] == CellType.Structure && result[2] == CellType.SpecialStructure) ||
            (result[1] == CellType.Structure && result[2] == CellType.Road) ||
            (result[1] == CellType.SpecialStructure && result[2] == CellType.Road) ||
            (result[1] == CellType.SpecialStructure && result[2] == CellType.Structure) ||
            (result[1] == CellType.Structure && result[2] == CellType.Structure) ||
            (result[1] == CellType.SpecialStructure && result[2] == CellType.SpecialStructure))
        {
            placementManager.ModifyStructureModel(temporaryPosition, corner, 90);
        }
        else if ((result[2] == CellType.Road && result[3] == CellType.Road) ||
            (result[2] == CellType.Road && result[3] == CellType.Structure) ||
            (result[2] == CellType.Road && result[3] == CellType.SpecialStructure) ||
            (result[2] == CellType.Structure && result[3] == CellType.SpecialStructure) ||
            (result[2] == CellType.Structure && result[3] == CellType.Road) ||
            (result[2] == CellType.SpecialStructure && result[3] == CellType.Road) ||
            (result[2] == CellType.SpecialStructure && result[3] == CellType.Structure) ||
            (result[2] == CellType.Structure && result[3] == CellType.Structure) ||
            (result[2] == CellType.SpecialStructure && result[3] == CellType.SpecialStructure))
        {
            placementManager.ModifyStructureModel(temporaryPosition, corner, 0);
        }
        else if ((result[3] == CellType.Road && result[0] == CellType.Road) ||
            (result[3] == CellType.Road && result[0] == CellType.Structure) ||
            (result[3] == CellType.Road && result[0] == CellType.SpecialStructure) ||
            (result[3] == CellType.Structure && result[0] == CellType.SpecialStructure) ||
            (result[3] == CellType.Structure && result[0] == CellType.Road) ||
            (result[3] == CellType.SpecialStructure && result[0] == CellType.Road) ||
            (result[3] == CellType.SpecialStructure && result[0] == CellType.Structure) ||
            (result[3] == CellType.Structure && result[0] == CellType.Structure) ||
            (result[3] == CellType.SpecialStructure && result[0] == CellType.SpecialStructure))
        {
            placementManager.ModifyStructureModel(temporaryPosition, corner, 270);
        }
        else if ((result[0] == CellType.Road && result[1] == CellType.Road) ||
            (result[0] == CellType.Road && result[1] == CellType.Structure) ||
            (result[0] == CellType.Road && result[1] == CellType.SpecialStructure) ||
            (result[0] == CellType.Structure && result[1] == CellType.SpecialStructure) ||
            (result[0] == CellType.Structure && result[1] == CellType.Road) ||
            (result[0] == CellType.SpecialStructure && result[1] == CellType.Road) ||
            (result[0] == CellType.SpecialStructure && result[1] == CellType.Structure) ||
            (result[0] == CellType.Structure && result[1] == CellType.Structure) ||
            (result[0] == CellType.SpecialStructure && result[1] == CellType.SpecialStructure))
        {
            placementManager.ModifyStructureModel(temporaryPosition, corner, 180);
        }
    }

    //[left, up, right, down]
    private bool CreateStraightRoad(PlacementManager placementManager, CellType[] result, Vector2Int temporaryPosition)
    {
        if ((result[0] == CellType.Road && result[2] == CellType.Road) ||
            (result[0] == CellType.Structure && result[2] == CellType.Structure) ||
            (result[0] == CellType.SpecialStructure && result[2] == CellType.SpecialStructure) ||
            (result[0] == CellType.Road && result[2] == CellType.Structure) ||
            (result[0] == CellType.Structure && result[2] == CellType.Road) ||
            (result[0] == CellType.Road && result[2] == CellType.SpecialStructure) ||
            (result[0] == CellType.SpecialStructure && result[2] == CellType.Road) ||
            (result[0] == CellType.Structure && result[2] == CellType.SpecialStructure) ||
            (result[0] == CellType.SpecialStructure && result[2] == CellType.Structure))
        {
            placementManager.ModifyStructureModel(temporaryPosition, roadStraight, 90);
            Debug.Log("straight");
            return true;
        }
        else if ((result[1] == CellType.Road && result[3] == CellType.Road) ||
            (result[1] == CellType.Structure && result[3] == CellType.Structure) ||
            (result[1] == CellType.SpecialStructure && result[3] == CellType.SpecialStructure) ||
            (result[1] == CellType.Road && result[3] == CellType.Structure) ||
            (result[1] == CellType.Structure && result[3] == CellType.Road) ||
            (result[1] == CellType.Road && result[3] == CellType.SpecialStructure) ||
            (result[1] == CellType.SpecialStructure && result[3] == CellType.Road) ||
            (result[1] == CellType.Structure && result[3] == CellType.SpecialStructure) ||
            (result[1] == CellType.SpecialStructure && result[3] == CellType.Structure))
        {
            placementManager.ModifyStructureModel(temporaryPosition, roadStraight, 0);
            return true;
        }
        return false;
    }

    //[left, up, right, down]
    private void CreateDeadEnd(PlacementManager placementManager, CellType[] result, Vector2Int temporaryPosition)
    {
        if ((result[1] == CellType.Road) || (result[1] == CellType.Structure) || (result[1] == CellType.SpecialStructure))
        {
            placementManager.ModifyStructureModel(temporaryPosition, deadEnd, 180);
        }
        else if ((result[2] == CellType.Road) || (result[2] == CellType.Structure) || (result[2] == CellType.SpecialStructure))
        {
            placementManager.ModifyStructureModel(temporaryPosition, deadEnd, 90);
        }
        else if ((result[3] == CellType.Road) || (result[3] == CellType.Structure) || (result[3] == CellType.SpecialStructure))
        {
            placementManager.ModifyStructureModel(temporaryPosition, deadEnd, 0);
        }
        else if ((result[0] == CellType.Road) || (result[0] == CellType.Structure) || (result[0] == CellType.SpecialStructure))
        {
            placementManager.ModifyStructureModel(temporaryPosition, deadEnd, 270);
        }
    }
}