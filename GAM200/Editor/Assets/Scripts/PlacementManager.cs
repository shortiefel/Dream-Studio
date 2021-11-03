﻿using System;
using System.Collections;
using System.Collections.Generic;

public class PlacementManager : MonoBehaviour
{
    public int width, height;
    Grid placementGrid;
    private Transform transform;

    private Dictionary<Vector2Int, StructureModel> temporaryRoadobjects = new Dictionary<Vector2Int, StructureModel>();
    private Dictionary<Vector2Int, StructureModel> structureDictionary = new Dictionary<Vector2Int, StructureModel>();

    private void Start()
    {
        placementGrid = new Grid(width, height);
        transform = GetComponent<Transform>();
    }

    internal CellType[] GetNeighbourTypesFor(Vector2Int position)
    {
        return placementGrid.GetAllAdjacentCellTypes(position.x, position.y);
    }

    internal bool CheckIfPositionInBound(Vector2Int position)
    {
        if (position.x >= 0 && position.x < width && position.y >= 0 && position.y < height)
        {
            return true;
        }
        return false;
    }

    internal void PlaceObjectOnTheMap(Vector2Int position, GameObject structurePrefab, CellType type)
    {
        placementGrid[position.x, position.y] = type;
        StructureModel structure = CreateANewStructureModel(position, structurePrefab, type);
        structureDictionary.Add(position, structure);
        //DestroyNatureAt(position);
    }

    //private void DestroyNatureAt(Vector2Int position)
    //{
    //    //RaycastHit[] hits = Physics.BoxCastAll(position + new Vector3(0, 0.5f, 0), new Vector3(0.5f, 0.5f, 0.5f),
    //                                              transform.up, Quaternion.identity, 1f, 1 << LayerMask.NameToLayer("Nature"));
    //    RaycastHit2D[] hits = Physics2D.BoxCastAll(position + new Vector2(0, 0.5f), new Vector2(0.5f, 0.5f),
    //                                              transform.up, Quaternion.identity, 1f, 1 << LayerMask.NameToLayer("Nature"));
    //    foreach (var item in hits)
    //    {
    //        Destroy(item.collider.gameObject);
    //    }
    //}

    internal bool CheckIfPositionIsFree(Vector2Int position)
    {
        return CheckIfPositionIsOfType(position, CellType.Empty);
    }

    private bool CheckIfPositionIsOfType(Vector2Int position, CellType type)
    {
        return placementGrid[position.x, position.y] == type;
    }

    internal void PlaceTemporaryStructure(Vector2Int position, GameObject structurePrefab, CellType type)
    {
        placementGrid[position.x, position.y] = type;
        StructureModel structure = CreateANewStructureModel(position, structurePrefab, type);
        //GameObject newStructure = Instantiate(roadStraight, new Vector3 (position.x, position.y, 0), Quaternion.identity);
        //Debug.Log("Placed road");
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

    private StructureModel CreateANewStructureModel(Vector2Int position, GameObject structurePrefab, CellType type)
    {
        GameObject structure = new GameObject(type.ToString());
        structure.transform.SetParent(transform);
        structure.transform.localPosition = new Vector2(position.x, position.y);
        var structureModel = structure.AddComponent<StructureModel>();
        structureModel.CreateModel(structurePrefab);
        return structureModel;
    }

    internal List<Vector2Int> GetPathBetween(Vector2Int startPosition, Vector2Int endPosition)
    {
        var resultPath = GridSearch.AStarSearch(placementGrid, new Point(startPosition.x, startPosition.y), new Point(endPosition.x, endPosition.y));
        List<Vector2Int> path = new List<Vector2Int>();
        foreach (Point point in resultPath)
        {
            path.Add(new Vector2Int(point.X, point.Y));
        }
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
            Debug.Log(structureDictionary);
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
}
