using System;
using System.Collections;
using System.Collections.Generic;

public class RoadManager : MonoBehaviour
{
    public PlacementManager placementManager;
    public RoadFixer roadFixer;
    public StructureManager structureManager;

    //public List<Vector2Int> temporaryPlacementPositions;
    private int temporaryRoadCount;
    public int taxRoadCount;

    //private List<Vector2Int> roadPositionsToRecheck;

    //private Vector2Int startPosition;
    //private Vector2Int randomDestinationPosition;
    //private bool placementMode;

    private AudioSource placeSound;
    private AudioSource removeSound;

    //private GameObject trafficLightGO;
    //private GameObject erpGO;
    public TrafficLightManager trafficLightManager;
    public ERPManager erpManager;

    public List<Vector2Int> temporaryRoadPositions;

    //public int roadCount;
    private int previousRoadMinus;

    float timer;
    bool addToTime;

    Transform removeCarTransform;
    Collider removeCarCollider;
    bool removeCarBool;
    float removeCarTimer;

    MoneySystem moneySystem;

    public override void Start()
    {
        roadFixer = GetComponent<RoadFixer>();
        placementManager = GameObject.Find("PlacementManager").GetComponent<PlacementManager>();
        structureManager = GameObject.Find("StructureManager").GetComponent<StructureManager>();

        //temporaryPlacementPositions = new List<Vector2Int>();
        temporaryRoadCount = 0;

        //roadPositionsToRecheck = new List<Vector2Int>();

        //placementMode = false;

        placeSound = GameObject.Find("DrawRoad").GetComponent<AudioSource>();
        removeSound = GameObject.Find("RemoveRoad").GetComponent<AudioSource>();


        //trafficLightGO = new GameObject(new Prefab("TrafficLight"));
        //erpGO = new GameObject(new Prefab("ERP"));

        //GameObject trafficLightManagerGO = GameObject.Find("TrafficManager");
        //if (trafficLightManagerGO != null)
        //{
        //    trafficLightManager = trafficLightManagerGO.GetComponent<TrafficLightManager>();
        //}
        GameObject go = GameObject.Find("TrafficManager");
        if (go != null)
            trafficLightManager = go.GetComponent<TrafficLightManager>();

        GameObject go2 = GameObject.Find("ERPManager");
        if (go2 != null)
            erpManager = go2.GetComponent<ERPManager>();

        temporaryRoadPositions = new List<Vector2Int>();

        //roadCount = 20;
        previousRoadMinus = 0;

        timer = 0f;
        addToTime = false;

        removeCarTransform = GameObject.Find("RemoveCarCollider").GetComponent<Transform>();
        removeCarCollider = GameObject.Find("RemoveCarCollider").GetComponent<Collider>();
        removeCarBool = false;
        removeCarTimer = 0f;

        moneySystem = GameObject.Find("MoneyText").GetComponent<MoneySystem>();
    }
    public void PlaceSpawnHouse(Vector2Int position)
    {
        /*if (placementManager.CheckIfPositionInBound(position) == false)
            return;
        if (placementManager.CheckIfPositionIsFree(position) == false)
            return;

        temporaryPlacementPositions.Clear();
        roadPositionsToRecheck.Clear();

        startPosition = position;
        //Debug.Log(position);

        temporaryPlacementPositions.Add(position);

        int random = Random.Range(0, 3);
        int structureRotate = 0;
        int roadRotate = 0;

        int randomX = position.x;
        int randomY = position.y;

        if (random == 0)
        {
            structureRotate = 0;
            roadRotate = 180;
            randomDestinationPosition.x = randomX;
            randomDestinationPosition.y = randomY + 1;
        }
        else if (random == 1)
        {
            structureRotate = 90;
            roadRotate = 270;
            randomDestinationPosition.x = randomX - 1;
            randomDestinationPosition.y = randomY;
        }
        else if (random == 2)
        {
            structureRotate = 180;
            roadRotate = 0;
            randomDestinationPosition.x = randomX;
            randomDestinationPosition.y = randomY - 1;
        }
        else if (random == 3)
        {
            structureRotate = 270;
            roadRotate = 90;
            randomDestinationPosition.x = randomX + 1;
            randomDestinationPosition.y = randomY;
        }

        placementManager.PlaceTemporaryStructure(position, roadFixer.deadEnd, CellType.Road, 1, false, roadRotate);
        structureManager.PlaceHouse(randomDestinationPosition, structureRotate);

        placementManager.AddtemporaryStructuresToStructureDictionary();
        temporaryPlacementPositions.Clear();
        //startPosition = Vector2Int.zero;

        //foreach (var positionsToFix in roadPositionsToRecheck)
        //{
        //    roadFixer.FixRoadAtPosition(placementManager, positionsToFix);
        //}

        //roadPositionsToRecheck.Clear();

        //temporaryPlacementPositions = placementManager.GetPathBetween(startPosition, position);

        //foreach (var temporaryPosition in temporaryPlacementPositions)
        //{
        //    if (placementManager.CheckIfPositionIsFree(temporaryPosition) == false)
        //    {
        //        roadPositionsToRecheck.Add(temporaryPosition);
        //        continue;
        //    }
        //    placementManager.PlaceTemporaryStructure(temporaryPosition, roadFixer.deadEnd, CellType.Road, 1);
        //}

        FixRoadPrefabs();*/

        //if (placementManager.CheckIfPositionInBound(position) == false)
        //    return;
        //if (placementManager.CheckIfPositionIsFree(position) == false)
        //    return;
        //
        //structureManager.PlaceHouse(randomDestinationPosition, 0);
    }

    public void PlaceSpawnDestination(Vector2Int position)
    {
        /*if (placementManager.CheckIfPositionInBound(position) == false)
            return;
        if (placementManager.CheckIfPositionIsFree(position) == false)
            return;

        temporaryPlacementPositions.Clear();
        roadPositionsToRecheck.Clear();

        startPosition = position;
        //Debug.Log(position);

        temporaryPlacementPositions.Add(position);

        int random = Random.Range(0, 3);
        int structureRotate = 0;
        int roadRotate = 0;

        int randomX = position.x;
        int randomY = position.y;

        if (random == 0)
        {
            structureRotate = 0;
            roadRotate = 180;
            randomDestinationPosition.x = randomX;
            randomDestinationPosition.y = randomY + 1;
        }
        else if (random == 1)
        {
            structureRotate = 90;
            roadRotate = 270;
            randomDestinationPosition.x = randomX - 1;
            randomDestinationPosition.y = randomY;
        }
        else if (random == 2)
        {
            structureRotate = 180;
            roadRotate = 0;
            randomDestinationPosition.x = randomX;
            randomDestinationPosition.y = randomY - 1;
        }
        else if (random == 3)
        {
            structureRotate = 270;
            roadRotate = 90;
            randomDestinationPosition.x = randomX + 1;
            randomDestinationPosition.y = randomY;
        }

        placementManager.PlaceTemporaryStructure(position, roadFixer.deadEnd, CellType.Road, 1, false, roadRotate);
        structureManager.PlaceSpecial(randomDestinationPosition, structureRotate);

        placementManager.AddtemporaryStructuresToStructureDictionary();
        temporaryPlacementPositions.Clear();
        //startPosition = Vector2Int.zero;

        //foreach (var positionsToFix in roadPositionsToRecheck)
        //{
        //    roadFixer.FixRoadAtPosition(placementManager, positionsToFix);
        //}

        //roadPositionsToRecheck.Clear();

        //temporaryPlacementPositions = placementManager.GetPathBetween(startPosition, position);

        //foreach (var temporaryPosition in temporaryPlacementPositions)
        //{
        //    if (placementManager.CheckIfPositionIsFree(temporaryPosition) == false)
        //    {
        //        roadPositionsToRecheck.Add(temporaryPosition);
        //        continue;
        //    }
        //    placementManager.PlaceTemporaryStructure(temporaryPosition, roadFixer.deadEnd, CellType.Road, 1);
        //}

        FixRoadPrefabs();*/


        //if (placementManager.CheckIfPositionInBound(position) == false)
        //    return;
        //if (placementManager.CheckIfPositionIsFree(position) == false)
        //    return;
        //
        //structureManager.PlaceSpecial(randomDestinationPosition, 0);
    }

    public void PlaceRoad(Vector2Int position)
    {

        if (placementManager.CheckIfPositionInBound(position) == false)
            return;
        if (temporaryRoadPositions.Count > 0 && temporaryRoadPositions[temporaryRoadPositions.Count - 1] == position)
            return;
        
        //if (temporaryRoadCount >= 20)
        //{
        //    Debug.Log("Max temporary road count reached (RoadManager PlaceRoad)");
        //    return;
        //}
        if (temporaryRoadPositions.Count > 0)
        {
            //Tile should be side by side to last tile so in the event that
            //the user draw too quickly that it becomes diagonal, it would not be added
            Vector2Int lp = temporaryRoadPositions[temporaryRoadPositions.Count - 1];

            int count = 0;
            if (lp.x == position.x + 1 || lp.x == position.x - 1) 
                if (lp.y == position.y) 
                    ++count;
            if (lp.y == position.y + 1 || lp.y == position.y - 1)
                if (lp.x == position.x) 
                    ++count;

            if (count != 1) return;
        }
        //Console.WriteLine("Adding ");
        temporaryRoadPositions.Add(position);

        if (temporaryRoadCount == temporaryRoadPositions.Count) return;
        //if(roadCount == 1 && temporaryRoadPositions.Count > 1)
        //{
        //    if (placementManager.placementGrid.IsPosFree(temporaryRoadPositions[0])
        //        && placementManager.placementGrid.IsPosFree(temporaryRoadPositions[1]))
        //        return;
        //}

        //if (temporaryRoadPositions.Count == 1)
        //{
        //    bool state0 = placementManager.placementGrid.IsPosFree(temporaryRoadPositions[0]);
        //    if (state0 && MoneySystem.money < 20)
        //    {
        //        temporaryRoadPositions.Clear();
        //        return;
        //    }
        //}

        if (temporaryRoadPositions.Count > 1)
        {
            bool state0 = placementManager.placementGrid.IsPosFree(temporaryRoadPositions[temporaryRoadPositions.Count - 2]);
            bool state1 = placementManager.placementGrid.IsPosFree(temporaryRoadPositions[temporaryRoadPositions.Count - 1]);


            if (state0 && state1 && MoneySystem.money < 40)
            {
                temporaryRoadPositions.Clear();
                moneySystem.RoadDisplayNotEnoughMoney();
                return;
            }
            if ((state0 || state1) && MoneySystem.money < 20)
            {
                temporaryRoadPositions.Clear();
                moneySystem.RoadDisplayNotEnoughMoney();
                return;
            }
        }

        int tmp = placementManager.placementGrid.SetRoad(temporaryRoadPositions);
        //Debug.Log("stuff");
        if (tmp > 0)
        {
            placeSound.Play();
            for (int i = 0; i < tmp; i++)
            {
                moneySystem.BuyRoad();
            }
        }

        //roadCount -= tmp;
        taxRoadCount += tmp;
 
        if (temporaryRoadPositions.Count == 2)
        {
            temporaryRoadPositions.RemoveAt(0);
        }

        temporaryRoadCount = temporaryRoadPositions.Count;
    }

    public override void Update()
    {
        //Debug.Log(temporaryRoadPositions.Count);
        if (Input.GetKeyDown(KeyCode.O)) placementManager.placementGrid.PrintGridOut();

        if (removeCarBool)
        {
            removeCarTimer += Time.deltaTime;
            if (removeCarTimer >= 0.3f)
            {
                removeCarTimer = 0f;
                removeCarBool = false;
                Disable<Collider>(removeCarCollider);
            }
        }
    }

    public void FinishPlacingRoad()
    {
        /*placementMode = false;
        placementManager.AddtemporaryStructuresToStructureDictionary();
        if (temporaryPlacementPositions.Count > 0)
        {
            //AudioPlayer.instance.PlayPlacementSound();
        }
        temporaryPlacementPositions.Clear();
        startPosition = Vector2Int.zero;

        placeSound.Play();*/

        //placementMode = false;
        //placementManager.AddtemporaryStructuresToStructureDictionary();
        //if (temporaryPlacementPositions.Count > 0)
        //{
        //    //AudioPlayer.instance.PlayPlacementSound();
        //}
        //temporaryPlacementPositions.Clear();
        //startPosition = Vector2Int.zero;

        //Debug.Log("Road placed " + placementManager.placementGrid.SetRoad(temporaryRoadPositions));

        placementManager.placementGrid.FinalizeGrid();
        temporaryRoadPositions.Clear();
        temporaryRoadCount = 0;
        previousRoadMinus = 0;
    }

    public void ClearTemporaryRoad()
    {
        temporaryRoadPositions.Clear();
    }

    public void RemoveRoad(Vector2Int position)
    {

        /*if (placementManager.CheckIfPositionInBound(position) == false)
            return;
        bool result = false;
        if (trafficLightManager != null)
            result |= trafficLightManager.RequestRemovingTrafficLight(position);
        if (erpManager != null)
            result |= erpManager.RequestRemovingERP(position);
        
        if (result == true)
            return;
        if (placementManager.CheckIfPositionIsFree(position) == false)
        {
            if (placementManager.CheckIfPositionIsOfType(position, CellType.Road))
            {
                //temporaryPlacementPositions.Clear();
                //roadPositionsToRecheck.Clear();
                placementManager.RemoveCurrentGrid(position);
                temporaryPlacementPositions.Add(position);
                //placementMode = false;
                removeSound.Play();
            }
        }

        FixRoadPrefabs();*/

        if (placementManager.CheckIfPositionInBound(position) == false)
            return;
        //
        bool result = false;
        if (trafficLightManager != null)
            result |= trafficLightManager.RequestRemovingTrafficLight(position);
        if (erpManager != null)
            result |= erpManager.RequestRemovingERP(position);
        //Debug.Log(result + " result");
        if (result == true)
            return;

        //if (placementManager.placementGrid.UnsetRoad(position))
        //{
        //    roadCount++;
        //    removeSound.Play();
        //}
        List<Vector2Int> roadRemoved = new List<Vector2Int>();
        int roadInc = placementManager.placementGrid.UnsetRoad(position, ref roadRemoved);
        //Debug.Log("Road removed " + roadInc);
        foreach (var pos in roadRemoved)
        {
            if (trafficLightManager != null)
                trafficLightManager.RequestRemovingTrafficLight(pos);
            if (erpManager != null)
                erpManager.RequestRemovingERP(pos);
        }


        if (roadInc > 0)
        {
            //roadCount += roadInc;
            removeSound.Play();

            taxRoadCount -= roadInc;

            for (int i = 0; i < roadInc; i++)
            {
                moneySystem.SellRoad();
            }
            
        }
        //if (result == true)
        //    return;
        //if (placementManager.CheckIfPositionIsFree(position) == false)
        //{
        //    if (placementManager.CheckIfPositionIsOfType(position, CellType.Road))
        //    {
        //        //placementManager.RemoveCurrentGrid(position);
        //        //temporaryPlacementPositions.Add(position);
        //
        //        removeSound.Play();
        //    }
        //}
        //
        //FixRoadPrefabs();
    }

    public void FinishRemovingRoad()
    {
        //Debug.Log("Something");
        /*placementMode = false;
        placementManager.AddtemporaryStructuresToStructureDictionary();
        temporaryPlacementPositions.Clear();

        removeSound.Play();*/

        //placementMode = false;

        //removeSound.Play();
    }

    //private void FixRoadPrefabs()
    //{
    //    foreach (var temporaryPosition in temporaryPlacementPositions)
    //    {
    //        roadFixer.FixRoadAtPosition(placementManager, temporaryPosition);
    //        var neighbours = placementManager.GetNeighboursOfTypeFor(temporaryPosition, CellType.Road);
    //        foreach (var roadposition in neighbours)
    //        {
    //            if (roadPositionsToRecheck.Contains(roadposition) == false)
    //            {
    //                roadPositionsToRecheck.Add(roadposition);
    //                Debug.Log(roadposition);
    //            }
    //        }
    //    }
    //    foreach (var positionToFix in roadPositionsToRecheck)
    //    {
    //        roadFixer.FixRoadAtPosition(placementManager, positionToFix);
    //    }
    //}

    public void PlaceTrafficLight(Vector2Int position)
    {
        if (!placementManager.CheckIfPositionInBound(position)) return;

        //if (placementManager.CheckIfPositionIsOfType(position, CellType.Road))
        if (placementManager.CheckIfPositionIsRoad(position))
            trafficLightManager.RequestPlacingTrafficLight(position);
    }

    public void PlaceERP(Vector2Int position)
    {
        if (!placementManager.CheckIfPositionInBound(position)) return;

        if (placementManager.CheckIfPositionIsRoad(position))
            erpManager.RequestPlacingERP(position);

    }
    
    public void RemoveCarClick(Vector2Int position)
    {
        removeCarBool = true;
        removeCarTimer = 0f;

        //removeCarTransform.position = position;
        Enable<Collider>(removeCarCollider);

        MoneySystem.RemoveCarMoney();
    }

    public void RemoveCarHover(Vector2Int position)
    {
        GameManager.smallHoverBox.position = position;
        if (!removeCarBool && placementManager.CheckIfPositionInBound(position))
            removeCarTransform.position = position;
    }

}