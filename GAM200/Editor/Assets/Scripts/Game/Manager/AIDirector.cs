using System;
using System.Collections;
using System.Collections.Generic;

public enum RouteType
{
    HouseToDest = 0,
    DestToHouse
}
public class AIDirector : MonoBehaviour
{
    public PlacementManager placementManager;
    private StructureManager structureManager;

    public Prefab[] carPrefabs;

    public override void Start()
    {

        carPrefabs = new Prefab[(int)BuildingType.House];
        carPrefabs[(int)BuildingType.Hospital] = new Prefab("HospitalCar");
        carPrefabs[(int)BuildingType.Office] = new Prefab("OfficeCar");
        carPrefabs[(int)BuildingType.Park] = new Prefab("ParkCar");
        carPrefabs[(int)BuildingType.Mall] = new Prefab("MallCar");
        carPrefabs[(int)BuildingType.PoliceStation] = new Prefab("PoliceCar");

        placementManager = GameObject.Find("PlacementManager").GetComponent<PlacementManager>();

        structureManager = GameObject.Find("StructureManager").GetComponent<StructureManager>();
    }
    

    //public bool GetNewPathList(Vector2Int endPos, uint entId, RouteType rt, bool reset = false)
    //{
    //    //-----------------------------------------------------------------------
    //    int pc = structureManager.destinationList[endPos].pathCount;
    //    if (pc == 0 || reset)
    //    {
    //        foreach (var startHouse in structureManager.houseList)
    //        {
    //            if (pc != 0 && startHouse.Key == structureManager.destinationList[endPos].startPos) continue;
    //
    //            //int roadNum;
    //            //List<Vector2> list = placementManager.GetPathBetween(startHouse.Key, new Vector2Int(endPos), out roadNum);
    //            Vector2Int startPos = startHouse.Key;
    //            List<Vector2> list = placementManager.GetPathBetween(out startPos, new Vector2Int(endPos), rt);
    //            if (list.Count == 0) continue;
    //
    //            if (list.Count < pc || pc == 0)
    //            {
    //                pc = list.Count;
    //                //structureManager.destinationList[endPos].SetPath(i.Key, pc, list);
    //
    //                StartPositionSet sps = new StartPositionSet(startHouse.Key, pc, entId);
    //
    //                structureManager.destinationList[endPos] = sps;
    //                //Console.WriteLine("Setting the path " + list.Count + " " + structureManager.destinationList[endPos].pathCount );
    //
    //            }
    //
    //            //else if (list.Count == pc)
    //        }
    //    }
    //
    //    if (pc == 0) return false;
    //    return true;
    //}

    //Spawning Car with position
    public bool SpawnCar(Vector2 spawnPos, uint startId, BuildingType bt, Vector2Int endPos, RouteType rt)
    {

        Vector2Int spawnPosInt = new Vector2Int(spawnPos);
        
        //int roadCount;
        //uint prevEntId = structureManager.destinationList[endPos].entityId;

        //var path = placementManager.GetPathBetween(spawnPosInt, new Vector2Int(endPos), rt, out roadCount);
        var path = placementManager.GetPathBetween(out spawnPosInt, new Vector2Int(endPos), rt);
        
        //if (path.Count == 0 || prevEntId != structureManager.destinationList[endPos].entityId)
        if (path.Count == 0)
        {
            //GetComponent<StructureModel>(prevEntId).SetSpawnBool(true);
            //structureManager.destinationList[endPos] = new StartPositionSet(new Vector2Int(0, 0), 0, 0);
            return false;
        }

        var car = Instantiate(SelectACarPrefab(bt), new Vector3(spawnPosInt.x, spawnPosInt.y, 0), 2);
        car.GetComponent<CarAI>().SetPath(path, 0, 0);

        return true;
    }

    //Return true if spawn
    //possibleDest is when the house previously spawned in that place
    //If return false, then it will retry spawn at a later time
    public bool SelectADestAndSpawn(Vector2Int startPos, uint startId, PosIdSet[] possibleDest, out BuildingType outBt, out PosIdSet posIdSet)
    {
        BuildingType bt = structureManager.GetRandomBuildingType();

        outBt = bt;
        posIdSet = new PosIdSet(0, startPos);


        if (bt == BuildingType.None) return false;

        if (possibleDest[(int)bt].pos != startPos)
        {
            //Debug.Log("Using this");
            //int roadNum;
            //List<Vector2> list = placementManager.GetPathBetween(startPos, possibleDest[(int)bt].pos, out roadNum);
            List<Vector2> list = placementManager.GetPathBetween(out startPos, possibleDest[(int)bt].pos, RouteType.HouseToDest);

            if (list.Count != 0)
            {
                var car = Instantiate(SelectACarPrefab(bt), new Vector3(startPos.x, startPos.y, 0), 2);
                car.GetComponent<CarAI>().SetPath(list, possibleDest[(int)bt].entityId, startId);

                posIdSet = new PosIdSet(possibleDest[(int)bt].entityId, possibleDest[(int)bt].pos);
                return true;
                //Skip the major check
            }
            //Debug.Log("Unsuccessful " + list.Count + "  " + bt  + "   "+ possibleDest[(int)bt].pos);
        }

        List<Vector2> path = new List<Vector2>();
        int count = 0;
        uint newId = 0;
        foreach (var endDestination in structureManager.destinationList[(int)bt])
        {
            //int roadNum;
            List<Vector2> list = placementManager.GetPathBetween(out startPos, endDestination.pos, RouteType.HouseToDest);
            //List<Vector2> list = placementManager.GetPathBetween(startPos, endDestination.pos, out roadNum);
            if (list.Count == 0) continue;

            if (list.Count < count || count == 0)
            {
                count = list.Count;
                path = list;
                newId = endDestination.entityId;
            }
        }

        if (count != 0)
        {
            var car = Instantiate(SelectACarPrefab(bt), new Vector3(startPos.x, startPos.y, 0), 2);
            car.GetComponent<CarAI>().SetPath(path, newId, startId);
            posIdSet = new PosIdSet(possibleDest[(int)bt].entityId, startPos);

            return true;
        }
        return false;
    }


    //Used to retry spawn
    public bool SpawnRetryWithType(Vector2Int startPos, BuildingType bt, uint startId)
    {
        List<Vector2> path = new List<Vector2>();
        int count = 0;
        uint newId = 0;
        foreach (var endDestination in structureManager.destinationList[(int)bt])
        {
            //int roadNum;
            //List<Vector2> list = placementManager.GetPathBetween(startPos, endDestination.pos, out roadNum);
            List<Vector2> list = placementManager.GetPathBetween(out startPos, endDestination.pos, RouteType.HouseToDest);
            if (list.Count == 0) continue;

            if (list.Count < count || count == 0)
            {
                count = list.Count;
                path = list;
                newId = endDestination.entityId;
            }
        }

        if (count != 0)
        {
            var car = Instantiate(SelectACarPrefab(bt), new Vector3(startPos.x, startPos.y, 0), 2);
            car.GetComponent<CarAI>().SetPath(path, newId, startId);
            return true;
        }
        return false;
    }

    private Prefab SelectACarPrefab(BuildingType bt)
    {
        //var randomIndex = Random.Range(0, carPrefabs.Length - 1);
        return carPrefabs[(int)bt];
    }
}