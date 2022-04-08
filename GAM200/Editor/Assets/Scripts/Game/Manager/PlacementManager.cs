using System;
using System.Collections;
using System.Collections.Generic;

public class PlacementManager : MonoBehaviour
{
    //public int width, height;
    public Grid placementGrid;
    public int width;
    public int height;

    //RoadFixer roadFixer;
    //private Transform transform;

    private Dictionary<Vector2Int, StructureModel> temporaryRoadobjects;
    private Dictionary<Vector2Int, StructureModel> structureDictionary;

    //private void Start()
    public override void Start()
    {
        width = 12; height = 7;
        placementGrid = new Grid(width, height);
        //placementGrid = new Grid(10, 5);
        transform = GetComponent<Transform>();
        //roadFixer = GameObject.Find("RoadManager").GetComponent<RoadFixer>();
       
        temporaryRoadobjects = new Dictionary<Vector2Int, StructureModel>();
        structureDictionary = new Dictionary<Vector2Int, StructureModel>();
    }

    public bool IsBuilding(Vector2Int targetPos, uint entId)
    {
        if (!structureDictionary.ContainsKey(targetPos)) return false;
        return structureDictionary[targetPos].entityId == entId;
    }

    //True = within
    internal bool CheckIfPositionInBound(Vector2Int position)
    {
        Vector2Int startPoint = placementGrid.GetStartPoint();
        Vector2Int endPoint = placementGrid.GetGridSize() + startPoint;
        if (position.x >= startPoint.x && position.x < endPoint.x && position.y >= startPoint.y && position.y < endPoint.y)
        {
            return true;
        }
        return false;
    }


    internal GameObject PlaceObjectOnTheMap(Vector2Int position, GameObject structurePrefab, CellType type, float rotation, int width = 1, int height = 1)
    {
        //Debug.Log("Placement in placementManager " + structurePrefab.name);
        //StructureModel structure = CreateANewStructureModel(position, structurePrefab, type, 3, rotation);
        Vector2 pos = new Vector2(position.x, position.y);
        if (type == CellType.SpecialStructure) pos += new Vector2(0.5f, 0.5f);
        GameObject structure = Instantiate(structurePrefab, new Vector3(pos.x, pos.y, 0f), 3);


        placementGrid[position.x, position.y] = type;
        placementGrid.SetCellType(position, type, structure.entityId);

        if (type == CellType.SpecialStructure)
        {
            StructureModel sm = structure.GetComponent<StructureModel>();
            structureDictionary.Add(position, sm);
            structureDictionary.Add(new Vector2Int(position.x + 1, position.y    ), sm); //Right
            structureDictionary.Add(new Vector2Int(position.x    , position.y + 1), sm); //Up
            structureDictionary.Add(new Vector2Int(position.x + 1, position.y + 1), sm); //Up Right
        }
        else
        {
            structureDictionary.Add(position, structure.GetComponent<StructureModel>());
        }

        return structure;
    }

    public void RemoveDestination(Vector2Int position)
    {
        Vector2Int posToRemove;
        bool result = placementGrid.UnsetDestination(position, out posToRemove);
        if (result)
        {
            structureDictionary.Remove(posToRemove);
            structureDictionary.Remove(new Vector2Int(posToRemove.x + 1, posToRemove.y));
            structureDictionary.Remove(new Vector2Int(posToRemove.x, posToRemove.y + 1));
            structureDictionary.Remove(new Vector2Int(posToRemove.x + 1, posToRemove.y + 1));

            //AddMoney
        }


        //return result;
    }

    internal bool CheckIfPositionIsFree(Vector2Int position)
    {
        return placementGrid.IsPosFree(position);
    }

    internal bool CheckIfPositionIsRoad(Vector2Int position)
    {
        return placementGrid.IsPosRoad(position);
    }


    internal List<Vector2Int> GetNeighboursOfTypeFor(Vector2Int position, CellType type)
    {
        var neighbourVertices = placementGrid.GetAdjacentCellsOfType(position.x, position.y, type);
        List<Vector2Int> neighbours = new List<Vector2Int>();
        foreach (var point in neighbourVertices)
        {
            neighbours.Add(new Vector2Int(point));
        }
        return neighbours;
    }

   
    internal List<Vector2> GetPathBetween(out Vector2Int housePos, Vector2Int destPos, RouteType rt, ref List<Vector2Int> leftList)
    {
        //Console.WriteLine("START OF ALL A STAR");
        //var resultPath = GridSearch.AStarSearch(placementGrid, housePos, destPos, out roadCount);
        List<Vector2> path = GridSearch.AStarSearch(placementGrid, out housePos, destPos, (int)rt, ref leftList);
        //List<Vector2> path = new List<Vector2>();
        //foreach (Point point in resultPath)
        //{
        //    path.Add(new Vector2(point));
        //}
        //Console.WriteLine("Path line count " + path.Count);
        return path;
    }


    //private StructureModel GetStructureAt(Point point)
    //{
    //    if (point != null)
    //    {
    //        return structureDictionary[new Vector2Int(point)];
    //    }
    //    return null;
    //}
    
}