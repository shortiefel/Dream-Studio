﻿using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

public class RoadFixer : MonoBehaviour
{
    public static Prefab deadEnd, roadStraight, corner, threeWay, fourWay;
    RoadFixer roadFixer;

    public override void Start()
    {
        roadFixer = GetComponent<RoadFixer>();
        RoadFixer.deadEnd = new Prefab("EndRoad");
        RoadFixer.roadStraight = new Prefab("StraightRoad");
        RoadFixer.corner = new Prefab("CurveRoad");
        RoadFixer.threeWay = new Prefab("ThreeWayRoad");
        RoadFixer.fourWay = new Prefab("FourWayRoad");
    }
    public static void FixRoadAtPosition(PlacementManager placementManager, Vector2Int temporaryPosition)
    {
        //[right, up, left, down]
        var result = placementManager.GetNeighbourTypesFor(temporaryPosition);
        int roadCount = 0;
        roadCount = result.Where(x => x == CellType.Road).Count();
        if (roadCount == 0 || roadCount == 1)
        {
            CreateDeadEnd(placementManager, result, temporaryPosition);
        }
        else if (roadCount == 2)
        {
            if (CreateStraightRoad(placementManager, result, temporaryPosition))
                return;
            CreateCorner(placementManager, result, temporaryPosition);
        }
        else if (roadCount == 3)
        {
            Create3Way(placementManager, result, temporaryPosition);
        }
        else
        {
            Create4Way(placementManager, result, temporaryPosition);
        }
    }

    private static void Create4Way(PlacementManager placementManager, CellType[] result, Vector2Int temporaryPosition)
    {
        placementManager.ModifyStructureModel(temporaryPosition, fourWay, 0);
    }

    //[left, up, right, down]
    private static void Create3Way(PlacementManager placementManager, CellType[] result, Vector2Int temporaryPosition)
    {
        if (result[1] == CellType.Road && result[2] == CellType.Road && result[3] == CellType.Road)
        {
            placementManager.ModifyStructureModel(temporaryPosition, threeWay, 90);
        }
        else if (result[2] == CellType.Road && result[3] == CellType.Road && result[0] == CellType.Road)
        {
            placementManager.ModifyStructureModel(temporaryPosition, threeWay, 0);
        }
        else if (result[3] == CellType.Road && result[0] == CellType.Road && result[1] == CellType.Road)
        {
            placementManager.ModifyStructureModel(temporaryPosition, threeWay, 270);
        }
        else if (result[0] == CellType.Road && result[1] == CellType.Road && result[2] == CellType.Road)
        {
            placementManager.ModifyStructureModel(temporaryPosition, threeWay, 180);
        }

    }

    //[left, up, right, down]
    private static void CreateCorner(PlacementManager placementManager, CellType[] result, Vector2Int temporaryPosition)
    {
        if (result[1] == CellType.Road && result[2] == CellType.Road)
        {
            placementManager.ModifyStructureModel(temporaryPosition, corner, 90);
        }
        else if (result[2] == CellType.Road && result[3] == CellType.Road)
        {
            placementManager.ModifyStructureModel(temporaryPosition, corner, 0);
        }
        else if (result[3] == CellType.Road && result[0] == CellType.Road)
        {
            placementManager.ModifyStructureModel(temporaryPosition, corner, 270);
        }
        else if (result[0] == CellType.Road && result[1] == CellType.Road)
        {
            placementManager.ModifyStructureModel(temporaryPosition, corner, 180);
        }
    }

    //[left, up, right, down]
    private static bool CreateStraightRoad(PlacementManager placementManager, CellType[] result, Vector2Int temporaryPosition)
    {
        if (result[0] == CellType.Road && result[2] == CellType.Road)
        {
            placementManager.ModifyStructureModel(temporaryPosition, roadStraight, 90);
            return true;
        }
        else if (result[1] == CellType.Road && result[3] == CellType.Road)
        {
            placementManager.ModifyStructureModel(temporaryPosition, roadStraight, 0);
            return true;
        }
        return false;
    }

    //[left, up, right, down]
    private static void CreateDeadEnd(PlacementManager placementManager, CellType[] result, Vector2Int temporaryPosition)
    {
        if (result[1] == CellType.Road)
        {
            placementManager.ModifyStructureModel(temporaryPosition, deadEnd, 180);
        }
        else if (result[2] == CellType.Road)
        {
            placementManager.ModifyStructureModel(temporaryPosition, deadEnd, 90);
        }
        else if (result[3] == CellType.Road)
        {
            placementManager.ModifyStructureModel(temporaryPosition, deadEnd, 0);
        }
        else if (result[0] == CellType.Road)
        {
            placementManager.ModifyStructureModel(temporaryPosition, deadEnd, 270);
        }
    }
}
