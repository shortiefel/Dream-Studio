using System;
using System.Collections;
using System.Collections.Generic;

public class AIDirector : MonoBehaviour
{
    public PlacementManager placementManager;

    public Prefab[] carPrefabs;

    AdjacencyGraph carGraph = new AdjacencyGraph();

    List<Vector3> carPath = new List<Vector3>();

    public float carSpawnTimerInterval;

    public override void Start()
    {
        carSpawnTimerInterval = 2f;
        carPrefabs = new Prefab[5];
        carPrefabs[(int)BuildingType.Hospital] = new Prefab("HospitalCar");
        carPrefabs[(int)BuildingType.Office] = new Prefab("OfficeCar");
        carPrefabs[(int)BuildingType.Park] = new Prefab("ParkCar");
        carPrefabs[(int)BuildingType.Mall] = new Prefab("MallCar");

        placementManager = GameObject.Find("PlacementManager").GetComponent<PlacementManager>();
    }
    //public void SpawnACar()
    //{
    //    foreach (var house in placementManager.GetAllHouses())
    //    {
    //        TrySpawninACar(house, placementManager.GetRandomSpecialStrucutre());
    //    }
    //}

    public bool SpawnToDestination(StructureModel endHouse)
    {

        if (endHouse != null)
            return TrySpawninACar(placementManager.GetRandomHouseStructure(), endHouse);
        return false;
    }

    //public bool SpawnAHouseCar(StructureModel house)
    //{
    //    /*foreach (var house in placementManager.GetAllHouses())
    //    {*/
    //    if (house != null)
    //        return TrySpawninACar(house, placementManager.GetRandomSpecialStrucutre());
    //    return false;
    //    //}
    //}

    private bool TrySpawninACar(StructureModel startStructure, StructureModel endStructure)
    {
        //Console.WriteLine("here but go in ?");
        if (startStructure == null || endStructure == null) return false;

        //Console.WriteLine(" actually inside ");
        //if(startStructure == null) Console.WriteLine("is null");
        //if(startStructure != null) Console.WriteLine("is not null");
        var startRoadPosition = Vector2Int.RoundToInt(((INeedingRoad)startStructure).RoadPosition);
        //Console.WriteLine("after start");
        var endRoadPosition = Vector2Int.RoundToInt(((INeedingRoad)endStructure).RoadPosition);

        //Debug.Log(startRoadPosition);
        //Debug.Log(endRoadPosition);

        var path = placementManager.GetPathBetween(startRoadPosition, endRoadPosition, new Vector2Int(startStructure.transform.position), new Vector2Int(endStructure.transform.position), true);
        if (path.Count == 0)
        {
            //Console.WriteLine("No path exist");
            return false;
        }

        //return;
        //if (path == null) return;
        //Console.WriteLine("Set path: " + path.Count);
        //foreach (var item in path)
        //{
        //    Debug.Log(item.ToString());
        //}

        //path.Reverse();
        //path.Add(Vector2Int.RoundToInt(endStructure.transform.position)); //Make car enter house
        //foreach (var item2 in path)
        //{
        //    Debug.Log(item2.ToString());
        //}

        //var car = Instantiate(SelectACarPrefab(), new Vector3(startRoadPosition.x, startRoadPosition.y, 0));
        Vector2 pos = startStructure.transform.position;
        var car = Instantiate(SelectACarPrefab(endStructure.buildingType), new Vector3(pos.x, pos.y, 0), 2);
        //var car = Instantiate(carPrefab, new Vector3(startRoadPosition.x, startRoadPosition.y, 0), Quaternion.identity);

        Console.WriteLine("Set path2: " + path.Count);
        //car.GetComponent<CarAI>().SetPath(path.ConvertAll(x => (Vector2)x));
        car.GetComponent<CarAI>().SetPath(path, ref endStructure);
        return true;
    }

    private Prefab SelectACarPrefab(BuildingType bt)
    {
        //var randomIndex = Random.Range(0, carPrefabs.Length - 1);
        return carPrefabs[(int)bt];
    }
}