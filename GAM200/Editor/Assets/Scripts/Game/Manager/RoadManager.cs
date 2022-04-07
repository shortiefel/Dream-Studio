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

    public int roadCount;
    private int previousRoadMinus;

    Transform RoadInfoText;
    Transform RoadInfo;

    float timer;
    bool addToTime;

    Transform removeCarCollider;
    bool removeCarBool;
    float removeCarTimer;

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

        roadCount = 20;
        previousRoadMinus = 0;

        GameObject go3 = GameObject.Find("RoadPopInfoText");
        if (go3 != null)
            RoadInfoText = go3.GetComponent<Transform>();

        GameObject go4 = GameObject.Find("RoadPopInfo");
        if (go4 != null)
            RoadInfo = go4.GetComponent<Transform>();

        Disable<Transform>(RoadInfoText);
        Disable<Transform>(RoadInfo);

        timer = 0f;
        addToTime = false;

        removeCarCollider = GameObject.Find("RemoveCarCollider").GetComponent<Transform>();
        removeCarBool = false;
        removeCarTimer = 0f;
    }

    public override void FixedUpdate()
    {
        if (addToTime == true)
        {
            timer += Time.fixedDeltaTime;

            if (timer > 2f)
            {
                Disable<Transform>(RoadInfoText);
                Disable<Transform>(RoadInfo);

                timer = 0f;
                addToTime = false;
            }
        }

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
        //Debug.Log(temporaryRoadPositions.Count);
        //foreach (var i in temporaryRoadPositions)
        //{
        //    Debug.Log(i);
        //}
        /*//Debug.Log("here");
        if (placementManager.CheckIfPositionInBound(position) == false)
            return;
        if (placementManager.CheckIfPositionIsFree(position) == false)
            return;
        //if (placementMode == false)
        //{
            temporaryPlacementPositions.Clear();
            roadPositionsToRecheck.Clear();

            //placementMode = true;
            startPosition = position;
            Debug.Log(position + " -----------------\n");

            temporaryPlacementPositions.Add(position);
            placementManager.PlaceTemporaryStructure(position, roadFixer.deadEnd, CellType.Road, 1);
            //Console.WriteLine("call function");

        //}
        //else
        //{
        //    //Console.WriteLine("call function2222222222");
        //    placementManager.RemoveAllTemporaryStructures();
        //    temporaryPlacementPositions.Clear();

        //    foreach (var positionsToFix in roadPositionsToRecheck)
        //    {
        //        roadFixer.FixRoadAtPosition(placementManager, positionsToFix);
        //    }

        //    roadPositionsToRecheck.Clear();

        //    temporaryPlacementPositions = placementManager.GetPathBetween(startPosition, position);

        //    foreach (var temporaryPosition in temporaryPlacementPositions)
        //    {
        //        if (placementManager.CheckIfPositionIsFree(temporaryPosition) == false)
        //        {
        //            roadPositionsToRecheck.Add(temporaryPosition);
        //            continue;
        //        }
        //        placementManager.PlaceTemporaryStructure(temporaryPosition, roadFixer.deadEnd, CellType.Road, 1);
        //    }
        //}

        FixRoadPrefabs();*/



        //placementMode = true;
        //startPosition = position;
        //Debug.Log(position + " -----------------\n");

        if (placementManager.CheckIfPositionInBound(position) == false)
            return;
        if (temporaryRoadPositions.Count > 0 && temporaryRoadPositions[temporaryRoadPositions.Count - 1] == position)
            return;
        //Remove last one if current position is the same as the second last position
        //Require at least two road to remove one road
        //else if (temporaryRoadPositions.Count > 1 && temporaryRoadPositions[temporaryRoadPositions.Count - 2] == position)
        //{
        //    //placementManager.placementGrid.UnsetRoad(temporaryRoadPositions[temporaryRoadPositions.Count - 1]);
        //    //Revert grid
        //    placementManager.placementGrid.RevertGrid();
        //    temporaryRoadPositions.RemoveAt(temporaryRoadPositions.Count - 1);
        //    //Debug.Log("Previous " + previousRoadMinus);
        //    //roadCount += previousRoadMinus;
        //
        //
        //    int nTmp = placementManager.placementGrid.SetRoad(temporaryRoadPositions);
        //    roadCount += previousRoadMinus - nTmp;
        //    previousRoadMinus = nTmp;
        //
        //    temporaryRoadCount = temporaryRoadPositions.Count;
        //
        //    taxRoadCount++;
        //
        //    return;
        //}
        //else
        {
            if (temporaryRoadCount >= 20)
            {
                Debug.Log("Max temporary road count reached (RoadManager PlaceRoad)");
                return;
            }
            if (roadCount < 1)
            {
                Enable<Transform>(RoadInfoText);
                Enable<Transform>(RoadInfo);

                addToTime = true;
                return;
            }
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
            //foreach (var i in temporaryRoadPositions) Console.WriteLine(i);
        }

        if (temporaryRoadCount == temporaryRoadPositions.Count) return;
        if(roadCount == 1 && temporaryRoadPositions.Count > 1)
        {
            if (placementManager.placementGrid.IsPosFree(temporaryRoadPositions[0])
                && placementManager.placementGrid.IsPosFree(temporaryRoadPositions[1]))
                return;
        }
        int tmp = placementManager.placementGrid.SetRoad(temporaryRoadPositions);
        Debug.Log("stuff");
        if (tmp > 0) placeSound.Play();

        //roadCount -= tmp;
        taxRoadCount += tmp;
        //placementManager.placementGrid.SetRoad(temporaryRoadPositions);
        //Debug.Log("tmp " + tmp);
        //previousRoadMinus += tmp;
        //roadCount -= tmp;

        temporaryRoadCount = temporaryRoadPositions.Count;

        //taxRoadCount++;

        //placementManager.PlaceTemporaryStructure(position, roadFixer.deadEnd, CellType.Road, 1);

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
                Disable<Transform>(removeCarCollider);
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
        //bool result = false;
        //if (trafficLightManager != null)
        //    result |= trafficLightManager.RequestRemovingTrafficLight(position);
        //if (erpManager != null)
        //    result |= erpManager.RequestRemovingERP(position);

        //if (result == true)
        //    return;

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
            roadCount += roadInc;
            removeSound.Play();

            taxRoadCount -= roadInc;
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
    
    public void RemoveCarGrid(Vector2Int position)
    {
        removeCarBool = true;
        removeCarTimer = 0f;

        removeCarCollider.position = position;
        Enable<Transform>(removeCarCollider);

        MoneySystem.RemoveCarMoney();
    }

}