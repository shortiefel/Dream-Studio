using System;
using System.Collections;
using System.Collections.Generic;

public class PlacementManager : MonoBehaviour
{
    //public int width, height;
    public Grid placementGrid;
    RoadFixer roadFixer;
    //private Transform transform;

    private Dictionary<Vector2Int, StructureModel> temporaryRoadobjects;
    private Dictionary<Vector2Int, StructureModel> structureDictionary;

    //private void Start()
    public override void Start()
    {
        //width = 20; height = 10;
        placementGrid = new Grid(20, 10);
        transform = GetComponent<Transform>();
        roadFixer = GameObject.Find("RoadManager").GetComponent<RoadFixer>();
       
        temporaryRoadobjects = new Dictionary<Vector2Int, StructureModel>();
        structureDictionary = new Dictionary<Vector2Int, StructureModel>();
    }

    internal CellType[] GetNeighbourTypesFor(Vector2Int position)
    {
        return placementGrid.GetAllAdjacentCellTypes(position.x, position.y);
    }

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

    //internal void PlaceObjectOnTheMap(Vector2Int position, Prefab structurePrefab, CellType type)
    //{
    //    placementGrid[position.x, position.y] = type;
    //    StructureModel structure = CreateANewStructureModel(position, structurePrefab, type);
    //    structureDictionary.Add(position, structure);
    //    //DestroyNatureAt(position);
    //}

    internal void PlaceObjectOnTheMap(Vector2Int position, GameObject structurePrefab, CellType type, float rotation, int width = 1, int height = 1)
    {
        StructureModel structure = CreateANewStructureModel(position, structurePrefab, type, 3, rotation);
        //var structureNeedingRoad = structure.GetComponent<INeedingRoad>();
        //if (structureNeedingRoad != null)
        //{
        structure.RoadPosition = GetNearestRoad(position, width, height).Value;
        //Debug.Log("My nearest road position is: " + structure.RoadPosition);
        //}

        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                var newPosition = position + new Vector2Int(x, y);
                placementGrid[newPosition.x, newPosition.y] = type;
                structureDictionary.Add(newPosition, structure);
                //DestroyNatureAt(newPosition);
            }
        }
    }

    private Vector2Int? GetNearestRoad(Vector2Int position, int width, int height)
    {
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                var newPosition = position + new Vector2Int(x, y);
                var roads = GetNeighboursOfTypeFor(newPosition, CellType.Road);
                if (roads.Count > 0)
                {
                    return roads[0];
                }
            }
        }
        return null;
    }

    //private void DestroyNatureAt(Vector2Int position)
    //{
    //    //RaycastHit2D[] hits = Physics2D.BoxCastAll(position + new Vector2(0, 0.5f), new Vector2(0.5f, 0.5f),
    //    //                                          transform.up, Quaternion.identity, 1f, 1 << LayerMask.NameToLayer("Nature"));

    //    RaycastHit2D hits = Physics2D.RayCast(new Vector3(position.x, position.y, 0), Vector2.zero);

    //    //foreach (var item in hits)
    //    //{
    //    //    Destroy(item.collider.gameObject);
    //    //}
    //}

    internal bool CheckIfPositionIsFree(Vector2Int position)
    {
        return CheckIfPositionIsOfType(position, CellType.Empty);
    }

    internal bool CheckIfPositionIsOfType(Vector2Int position, CellType type)
    {
        return placementGrid[position.x, position.y] == type;
    }

    internal bool TryAddRoad(Vector2Int position)
    {
        List<Vector2Int> listOfEmpty = GetNeighboursOfTypeFor(position, CellType.Empty);
        int cnt = listOfEmpty.Count;
        if (cnt <= 0) return false;
        int index = Random.Range(0, cnt - 1);
        Console.WriteLine("Index: " + index + " sz " + cnt + " in placementManager");
        Vector2Int roadPos = listOfEmpty[index];

        PlaceTemporaryStructure(roadPos, roadFixer.deadEnd, CellType.Road, 1, true);

        return true;
    }

    internal void PlaceTemporaryStructure(Vector2Int position, GameObject structurePrefab, CellType type, int layer, bool single = false, float rotation = 0)
    {
        placementGrid[position.x, position.y] = type;
        StructureModel structure = CreateANewStructureModel(position, structurePrefab, type, layer, rotation);
        
        //GameObject newStructure = Instantiate(roadStraight, new Vector3 (position.x, position.y, 0), Quaternion.identity);
        //Debug.Log("Placed road");
        if (!single)
            temporaryRoadobjects.Add(position, structure);
    }

    internal List<Vector2Int> GetNeighboursOfTypeFor(Vector2Int position, CellType type)
    {
        var neighbourVertices = placementGrid.GetAdjacentCellsOfType(position.x, position.y, type);
        List<Vector2Int> neighbours = new List<Vector2Int>();
        foreach (var point in neighbourVertices)
        {
            neighbours.Add(new Vector2Int(point.X, point.Y));
        }
        return neighbours;
    }

    private StructureModel CreateANewStructureModel(Vector2Int position, GameObject structurePrefab, CellType type, int layer = 2, float rotation = 0)
    {
        //GameObject structure = new GameObject(type.ToString());
        
        //GameObject structure = Instantiate(structurePrefab, transform);
        GameObject structure = Instantiate(structurePrefab, new Vector3(position.x, position.y, 0f), layer);
        structure.transform.SetParent(transform);
        structure.transform.angle = rotation;
        //structure.transform.localPosition = new Vector2(position.x, position.y);
 
        //var structureModel = structure.AddComponent<StructureModel>();
        var structureModel = structure.GetComponent<StructureModel>();
        //structureModel.CreateModel(structurePrefab);
        
        return structureModel;
    }

    internal List<Vector2Int> GetPathBetween(Vector2Int startPosition, Vector2Int endPosition, bool isAgent = false)
    {
        var resultPath = GridSearch.AStarSearch(placementGrid, new Point(startPosition.x, startPosition.y), new Point(endPosition.x, endPosition.y), isAgent);
        Console.WriteLine("After a star");
        
        List<Vector2Int> path = new List<Vector2Int>();
        foreach (Point point in resultPath)
        {
            path.Add(new Vector2Int(point.X, point.Y));
        }
        Console.WriteLine("Path line count " + path.Count);
        return path;
    }

    internal void RemoveAllTemporaryStructures()
    {
        foreach (var structure in temporaryRoadobjects.Values)
        {
            var position = Vector2Int.RoundToInt(structure.transform.position);
            placementGrid[position.x, position.y] = CellType.Empty;
            Destroy(structure.gameObject);
        }
        temporaryRoadobjects.Clear();
    }

    internal void AddtemporaryStructuresToStructureDictionary()
    {
        foreach (var structure in temporaryRoadobjects)
        {
            structureDictionary.Add(structure.Key, structure.Value);
            //DestroyNatureAt(structure.Key);
            //Debug.Log(structureDictionary);
        }
        temporaryRoadobjects.Clear();
    }

    public void ModifyStructureModel(Vector2Int position, GameObject newModel, float rotation)
    {
        if (temporaryRoadobjects.ContainsKey(position))
            temporaryRoadobjects[position].SwapModel(newModel, rotation);
        else if (structureDictionary.ContainsKey(position))
            structureDictionary[position].SwapModel(newModel, rotation);
    }

    public StructureModel GetRandomRoad()
    {
        var point = placementGrid.GetRandomRoadPoint();
        return GetStructureAt(point);
    }

    public StructureModel GetRandomSpecialStrucutre()
    {
        var point = placementGrid.GetRandomSpecialStructurePoint();
        if (point == null) return null;
        //Debug.Log("Here acutal " + point);
        return GetStructureAt(point);
    }

    public StructureModel GetRandomHouseStructure()
    {
        var point = placementGrid.GetRandomHouseStructurePoint();
        //Debug.Log(point);
        return GetStructureAt(point);
    }

    public List<StructureModel> GetAllHouses()
    {
        List<StructureModel> returnList = new List<StructureModel>();
        var housePositions = placementGrid.GetAllHouses();
        foreach (var point in housePositions)
        {
            returnList.Add(structureDictionary[new Vector2Int(point.X, point.Y)]);
        }
        return returnList;
    }

    internal List<StructureModel> GetAllSpecialStructures()
    {
        List<StructureModel> returnList = new List<StructureModel>();
        var housePositions = placementGrid.GetAllSpecialStructure();
        foreach (var point in housePositions)
        {
            returnList.Add(structureDictionary[new Vector2Int(point.X, point.Y)]);
        }
        return returnList;
    }


    private StructureModel GetStructureAt(Point point)
    {
        if (point != null)
        {
            return structureDictionary[new Vector2Int(point.X, point.Y)];
        }
        return null;
    }

    public StructureModel GetStructureAt(Vector2Int position)
    {
        if (structureDictionary.ContainsKey(position))
        {
            return structureDictionary[position];
        }
        return null;
    }

    internal void RemoveCurrentGrid(Vector2Int position)
    {
        if (structureDictionary.ContainsKey(position))
        {
            structureDictionary[position].DeleteModel();
            structureDictionary.Remove(position);
            placementGrid[position.x, position.y] = CellType.Empty;
        }
    }

    public override void Update()
    {
        if (Input.GetKeyDown(KeyCode.M))
        {
            placementGrid.PrintGridOut();
        }
    }
}