using System;
using System.Collections;
using System.Collections.Generic;

public class AIDirector : MonoBehaviour
{
    public PlacementManager placementManager;
    public GameObject[] pedestrianPrefabs;

    public Prefab[] carPrefabs;

    public float carSpawnTimerInterval;

    public override void Start()
    {
        carSpawnTimerInterval = 2f;
        carPrefabs = new Prefab[1];
        carPrefabs[0] = new Prefab("Car");

        placementManager = GameObject.Find("PlacementManager").GetComponent<PlacementManager>();
    }
    public void SpawnACar()
    {
        foreach (var house in placementManager.GetAllHouses())
        {
            TrySpawninACar(house, placementManager.GetRandomSpecialStrucutre());
        }
    }

    public void SpawnAHouseCar(StructureModel house)
    {
        /*foreach (var house in placementManager.GetAllHouses())
        {*/
        if (house != null)
            TrySpawninACar(house, placementManager.GetRandomSpecialStrucutre());
        //}
    }

    private void TrySpawninACar(StructureModel startStructure, StructureModel endStructure)
    {
        Console.WriteLine("here but go in ?");
        if (startStructure != null && endStructure != null)
        {
        Console.WriteLine(" actually inside ");
            if(startStructure == null) Console.WriteLine("is null");
            if(startStructure != null) Console.WriteLine("is not null");
            var startRoadPosition = ((INeedingRoad)startStructure).RoadPosition;
            Console.WriteLine("after start");
            var endRoadPosition = ((INeedingRoad)endStructure).RoadPosition;

            Debug.Log(startRoadPosition);
            Debug.Log(endRoadPosition);

            var path = placementManager.GetPathBetween(startRoadPosition, endRoadPosition, true);
            if (path.Count == 0)
            {
                Console.WriteLine("No path exist");
                return;
            }
            //return;
            //if (path == null) return;
            Console.WriteLine("Set path: " + path.Count);
            //foreach (var item in path)
            //{
            //    Debug.Log(item.ToString());
            //}

            path.Reverse();

            //foreach (var item2 in path)
            //{
            //    Debug.Log(item2.ToString());
            //}

            //var car = Instantiate(SelectACarPrefab(), new Vector3(startRoadPosition.x, startRoadPosition.y, 0));
            Vector2 pos = startStructure.transform.position;
            var car = Instantiate(SelectACarPrefab(), new Vector3(pos.x, pos.y, 0));
            //var car = Instantiate(carPrefab, new Vector3(startRoadPosition.x, startRoadPosition.y, 0), Quaternion.identity);

            Console.WriteLine("Set path2: " + path.Count);
            //car.GetComponent<CarAI>().SetPath(path.ConvertAll(x => (Vector2)x));
            car.GetComponent<CarAI>().SetPath(path, ref endStructure);
        }
    }

    private Prefab SelectACarPrefab()
    {
        var randomIndex = Random.Range(0, carPrefabs.Length - 1);
        return carPrefabs[randomIndex];
    }
}