using System;
using System.Collections;
using System.Collections.Generic;

public class AIDirector : MonoBehaviour
{
    public PlacementManager placementManager;
    private StructureManager structureManager;

    public Prefab[] carPrefabs;

    AdjacencyGraph carGraph = new AdjacencyGraph();

    List<Vector3> carPath = new List<Vector3>();

    //public float carSpawnTimerInterval;

    public override void Start()
    {
        //carSpawnTimerInterval = 2f;
        carPrefabs = new Prefab[5];
        carPrefabs[(int)BuildingType.Hospital] = new Prefab("HospitalCar");
        carPrefabs[(int)BuildingType.Office] = new Prefab("OfficeCar");
        carPrefabs[(int)BuildingType.Park] = new Prefab("ParkCar");
        carPrefabs[(int)BuildingType.Mall] = new Prefab("MallCar");

        placementManager = GameObject.Find("PlacementManager").GetComponent<PlacementManager>();

        structureManager = GameObject.Find("StructureManager").GetComponent<StructureManager>();
    }
    //public void SpawnACar()
    //{
    //    foreach (var house in placementManager.GetAllHouses())
    //    {
    //        TrySpawninACar(house, placementManager.GetRandomSpecialStrucutre());
    //    }
    //}

    //public bool SpawnToDestination(StructureModel endHouse)
    public bool SpawnToDestination(StructureModel endHouse)
    {

        //if (endHouse != null)
            return TrySpawninACar(endHouse);
            //return TrySpawninACar(placementManager.GetRandomHouseStructure(), endHouse);
        //return false;
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

    private bool GetNewPathList(Vector2Int endPos)
    {
        int pc = structureManager.destinationList[endPos].pathCount;
        if (pc == 0)
        {
            foreach (var i in structureManager.houseList)
            {
                if (pc != 0 && i.Key == structureManager.destinationList[endPos].startPos) continue;

                List<Vector2> list = placementManager.GetPathBetween(i.Key, new Vector2Int(endPos), true);
                if (list.Count == 0) continue;

                if (list.Count < pc || pc == 0)
                {
                    pc = list.Count;
                    //structureManager.destinationList[endPos].SetPath(i.Key, pc, list);
                    StartPositionSet sps = new StartPositionSet(i.Key, pc);
                    structureManager.destinationList[endPos] = sps;
                    //Console.WriteLine("Setting the path " + list.Count + " " + structureManager.destinationList[endPos].pathCount );

                }
            }
        }

        if (pc == 0) return false;
        return true;
    }

    //private bool TrySpawninACar(StructureModel startStructure, StructureModel endStructure)
    private bool TrySpawninACar(StructureModel endStructure)
    {
        //Console.WriteLine("here but go in ?");
        if (endStructure == null) return false;

        //Console.WriteLine(" actually inside ");
        //if(startStructure == null) Console.WriteLine("is null");
        //if(startStructure != null) Console.WriteLine("is not null");
        //var startRoadPosition = Vector2Int.RoundToInt(((INeedingRoad)startStructure).RoadPosition);
        ////Console.WriteLine("after start");
        //var endRoadPosition = Vector2Int.RoundToInt(((INeedingRoad)endStructure).RoadPosition);

        //Debug.Log(startRoadPosition);
        //Debug.Log(endRoadPosition);
        Vector2Int endPos = new Vector2Int(endStructure.transform.position);
        if (!GetNewPathList(endPos)) return false;

        //Debug.Log(GameObject.FindWithId(endStructure.entityId).entityId + " " + endStructure.entityId);

        //var path = placementManager.GetPathBetween(new Vector2Int(startStructure.transform.position), new Vector2Int(endPos), true);
        CarSpawner cs = structureManager.houseList[structureManager.destinationList[endPos].startPos];
        if (cs == null) Console.WriteLine("Cs is null");
        cs.RequestSpawn(new EndStruct(endStructure.entityId, endStructure.buildingType, endPos));


        //var path = placementManager.GetPathBetween(structureManager.destinationList[endPos].startPos, new Vector2Int(endPos), true);
        ////Console.WriteLine("New path is " + path.Count);
        //if (path.Count == 0)
        //{
        //    structureManager.destinationList[endPos] = new StartPositionSet(new Vector2Int(0, 0), 0);
        //    return false;
        //}
        //
        ////return;
        ////if (path == null) return;
        ////Console.WriteLine("Set path: " + path.Count);
        ////foreach (var item in path)
        ////{
        ////    Debug.Log(item.ToString());
        ////}
        //
        ////path.Reverse();
        ////path.Add(Vector2Int.RoundToInt(endStructure.transform.position)); //Make car enter house
        ////foreach (var item2 in path)
        ////{
        ////    Debug.Log(item2.ToString());
        ////}
        //
        ////var car = Instantiate(SelectACarPrefab(), new Vector3(startRoadPosition.x, startRoadPosition.y, 0));
        ////Vector2 pos = startStructure.transform.position;
        //Vector2 pos = structureManager.destinationList[endPos].startPos;
        //var car = Instantiate(SelectACarPrefab(endStructure.buildingType), new Vector3(pos.x, pos.y, 0), 2);
        ////var car = Instantiate(carPrefab, new Vector3(startRoadPosition.x, startRoadPosition.y, 0), Quaternion.identity);
        //
        ////Console.WriteLine("Set path2: " + path.Count);
        ////car.GetComponent<CarAI>().SetPath(path.ConvertAll(x => (Vector2)x));
        //car.GetComponent<CarAI>().SetPath(path, ref endStructure);
        return true;
    }

    public void SpawnCar(uint id, BuildingType bt, Vector2Int endPos)
    {
        if (structureManager.destinationList[endPos].pathCount == 0)
            GetNewPathList(endPos);

        var path = placementManager.GetPathBetween(structureManager.destinationList[endPos].startPos, new Vector2Int(endPos), true);
        //Console.WriteLine("New path is " + path.Count);
        if (path.Count == 0)
        {
            structureManager.destinationList[endPos] = new StartPositionSet(new Vector2Int(0, 0), 0);
            return;
        }
       
        Vector2 pos = structureManager.destinationList[endPos].startPos;

        var car = Instantiate(SelectACarPrefab(bt), new Vector3(pos.x, pos.y, 0), 2);
        //var car = Instantiate(carPrefab, new Vector3(startRoadPosition.x, startRoadPosition.y, 0), Quaternion.identity);
       
        //Console.WriteLine("Set path2: " + path.Count);
        //car.GetComponent<CarAI>().SetPath(path.ConvertAll(x => (Vector2)x));
        car.GetComponent<CarAI>().SetPath(path, id);
    }

    private Prefab SelectACarPrefab(BuildingType bt)
    {
        //var randomIndex = Random.Range(0, carPrefabs.Length - 1);
        return carPrefabs[(int)bt];
    }
}