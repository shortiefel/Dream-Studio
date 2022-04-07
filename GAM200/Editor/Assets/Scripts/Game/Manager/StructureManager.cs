using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

public enum BuildingType
{
    Hospital = 0,
    Office,
    Park,
    Mall,
    PoliceStation,
    //Destination must be above this line------------------
    //Dont add anything between the previous comment and House
    House, 
    COUNT,
    None
}

public struct StartPositionSet
{
    public Vector2Int startPos;
    public int pathCount;
    public uint entityId;

    public StartPositionSet(Vector2Int newPos, int pc, uint entId)
    {
        startPos = newPos;
        pathCount = pc;
        entityId = entId;
    }
}

public struct PosIdSet
{
    public uint entityId;
    public Vector2Int pos;

    public PosIdSet(uint id, Vector2Int ep)
    {
        entityId = id;
        pos = ep;
    }
}

public struct StructurePrefabWeighted
{
    public GameObject prefab;
    //[Range(0, 1)]
    public float weight;
}

public class StructureManager : MonoBehaviour
{
    public StructurePrefabWeighted[] housesPrefabs, specialPrefabs;
    public PlacementManager placementManager;
    MoneySystem moneySystem;
    //public NotificationManager notificationManager;


    private float[] houseWeights, specialWeights;

    public Dictionary<Vector2Int, CarSpawner> houseList;
    public List<PosIdSet>[] destinationList;

    //private float pathTimerMax;
   
    //private void Start()
    public override void Start()
    {

        placementManager = GameObject.Find("PlacementManager").GetComponent<PlacementManager>();
        moneySystem = GameObject.Find("MoneyText").GetComponent<MoneySystem>();
        housesPrefabs = new StructurePrefabWeighted[2];
        housesPrefabs[0].prefab = new GameObject(new Prefab("House")); housesPrefabs[0].weight = 1;

        specialPrefabs = new StructurePrefabWeighted[(int)BuildingType.COUNT];
        //specialPrefabs[0].prefab = new GameObject(new Prefab("Destination")); specialPrefabs[0].weight = 1;

        specialPrefabs[(int)BuildingType.Hospital].prefab = new GameObject(new Prefab("HospitalDestination")); specialPrefabs[(int)BuildingType.Hospital].weight = 1;
        specialPrefabs[(int)BuildingType.Office].prefab = new GameObject(new Prefab("OfficeDestination")); specialPrefabs[(int)BuildingType.Office].weight = 1;
        specialPrefabs[(int)BuildingType.Park].prefab = new GameObject(new Prefab("ParkDestination")); specialPrefabs[(int)BuildingType.Park].weight = 1;
        specialPrefabs[(int)BuildingType.Mall].prefab = new GameObject(new Prefab("MallDestination")); specialPrefabs[(int)BuildingType.Mall].weight = 1;
        specialPrefabs[(int)BuildingType.PoliceStation].prefab = new GameObject(new Prefab("PoliceStationDestination")); specialPrefabs[(int)BuildingType.PoliceStation].weight = 1;

        houseWeights = new float[] { housesPrefabs[0].weight };
        specialWeights = new float[] 
        { specialPrefabs[(int)BuildingType.Hospital].weight
        , specialPrefabs[(int)BuildingType.Office].weight 
        , specialPrefabs[(int)BuildingType.Park].weight 
        , specialPrefabs[(int)BuildingType.Mall].weight 
        , specialPrefabs[(int)BuildingType.PoliceStation].weight 
        };

        houseList = new Dictionary<Vector2Int, CarSpawner>();

        //Use House because everything before are destination buildings
        destinationList = new List<PosIdSet>[(int)BuildingType.House];
        destinationList[(int)BuildingType.Hospital] = new List<PosIdSet>();
        destinationList[(int)BuildingType.Office] = new List<PosIdSet>();
        destinationList[(int)BuildingType.Park] = new List<PosIdSet>();
        destinationList[(int)BuildingType.Mall] = new List<PosIdSet>();
        destinationList[(int)BuildingType.PoliceStation] = new List<PosIdSet>();
    }


    public BuildingType GetRandomBuildingType()
    {
        
        //For randomly spawning Destination (This algorithm randomly selects destination that exists in game)
        {
            //List<int> tempBt = new List<int>();
            //for (int i = 0; i < (int)BuildingType.House; i++)
            //{
            //    if (destinationList[i].Count > 0) tempBt.Add(i);
            //}
            //
            //if (tempBt.Count == 0) { Debug.Log("No Destination detected"); return BuildingType.None; }
            //
            //return (BuildingType)(tempBt[Random.Range(0, tempBt.Count - 1)]);
        }

        //For player controlled spawning Destination (This algorithm randomly selects destination from all destination)
        {
            return (BuildingType)(Random.Range(0, (int)BuildingType.House - 1));
        }
    }
    public bool PlaceHouse(Vector2Int position, float rotation)
    {
        //Debug.Log("here house " + position);
        if (CheckPositionBeforePlacement(position, CellType.Structure))
        {
        //Debug.Log("place house " + position);
            int randomIndex = GetRandomWeightedIndex(houseWeights);
            GameObject go = placementManager.PlaceObjectOnTheMap(position, housesPrefabs[randomIndex].prefab, CellType.Structure, rotation);
            houseList.Add(position, go.GetComponent<CarSpawner>());
            //AudioPlayer.instance.PlayPlacementSound();
            //StartCoroutine(waitABit(position));
            return true;
        }

        return false;
    }

    public void RemoveDestination(Vector2Int position)
    {
        placementManager.RemoveDestination(position);
    }

    public bool PlaceSpecial(Vector2Int position, BuildingType _bt,  float rotation = 0)
    {
        if (CheckPositionBeforePlacement(position, CellType.SpecialStructure))
        {
            //int randomIndex = GetRandomWeightedIndex(specialWeights);
            uint id = placementManager.PlaceObjectOnTheMap(position, specialPrefabs[(int)_bt].prefab, CellType.SpecialStructure, rotation).entityId;
            destinationList[(int)_bt].Add(new PosIdSet(id, position));
            Debug.Log("Created special with id " + id);
            //AudioPlayer.instance.PlayPlacementSound();
            return true;
        }

        return false;
    }

    public void PlaceDestHospital(Vector2Int position)
    {
        if(moneySystem.BuyHospital())
            PlaceSpecial(position, BuildingType.Hospital, 0);
    }
    public void PlaceDestOffice(Vector2Int position)
    {
        if(moneySystem.BuyOffice())
            PlaceSpecial(position, BuildingType.Office, 0);
    }
    public void PlaceDestPark(Vector2Int position)
    {
        if(moneySystem.BuyPark())
            PlaceSpecial(position, BuildingType.Park, 0);
    }
    public void PlaceDestMall(Vector2Int position)
    {
        if(moneySystem.BuyMall())
            PlaceSpecial(position, BuildingType.Mall, 0);
    }

    public void PlaceDestPoliceStation(Vector2Int position)
    {
        if(moneySystem.BuyPoliceStation())
            PlaceSpecial(position, BuildingType.PoliceStation, 0);
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
    public bool CheckPositionBeforePlacement(Vector2Int position, CellType cellType)
    {
        if (cellType == CellType.Structure) 
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

            if (placementManager.placementGrid.IsSurrounded(position, cellType) == true)
            {
                Debug.Log("This surrounding already has buildings");
                return false;
            }
        }

        else if (cellType == CellType.SpecialStructure)
        {
            Vector2Int rightPos = new Vector2Int(position.x + 1, position.y);
            Vector2Int upPos = new Vector2Int(position.x, position.y + 1);
            Vector2Int rightUpPos = new Vector2Int(position.x + 1, position.y + 1);

            if (placementManager.CheckIfPositionInBound(position) == false ||
                placementManager.CheckIfPositionInBound(rightPos) == false ||
                placementManager.CheckIfPositionInBound(upPos) == false ||
                placementManager.CheckIfPositionInBound(rightUpPos) == false)
            {
                Debug.Log("This position is out of bounds");
                return false;
            }

            if (placementManager.CheckIfPositionIsFree(position) == false ||
                placementManager.CheckIfPositionIsFree(rightPos) == false ||
               placementManager.CheckIfPositionIsFree(upPos) == false ||
               placementManager.CheckIfPositionIsFree(rightUpPos) == false)
            {
                Debug.Log("This position is not EMPTY");
                return false;
            }


            //Comment this to allow destination to spawn beside each other--------------------------------------------------------------------
            //if (placementManager.placementGrid.IsSurrounded(position, cellType) == true ||
            //   placementManager.placementGrid.IsSurrounded(rightPos, cellType) == true ||
            //   placementManager.placementGrid.IsSurrounded(upPos, cellType) == true ||
            //   placementManager.placementGrid.IsSurrounded(rightUpPos, cellType) == true)
            //{
            //    Debug.Log("This surrounding already has buildings");
            //    return false;
            //}
        }

        return true;
    }
}
