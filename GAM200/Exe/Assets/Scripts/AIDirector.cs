﻿using System;
using System.Collections;
using System.Collections.Generic;

public class AIDirector : MonoBehaviour
{
    public PlacementManager placementManager;
    public GameObject[] pedestrianPrefabs;

    public Prefab carPrefab;

    public override void Start()
    {
        carPrefab = new Prefab("Car"); //Need to be same name as Texture
        Instantiate(carPrefab);
        placementManager = GameObject.Find("PlacementManager").GetComponent<PlacementManager>();
    }
    public void SpawnACar()
    {
        foreach (var house in placementManager.GetAllHouses())
        {
            TrySpawninACar(house, placementManager.GetRandomSpecialStrucutre());
        }
    }

    private void TrySpawninACar(StructureModel startStructure, StructureModel endStructure)
    {
        if (startStructure != null && endStructure != null)
        {
            var startRoadPosition = ((INeedingRoad)startStructure).RoadPosition;
            var endRoadPosition = ((INeedingRoad)endStructure).RoadPosition;

            Debug.Log(startRoadPosition);
            Debug.Log(endRoadPosition);

            var path = placementManager.GetPathBetween(startRoadPosition, endRoadPosition, true);
            //foreach (var item in path)
            //{
            //    Debug.Log(item.ToString());
            //}

            path.Reverse();

            //foreach (var item2 in path)
            //{
            //    Debug.Log(item2.ToString());
            //}

            var car = Instantiate(carPrefab, new Vector3(startRoadPosition.x, startRoadPosition.y, 0));
            //var car = Instantiate(carPrefab, new Vector3(startRoadPosition.x, startRoadPosition.y, 0), Quaternion.identity);

            car.GetComponent<CarAI>().SetPath(path.ConvertAll(x => (Vector2)x));
        }
    }
}