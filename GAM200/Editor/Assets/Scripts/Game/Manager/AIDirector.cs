using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

public class AIDirector : MonoBehaviour
{
    public PlacementManager placementManager;

    public Prefab[] carPrefabs;

    AdjacencyGraph carGraph;

    List<Vector2> carPath;

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

        carGraph = new AdjacencyGraph();
        carPath = new List<Vector2>();
    }

    public void SpawnACar()
    {
        foreach (var house in placementManager.GetAllHouses())
        {
            TrySpawninACar(house, placementManager.GetRandomSpecialStrucutre());
        }
    }

    public bool SpawnToDestination(StructureModel endHouse)
    {

        if (endHouse != null)
            return TrySpawninACar(placementManager.GetRandomHouseStructure(), endHouse);
        return false;
    }

    public bool SpawnAHouseCar(StructureModel house)
    {
        /*foreach (var house in placementManager.GetAllHouses())
        {*/
        if (house != null)
            return TrySpawninACar(house, placementManager.GetRandomSpecialStrucutre());
        return false;
        //}
    }

    private bool TrySpawninACar(StructureModel startStructure, StructureModel endStructure)
    {
        //Console.WriteLine("here but go in ?");
        if (startStructure != null && endStructure != null)
        {
        //Console.WriteLine(" actually inside ");
            //if(startStructure == null) Console.WriteLine("is null");
            //if(startStructure != null) Console.WriteLine("is not null");
            var startRoadPosition = Vector2Int.RoundToInt(((INeedingRoad)startStructure).RoadPosition);
            //Console.WriteLine("after start");
            var endRoadPosition = Vector2Int.RoundToInt(((INeedingRoad)endStructure).RoadPosition);

            Debug.Log(startRoadPosition);
            Debug.Log(endRoadPosition);

            var path = placementManager.GetPathBetween(startRoadPosition, endRoadPosition, true);

            //Debug.Log("path count = " + path.Count);

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

            path.Reverse();

            //foreach (var item2 in path)
            //{
            //    Debug.Log(item2.ToString());
            //}

            //var car = Instantiate(SelectACarPrefab(), new Vector3(startRoadPosition.x, startRoadPosition.y, 0));
            //Vector2 pos = startStructure.transform.position;
            //var car = Instantiate(SelectACarPrefab(endStructure.buildingType), new Vector3(pos.x, pos.y, 0));
            ////var car = Instantiate(carPrefab, new Vector3(startRoadPosition.x, startRoadPosition.y, 0), Quaternion.identity);

            //Console.WriteLine("Set path2: " + path.Count);
            ////car.GetComponent<CarAI>().SetPath(path.ConvertAll(x => (Vector2)x));
            //car.GetComponent<CarAI>().SetPath(path, ref endStructure);

            if (path.Count == 0 && path.Count > 2)
                return true;

            Console.WriteLine("Structure Type = " + placementManager.placementGrid[startRoadPosition.x, startRoadPosition.y]);

            Console.WriteLine("Start Structure = " + placementManager.GetStructureAt(startRoadPosition).GetCarSpawnMarker(path[1]));

            var startMarkerPosition = placementManager.GetStructureAt(startRoadPosition).GetCarSpawnMarker(path[1]);

            var endMarkerPosition = placementManager.GetStructureAt(endRoadPosition).GetCarEndMarker(path[path.Count - 2]);

            carPath = GetCarPath(path, startMarkerPosition.Position, endMarkerPosition.Position);

            Debug.Log("marker start: " + startMarkerPosition.Position);
            Debug.Log("marker end: " + endMarkerPosition.Position);

            if (carPath.Count > 0)
            {
                var car = Instantiate(SelectACarPrefab(endStructure.buildingType),
                    new Vector3(startMarkerPosition.Position.x, startMarkerPosition.Position.y, 0));
                car.GetComponent<CarAI>().SetPath(carPath);
            }
        }

        return false;
    }

    //private void TrySpawninACar(StructureModel startStructure, StructureModel endStructure)
    //{
    //    if (startStructure != null && endStructure != null)
    //    {
    //        var startRoadPosition = ((INeedingRoad)startStructure).RoadPosition;
    //        var endRoadPosition = ((INeedingRoad)endStructure).RoadPosition;

    //        var path = placementManager.GetPathBetween(startRoadPosition, endRoadPosition, true);
    //        path.Reverse();

    //        if (path.Count == 0 && path.Count > 2)
    //            return;

    //        var startMarkerPosition = placementManager.GetStructureAt(startRoadPosition).GetCarSpawnMarker(path[1]);

    //        var endMarkerPosition = placementManager.GetStructureAt(endRoadPosition).GetCarEndMarker(path[path.Count - 2]);

    //        carPath = GetCarPath(path, startMarkerPosition.Position, endMarkerPosition.Position);

    //        if (carPath.Count > 0)
    //        {
    //            var car = Instantiate(SelectACarPrefab(endStructure.buildingType), 
    //                new Vector3(startMarkerPosition.Position.x, startMarkerPosition.Position.y, 0));
    //            car.GetComponent<CarAI>().SetPath(carPath);
    //        }
    //    }
    //}

    private List<Vector2> GetCarPath(List<Vector2Int> path, Vector2 startPosition, Vector2 endPosition)
    {
        Console.WriteLine("CarGraph Start" + startPosition);
        Console.WriteLine("Car Gatph End" + endPosition);

        carGraph.ClearGraph();
        Console.WriteLine("Next part of the function");

        if (path == null) Console.WriteLine("Path is null     -00000000000000000000000000000000");
        CreateACarGraph(path);
        Console.WriteLine("Next part of the function");
        return AdjacencyGraph.AStarSearch(carGraph, startPosition, endPosition);
    }

    private void CreateACarGraph(List<Vector2Int> path)
    {
        Console.WriteLine("\n\n\n\nStarting everything------------------------------------");
        Dictionary<Marker, Vector2> tempDictionary = new Dictionary<Marker, Vector2>();
        for (int i = 0; i < path.Count; i++)
        {
            Console.WriteLine("Loop count " + i);
            var currentPosition = path[i];
            if (path[i] == null) Console.WriteLine("path[i] is null        -00000000000000000000000000000000");
            var roadStructure = placementManager.GetStructureAt(currentPosition);
            if (placementManager == null) Console.WriteLine("placementManager is null        -00000000000000000000000000000000");
            if (roadStructure == null) Console.WriteLine("roadStructure is null        -00000000000000000000000000000000");
            var markersList = roadStructure.GetCarMarkers();
            var limitDistance = markersList.Count > 3;
            tempDictionary.Clear();
        
            if (markersList == null) Console.WriteLine("markersList is null        -00000000000000000000000000000000");
            foreach (var marker in markersList)
            {
                Console.WriteLine("Marker count " + marker.Position);
                if (marker == null) Console.WriteLine("marker is null        -00000000000000000000000000000000");
                carGraph.AddVertex(marker.Position);
                Console.WriteLine("After AddVertex");
                foreach (var markerNeighbour in marker.adjacentMarkers)
                {
                    Console.WriteLine("counting ");
                    Console.WriteLine("markerNeighbour " + markerNeighbour);
                    carGraph.AddEdge(marker.Position, markerNeighbour);
                }
                Console.WriteLine("Check for open for connection");
                if (marker.OpenForconnections && i + 1 < path.Count)
                {
                    Console.WriteLine("inside if statement openforconnection");
                    var nextRoadPosition = placementManager.GetStructureAt(path[i + 1]);
                    if (limitDistance)
                    {
                        Console.WriteLine("Adding to tempDictionary");
                        tempDictionary.Add(marker, nextRoadPosition.GetNearestCarMarkerTo(marker.Position));
                    }
                    else
                    {
                        Console.WriteLine("Cargraph add edge");
                        carGraph.AddEdge(marker.Position, nextRoadPosition.GetNearestCarMarkerTo(marker.Position));
                    }
                }
            }
            Console.WriteLine("Check limitDistance");
            if (limitDistance && tempDictionary.Count > 2)
            {
                var distanceSortedMarkers = tempDictionary.OrderBy(x => Vector2.Distance(x.Key.Position, x.Value)).ToList();
                
                if(distanceSortedMarkers == null) Console.WriteLine("distanceSortedMarkers is null        -00000000000000000000000000000000");
                foreach (var item in distanceSortedMarkers)
                {
                    Debug.Log(Vector2.Distance(item.Key.Position, item.Value));
                }
                for (int j = 0; j < 2; j++)
                {
                    carGraph.AddEdge(distanceSortedMarkers[j].Key.Position, distanceSortedMarkers[j].Value);
                }
            }
        
            Console.WriteLine("Actually ends one loop in path loop---------------");
        }

        Console.WriteLine("Ending everything------------------------------------\n\n\n\n");
    }

    private Prefab SelectACarPrefab(BuildingType bt)
    {
        //var randomIndex = Random.Range(0, carPrefabs.Length - 1);
        return carPrefabs[(int)bt];
    }
}