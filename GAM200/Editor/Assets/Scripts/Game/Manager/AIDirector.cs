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

    //The number of tile away from lowest that still allow house to be considered a spawner
    int maxTileAway;
    //The number of lesser car that allow the house to be chosen
    int maxCarSpawn;

    //The timer to check for new path (periodically check if shorter path exist)
    public float pathTimerMax;

    public override void Start()
    {
        maxTileAway = 4;
        maxCarSpawn = 2;

        //carSpawnTimerInterval = 2f;
        carPrefabs = new Prefab[5];
        carPrefabs[(int)BuildingType.Hospital] = new Prefab("HospitalCar");
        carPrefabs[(int)BuildingType.Office] = new Prefab("OfficeCar");
        carPrefabs[(int)BuildingType.Park] = new Prefab("ParkCar");
        carPrefabs[(int)BuildingType.Mall] = new Prefab("MallCar");

        placementManager = GameObject.Find("PlacementManager").GetComponent<PlacementManager>();

        structureManager = GameObject.Find("StructureManager").GetComponent<StructureManager>();

        pathTimerMax = 17f;
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

    public bool GetNewPathList(Vector2Int endPos, uint entId, bool reset = false)
    {

        //Dictionary<Vector2Int, int> decisionContainer = new Dictionary<Vector2Int, int>();
        //int pc = structureManager.destinationList[endPos].pathCount;
        //Vector2Int ogStart = structureManager.destinationList[endPos].startPos;
        //int chosenHouseRequestCount = 999;
        //if (structureManager.houseList.ContainsKey(ogStart))
        //{
        //    chosenHouseRequestCount = structureManager.houseList[ogStart].requestLine.Count;
        //
        //    //Reset pc to recalulate for a nearer path when too maxCarSpawn amount of car in queue
        //    if (chosenHouseRequestCount > maxCarSpawn) pc = 0;
        //}
        //
        //if (pc == 0)
        //{
        //    foreach (var startHouse in structureManager.houseList)
        //    {
        //       //Debug.Log("StartHouse " + startHouse.Value.requestLine.Count);
        //
        //        if (pc != 0 && startHouse.Key == structureManager.destinationList[endPos].startPos) continue;
        //
        //        int roadCount;
        //        List<Vector2> list = placementManager.GetPathBetween(startHouse.Key, new Vector2Int(endPos), out roadCount);
        //        if (list.Count == 0) continue;
        //
        //        //The algorithm example:
        //        //low ----------------A----pc----A------ high (list.Count/pc)
        //        //Case 1: Anything to the left of the first A will be chosen as the new path
        //        //Case 2: Anything between the two A will be decided based on the queue size
        //        //Case 3: Anything to the right of 2nd A will not be considered
        //
        //        
        //        if (pc != 0)
        //        {
        //            //Case 3
        //            //Debug.Log(roadCount + " another " + pc + " plus " + maxTileAway);
        //            if (roadCount > pc + maxTileAway) continue;
        //            //if (list.Count > pc) continue;
        //
        //            //Case 2
        //            if ((roadCount >= pc - maxTileAway) && startHouse.Value.requestLine.Count >= maxCarSpawn + chosenHouseRequestCount) continue;
        //            //Debug.Log(startHouse.Value.requestLine.Count + " vs " + chosenHouseRequestCount + " plus " + maxCarSpawn);
        //        }
        //        
        //        
        //        pc = roadCount;
        //        
        //        StartPositionSet sps = new StartPositionSet(startHouse.Key, pc, entId);
        //        structureManager.destinationList[endPos] = sps;
        //        chosenHouseRequestCount = startHouse.Value.requestLine.Count;
        //        //Debug.Log("Chosen count " + chosenHouseRequestCount);
        //       
        //
        //
        //
        //
        //        ////if (list.Count < pc || list.Count < pc + maxTileAway || pc == 0)
        //        //if (list.Count < pc || pc == 0)
        //        //{
        //        //    //If a house that is about maxTileAway tiles away, has maxCarSpawn lesser
        //        //    //if (pc - list.Count < maxTileAway)
        //        //    //{
        //        //    //    if (startHouse.Value.requestLine.Count >= maxCarSpawn + chosenHouseRequestCount)
        //        //    //    {
        //        //    //        continue;
        //        //    //    }
        //        //    //}
        //        //    //Debug.Log(list.Count + " vs old: " + pc);
        //        //    pc = list.Count;
        //        //    //structureManager.destinationList[endPos].SetPath(i.Key, pc, list);
        //        //    StartPositionSet sps = new StartPositionSet(startHouse.Key, pc);
        //        //    structureManager.destinationList[endPos] = sps;
        //        //    chosenHouseRequestCount = startHouse.Value.requestLine.Count;
        //        //    //Console.WriteLine("Setting the path " + list.Count + " " + structureManager.destinationList[endPos].pathCount );
        //        //}
        //
        //
        //    }
        //}
        //
        //if (pc == 0) return false;
        //return true;


        //-----------------------------------------------------------------------
        int pc = structureManager.destinationList[endPos].pathCount;
        if (pc == 0 || reset)
        {
            foreach (var startHouse in structureManager.houseList)
            {
                if (pc != 0 && startHouse.Key == structureManager.destinationList[endPos].startPos) continue;

                int roadNum;
                List<Vector2> list = placementManager.GetPathBetween(startHouse.Key, new Vector2Int(endPos), out roadNum);
                if (list.Count == 0) continue;

                if (list.Count < pc || pc == 0)
                {
                    pc = list.Count;
                    //structureManager.destinationList[endPos].SetPath(i.Key, pc, list);

                    StartPositionSet sps = new StartPositionSet(startHouse.Key, pc, entId);

                    structureManager.destinationList[endPos] = sps;
                    //Console.WriteLine("Setting the path " + list.Count + " " + structureManager.destinationList[endPos].pathCount );

                }

                //else if (list.Count == pc)
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
        if (!GetNewPathList(endPos, endStructure.entityId)) return false;

        //Debug.Log(GameObject.FindWithId(endStructure.entityId).entityId + " " + endStructure.entityId);

        //var path = placementManager.GetPathBetween(new Vector2Int(startStructure.transform.position), new Vector2Int(endPos), true);
        CarSpawner cs = structureManager.houseList[structureManager.destinationList[endPos].startPos];
        //if (cs == null) Console.WriteLine("Cs is null");
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

    //Actually spawning it called by CarSpawner
    public void SpawnCar(Vector2 spawnPos, uint id, BuildingType bt, Vector2Int endPos)
    {
        //if (structureManager.destinationList[endPos].pathCount == 0)
        //{
        //
        //    GetNewPathList(endPos);
        //}
        Vector2Int spawnPosInt = new Vector2Int(spawnPos);
        //Debug.Log(spawnPosInt);
        //var path = placementManager.GetPathBetween(structureManager.destinationList[endPos].startPos, new Vector2Int(endPos), true);
        int roadCount;
        uint prevEntId = structureManager.destinationList[endPos].entityId;

        var path = placementManager.GetPathBetween(spawnPosInt, new Vector2Int(endPos), out roadCount);
        //Console.WriteLine("New path is " + path.Count);
        if (path.Count == 0 || prevEntId != structureManager.destinationList[endPos].entityId)
        {
            //GetComponent<StructureModel>(structureManager.destinationList[endPos].entityId).SetSpawnBool(true);
            GetComponent<StructureModel>(prevEntId).SetSpawnBool(true);
            structureManager.destinationList[endPos] = new StartPositionSet(new Vector2Int(0, 0), 0, 0);
            return;
        }
       
        //Vector2 pos = structureManager.destinationList[endPos].startPos;

        //var car = Instantiate(SelectACarPrefab(bt), new Vector3(pos.x, pos.y, 0), 2);
        var car = Instantiate(SelectACarPrefab(bt), new Vector3(spawnPosInt.x, spawnPosInt.y, 0), 2);
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