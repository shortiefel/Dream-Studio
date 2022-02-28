﻿using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

public enum BuildingType
{
    Hospital = 0,
    Office,
    Park,
    Mall,
    House
}

public struct StartPositionSet
{
    public Vector2Int startPos;
    public int pathCount;

    public StartPositionSet(Vector2Int newPos, int pc)
    {
        startPos = newPos;
        pathCount = pc;
    }
}


public class StructureManager : MonoBehaviour
{
    public StructurePrefabWeighted[] housesPrefabs, specialPrefabs;
    public PlacementManager placementManager;
    //public NotificationManager notificationManager;


    private float[] houseWeights, specialWeights;

    public Dictionary<Vector2Int, CarSpawner> houseList;
    public Dictionary<Vector2Int, StartPositionSet> destinationList;
   
    //private void Start()
    public override void Start()
    {
        /*houseWeights = housesPrefabs.Select(prefabStats => prefabStats.weight).ToArray();
        specialWeights = specialPrefabs.Select(prefabStats => prefabStats.weight).ToArray();
        placementManager = GetComponent<Pl_roadListacementManager>();*/

        placementManager = GameObject.Find("PlacementManager").GetComponent<PlacementManager>();

        housesPrefabs = new StructurePrefabWeighted[2];
        housesPrefabs[0].prefab = new GameObject(new Prefab("House")); housesPrefabs[0].weight = 1;

        specialPrefabs = new StructurePrefabWeighted[5];
        //specialPrefabs[0].prefab = new GameObject(new Prefab("Destination")); specialPrefabs[0].weight = 1;

        specialPrefabs[(int)BuildingType.Hospital].prefab = new GameObject(new Prefab("HospitalDestination")); specialPrefabs[(int)BuildingType.Hospital].weight = 1;
        specialPrefabs[(int)BuildingType.Office].prefab = new GameObject(new Prefab("OfficeDestination")); specialPrefabs[(int)BuildingType.Office].weight = 1;
        //specialPrefabs[(int)BuildingType.Park].prefab = new GameObject(new Prefab("ParkDestination")); specialPrefabs[(int)BuildingType.Park].weight = 1;
        //specialPrefabs[(int)BuildingType.Mall].prefab = new GameObject(new Prefab("MallDestination")); specialPrefabs[(int)BuildingType.Mall].weight = 1;

        houseWeights = new float[] { housesPrefabs[0].weight };
        specialWeights = new float[] { specialPrefabs[(int)BuildingType.Hospital].weight, specialPrefabs[(int)BuildingType.Office].weight };

        houseList = new Dictionary<Vector2Int, CarSpawner>();
        destinationList = new Dictionary<Vector2Int, StartPositionSet>();
    }

    //private IEnumerator waitABit(Vector2Int newPos)
    //{
    //    Debug.Log("got wait until");
    //    yield return new WaitForSeconds(notificationManager.GetRandomNumber()); //tell unity to wait!!
    //    notificationManager.CreateNotificationModel(newPos);

    //}
    public void PlaceHouse(Vector2Int position, float rotation)
    {
        //Debug.Log("here house " + position);
        if (CheckPositionBeforePlacement(position))
        {
        //Debug.Log("place house " + position);
            int randomIndex = GetRandomWeightedIndex(houseWeights);
            GameObject go = placementManager.PlaceObjectOnTheMap(position, housesPrefabs[randomIndex].prefab, CellType.Structure, rotation);
            houseList.Add(position, go.GetComponent<CarSpawner>());
            //AudioPlayer.instance.PlayPlacementSound();
            //StartCoroutine(waitABit(position));
        }
    }

    public void PlaceSpecial(Vector2Int position, float rotation)
    {
        //Debug.Log("here special " + position);
        if (CheckPositionBeforePlacement(position))
        {
            int randomIndex = GetRandomWeightedIndex(specialWeights);
            placementManager.PlaceObjectOnTheMap(position, specialPrefabs[randomIndex].prefab, CellType.SpecialStructure, rotation);
            destinationList.Add(position, new StartPositionSet(new Vector2Int(0,0), 0));
            //AudioPlayer.instance.PlayPlacementSound();
        }
    }

    private int GetRandomWeightedIndex(float[] weights)
    {
        float sum = 0f;
        for (int i = 0; i < weights.Length; i++)
        {
            sum += weights[i];
        }

        float randomValue = Random.Range(0, (int)sum);
        float tempSum = 0;
        for (int i = 0; i < weights.Length; i++)
        {
            //0->weight[0] weight[0]->weight[1]
            if (randomValue >= tempSum && randomValue < tempSum + weights[i])
            {
                return i;
            }
            tempSum += weights[i];
        }
        return 0;
    }

    // change to public cause jiayi needs to use in notification manager
    public bool CheckPositionBeforePlacement(Vector2Int position)
    {
        if (placementManager.CheckIfPositionInBound(position) == false)
        {
            Debug.Log("This position is out of bounds");
            return false;
        }
        if (placementManager.CheckIfPositionIsFree(position) == false)
        {
            Debug.Log("This position is not EMPTY");
            return false;
        }
        if (placementManager.placementGrid.IsSurrounded(position) == true)
        {
            Debug.Log("This surrounding already has buildings");
            return false;
        }


        //if (placementManager.GetNeighboursOfTypeFor(position, CellType.Road).Count <= 0)
        //{
        //    //Add road
        //    Console.WriteLine("Try add road in StructureManager");
        //    return placementManager.TryAddRoad(position);
        //    //Debug.Log("Must be placed near a road");
        //    //return false;
        //}
        return true;
    }
}

[Serializable]
public struct StructurePrefabWeighted
{
    public GameObject prefab;
    //[Range(0, 1)]
    public float weight;
}