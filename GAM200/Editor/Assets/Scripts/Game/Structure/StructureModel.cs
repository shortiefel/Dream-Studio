using System.Collections;
using System.Collections.Generic;
using System;

struct DestToHouseSet
{
    public Vector2Int startPos;
    public Vector2Int endPos;
    public BuildingType bt;

    public DestToHouseSet(Vector2Int _startPos, Vector2Int _endPos, BuildingType _bt)
    {
        startPos = _startPos;
        endPos = _endPos;
        bt = _bt;
    }
}
public class StructureModel : MonoBehaviour, INeedingRoad
{
    //float yHeight = 0;
    //private Transform transform;
    
    //Notification notification;
    //CarSpawner carSpawner;
    public Vector2Int RoadPosition { get; set; }

    GameState gameState;

    //ReturnCar returnCar;

    //Animation animation;
    //StructureModel structureModel;

    //private Prefab notifiPrefab;
    //private GameObject notifiSymbol;
    //private AudioSource notificationSound;
    //private AudioSource destroySound;

    AIDirector aiDirector;
    //bool spawnBool;

    Light light;

    public BuildingType buildingType;

    //If true means its waiting for day
    bool waitForDayChange = false;
    bool nightStatus;

    //private float pathTimer;

    Queue<DestToHouseSet> destToHouseQueue;


    DestToHouseSet toberemoved;

    int carCounter = 0;
    float carSpawnTime;
    float carSpawnTimeMax;
    public override void Start()
    {
        gameState = GameObject.Find("GameManager").GetComponent<GameState>();

        light = GetComponent<Light>();
        if (light != null)
        {

            if (gameState.GetNight())
            {
                waitForDayChange = true;
            }
            else
            {
                waitForDayChange = false;
                Disable<Light>(light);
            }
        }


        destToHouseQueue = new Queue<DestToHouseSet>();

        carSpawnTime = 0f;
        carSpawnTimeMax = 0.2f;
        //returnCar = GetComponent<ReturnCar>();

        //structureModel = GetComponent<StructureModel>();

        //notification = GetComponent<Notification>();
        //carSpawner = GetComponent<CarSpawner>();
        //animation = GetComponent<Animation>();
        //spawnBool = false;
        //
        //if (notification != null)
        //{
        //    //notifiPrefab = ;
        //    Vector2 center = transform.localPosition;
        //    
        //    //Debug.Log("come in here --------------------------------------------------------------------------------");
        //    notifiSymbol = Instantiate(new Prefab("Notification"), new Vector3(center.x, center.y + 1.5f, 0f), 4);
        //    //notification.SetAnimation(ref notifiSymbol.GetComponent<Animation>());
        //    animation = notifiSymbol.GetComponent<Animation>();
        //    //animation.Play("Appear");
        //    //notification.SetAnimation("Appear");
        //    spawnBool = true;
        //    SetToSpawn();
        //    notificationSound = GetComponent<AudioSource>();
        //    destroySound = notifiSymbol.GetComponent<AudioSource>();
        //
        //    //Have to be texture names without the extension
        //    switch (texure.RetrieveTexture())
        //    {
        //        case "Office":
        //            buildingType = BuildingType.Office;
        //            break;
        //
        //        case "Hospital":
        //            buildingType = BuildingType.Hospital;
        //            break;
        //        
        //        case "Park":
        //            buildingType = BuildingType.Park;
        //            break;
        //
        //        case "ShoppingMall":
        //            buildingType = BuildingType.Mall;
        //            break;
        //    }
        //}
        //
        //else
        //{
        //    buildingType = BuildingType.House;
        //}

        aiDirector = GameObject.Find("AIDirector").GetComponent<AIDirector>();

        //pathTimer = 0f;

        Texture texure = GetComponent<Texture>();
        switch (texure.RetrieveTexture())
        {
            case "Office":
                buildingType = BuildingType.Office;
                break;

            case "Hospital":
                buildingType = BuildingType.Hospital;
                break;

            case "Park":
                buildingType = BuildingType.Park;
                break;

            case "ShoppingMall":
                buildingType = BuildingType.Mall;
                break;
        }
    }

    public override void Update()
    {
        if (light != null)
        {
            nightStatus = gameState.GetNight();
            if (!waitForDayChange && nightStatus)
            {
                //Debug.Log("Change to turn on light");
                Enable<Light>(light);
                waitForDayChange = true;
            }

            else if (waitForDayChange && !nightStatus)
            {
                //Debug.Log("Change to turn off light");
                Disable<Light>(light);
                waitForDayChange = false;
            }
        }

        carSpawnTime += Time.deltaTime;
            Debug.Log("Current " + entityId + " " + carCounter);
        if (destToHouseQueue.Count != 0 && carSpawnTime > carSpawnTimeMax && carCounter == 0)
        {
            carSpawnTime = 0f;
            DestToHouseSet dts = destToHouseQueue.Dequeue();
            toberemoved = new DestToHouseSet(dts.startPos, dts.endPos, dts.bt); //-----------------------------------
            aiDirector.SpawnCar(dts.startPos, 0, dts.bt, dts.endPos, RouteType.DestToHouse);
            //++carCounter;
        }

        //-----------------------------------------------------
        if (GetComponent<Light>() != null)
        {
            if (Input.GetKeyDown(KeyCode.B))
            {
                destToHouseQueue.Enqueue(new DestToHouseSet(toberemoved.startPos, toberemoved.endPos, toberemoved.bt));
                //aiDirector.SpawnCar(toberemoved.startPos, 0, toberemoved.bt, toberemoved.endPos, RouteType.DestToHouse);
            }
        }
        //-----------------------------------------------------

        //if (notification != null)
        //{
        //    if (!notification.NotificationUpdate())
        //    {
        //        //gameState.shouldEnd = true;
        //        //gameState.SetLoseHouse(transform.position);
        //
        //        //Lose points instead of lose game
        //        if (gameState != null)
        //            gameState.MissedDestinationTime(buildingType);
        //    }
        //
        //    if (notification.AppearCheck())
        //    {
        //        animation.Play("Stay");
        //    }
        //    if (notification.TickerAppearCheck())
        //    {
        //        animation.Play("TickingAppear");
        //    }
        //    if (notification.DestroyCheck())
        //    {
        //        Console.Write("Enter normal destroy");
        //        Disable<Transform>(notifiSymbol.transform);
        //        destroySound.Play();
        //        notification.alreadyShowing = false;
        //       
        //    }
        //    if(notification.TickerDestroyCheck())
        //    {
        //        Console.Write("Enter timer destroy");
        //        Disable<Transform>(notifiSymbol.transform);
        //        notification.alreadyShowing = false;
        //       
        //    }
        //    if(notification.expirebool == true)
        //    {
        //        Debug.Log("destory Timer");
        //        Disable<Transform>(notifiSymbol.transform);
        //        notification.expirebool = false;
        //    }
        //    if (notification.timerShow == true)
        //    {
        //        SetToSpawn2();
        //    }
        //    if (notification.shouldShow == true)
        //    {
        //        SetToSpawn();
        //        notificationSound.Play();
        //        notification.shouldShow = false;
        //        notification.ResetTimer();
        //        Enable<Transform>(notifiSymbol.transform);
        //        
        //    }
        //
        //    pathTimer += Time.deltaTime;
        //    if (pathTimer >= aiDirector.pathTimerMax)
        //    {
        //        aiDirector.GetNewPathList(new Vector2Int(transform.position), entityId, true);
        //        pathTimer = 0f;
        //    }
        //
        //    //if (spawnBool && aiDirector != null)
        //    //    spawnBool = !(aiDirector.SpawnToDestination(structureModel));
        //    if (Input.GetKeyDown(KeyCode.C) && Input.GetKey(KeyCode.Shift))
        //        aiDirector.SpawnToDestination(structureModel);
        //}
    }


    public override void OnTriggerEnter(uint entId)
    {
        ++carCounter;
    }

    public override void OnTriggerExit(uint entId)
    {
        --carCounter;
    }

    /*public void CreateModel(Prefab model)
    {
        //var structure = Instantiate(model, transform);
        //yHeight = structure.transform.position.y;
    }*/

    //public void SetSpawnBool(bool state)
    //{
    //    spawnBool = state;
    //}

    //public StructureModel SwapModel(GameObject model, float rotation)
    //{
    //    /*foreach (Transform child in transform)
    //    {
    //        Destroy(child.gameObject);
    //    }*/
    //
    //    //texure.ChangeTexture(model.name);
    //    //transform.angle = rotation;
    //    Debug.Log("SwapModel not in use");
    //    //var structure = Instantiate(model, new Vector3(transform.position, 0f), 1);
    //    ////structure.transform.position = new Vector2(0, 0);
    //    //structure.transform.angle = rotation;
    //    //
    //    //aiDirector.placementManager.placementGrid.SetCellType(new Vector2Int(transform.position), CellType.Road, structure.entityId);
    //    //
    //    //Destroy(gameObject);
    //
    //    //texure.color = new Color(0, 1, 0, 0.5f);
    //    //texure.ChangeTexture(model.name);
    //    //transform.angle = rotation;
    //    //Disable<Transform>(transform);
    //
    //    return GetComponent<StructureModel>();
    //}

    /*
     * Notify house that a car has reached it
    */
    public void Notify(Vector2Int spawnPoint, Vector2Int nextDest)
    {
        gameState.ReachedDestination(buildingType);

        //Debug.Log("Try spawn to house ------ " + spawnPoint + " to " + nextDest);
        //aiDirector.SpawnCar(spawnPoint, 0, buildingType, nextDest, RouteType.DestToHouse);

        destToHouseQueue.Enqueue(new DestToHouseSet(spawnPoint, nextDest, buildingType));

        //if (returnCar != null)
        //{
        //
        //}
        //if (notification != null)
        //{
        //    //Disable<Transform>(notifiSymbol.transform);
        //    //if (notification != null)
        //    if (notification.alreadyShowing)
        //    {
        //        if (notification.timerShow)
        //        {
        //            Console.WriteLine("Timer Destroy");
        //            animation.Play("TickingClose");
        //            notification.SetAnimation("TickingClose");
        //            notification.timerShow = false;
        //        }
        //        else
        //        {
        //            animation.Play("Destroy");
        //            notification.SetAnimation("Destroy");
        //        }
        //        
        //    }
        //    //notification.transform.
        //    if (gameState != null)
        //        gameState.ReachedDestination(buildingType);
        //    notification.ResetTimer();
        //}
    }

    internal void DeleteModel()
    {
        Destroy(entityId);
    }

    //void SetToSpawn()
    //{
    //    animation.Play("Appear");
    //    notification.SetAnimation("Appear");
    //    spawnBool = true;
    //}
    //
    //void SetToSpawn2()
    //{
    //    animation.Play("TickingAppear");
    //    notification.SetAnimation("TickingAppear");
    //    //spawnBool = true;
    //}

    //internal List<Marker> GetCarMarkers()
    //{
    //    var componentMultiple = GetComponent<RoadHelperMultiple>();
    //
    //    var componentStraight = GetComponent<RoadHelperStraight>();
    //
    //    var component = GetComponent<RoadHelper>();
    //
    //    var componentCurve = GetComponent<RoadHelperCurve>();
    //
    //    var component4Way = GetComponent<RoadHelperFourWay>();
    //
    //    List<Marker> sortMarker = null;
    //
    //    if (component != null)
    //    {
    //        //Console.WriteLine("roadhelper NULL COMPONENT");
    //        sortMarker = component.GetAllCarMarkers();
    //    }
    //
    //    if (componentMultiple != null)
    //    {
    //        //Console.WriteLine("componentMultiple NULL COMPONENT");
    //        sortMarker = componentMultiple.GetAllCarMarkers();
    //    }
    //
    //    if (componentStraight != null)
    //    {
    //        //Console.WriteLine("componentStraight NULL COMPONENT");
    //        sortMarker = componentStraight.GetAllCarMarkers();
    //    }
    //
    //    if (componentCurve != null)
    //    {
    //        //Console.WriteLine("componentCurve NULL COMPONENT");
    //        sortMarker = componentCurve.GetAllCarMarkers();
    //    }
    //
    //    if (component4Way != null)
    //    {
    //        //Console.WriteLine("component4Way NULL COMPONENT");
    //        sortMarker = component4Way.GetAllCarMarkers();
    //    }
    //
    //    //Console.WriteLine("structuremodel marker" + component);
    //    return sortMarker;
    //}
    //
    //public Vector2 GetNearestCarMarkerTo(Vector2 position)
    //{
    //    var componentMultiple = GetComponent<RoadHelperMultiple>();
    //
    //    var componentStraight = GetComponent<RoadHelperStraight>();
    //
    //    var component = GetComponent<RoadHelper>();
    //
    //    var componentCurve = GetComponent<RoadHelperCurve>();
    //
    //    var component4Way = GetComponent<RoadHelperFourWay>();
    //
    //    Vector2 sortMarker = Vector2.zero;
    //
    //    if (component != null)
    //    {
    //        //Console.WriteLine("roadhelper NULL COMPONENT");
    //        sortMarker = component.GetClosestCarMarkerPosition(position);
    //    }
    //
    //    if (componentMultiple != null)
    //    {
    //        //Console.WriteLine("componentMultiple NULL COMPONENT");
    //        sortMarker = componentMultiple.GetClosestCarMarkerPosition(position);
    //    }
    //
    //    if (componentStraight != null)
    //    {
    //        //Console.WriteLine("componentStraight NULL COMPONENT");
    //        sortMarker = componentStraight.GetClosestCarMarkerPosition(position);
    //    }
    //
    //    if (componentCurve != null)
    //    {
    //        //Console.WriteLine("componentCurve NULL COMPONENT");
    //        sortMarker = componentCurve.GetClosestCarMarkerPosition(position);
    //    }
    //
    //    if (component4Way != null)
    //    {
    //        //Console.WriteLine("component4Way NULL COMPONENT");
    //        sortMarker = component4Way.GetClosestCarMarkerPosition(position);
    //    }
    //
    //    //Console.WriteLine("structuremodel marker" + component);
    //    return sortMarker;
    //}
    //
    //public Marker GetCarSpawnMarker(Vector2Int nextPathPosition)
    //{
    //    var componentMultiple = GetComponent<RoadHelperMultiple>();
    //
    //    var componentStraight = GetComponent<RoadHelperStraight>();
    //
    //    var component = GetComponent<RoadHelper>();
    //
    //    var componentCurve = GetComponent<RoadHelperCurve>();
    //
    //    var component4Way = GetComponent<RoadHelperFourWay>();
    //
    //    Marker sortMarker = null;
    //
    //    if (component != null)
    //    {
    //        //Console.WriteLine("roadhelper NULL COMPONENT");
    //        sortMarker = component.GetPositionForCarToSpawn(nextPathPosition);
    //    }
    //
    //    if (componentMultiple != null)
    //    {
    //        //Console.WriteLine("componentMultiple NULL COMPONENT");
    //        sortMarker = componentMultiple.GetPositionForCarToSpawn(nextPathPosition);
    //    }
    //
    //    if (componentStraight != null)
    //    {
    //        //Console.WriteLine("componentStraight NULL COMPONENT");
    //        sortMarker = componentStraight.GetPositionForCarToSpawn(nextPathPosition);
    //    }
    //
    //    if (componentCurve != null)
    //    {
    //        //Console.WriteLine("componentCurve NULL COMPONENT");
    //        sortMarker = componentCurve.GetPositionForCarToSpawn(nextPathPosition);
    //    }
    //
    //    if (component4Way != null)
    //    {
    //        //Console.WriteLine("component4Way NULL COMPONENT");
    //        sortMarker = component4Way.GetPositionForCarToSpawn(nextPathPosition);
    //    }
    //
    //    //Console.WriteLine("structuremodel marker" + component);
    //    return sortMarker;
    //}
    //
    //public Marker GetCarEndMarker(Vector2Int prevPathPosition)
    //{
    //    Console.WriteLine("Endmarker");
    //
    //    var componentMultiple = GetComponent<RoadHelperMultiple>();
    //
    //    var componentStraight = GetComponent<RoadHelperStraight>();
    //
    //    var component = GetComponent<RoadHelper>();
    //
    //    var componentCurve = GetComponent<RoadHelperCurve>();
    //
    //    var component4Way = GetComponent<RoadHelperFourWay>();
    //
    //    Marker sortMarker = null;
    //
    //    if (component != null)
    //    {
    //        //Console.WriteLine("roadhelper NULL COMPONENT");
    //        sortMarker = component.GetPositionForCarToEnd(prevPathPosition);
    //    }
    //
    //    if (componentMultiple != null)
    //    {
    //        //Console.WriteLine("componentMultiple NULL COMPONENT");
    //        sortMarker = componentMultiple.GetPositionForCarToEnd(prevPathPosition);
    //    }
    //
    //    if (componentStraight != null)
    //    {
    //        //Console.WriteLine("componentStraight NULL COMPONENT");
    //        sortMarker = componentStraight.GetPositionForCarToEnd(prevPathPosition);
    //    }
    //
    //    if (componentCurve != null)
    //    {
    //        //Console.WriteLine("componentCurve NULL COMPONENT");
    //        sortMarker = componentCurve.GetPositionForCarToEnd(prevPathPosition);
    //    }
    //
    //    if (component4Way != null)
    //    {
    //        //Console.WriteLine("component4Way NULL COMPONENT");
    //        sortMarker = component4Way.GetPositionForCarToEnd(prevPathPosition);
    //    }
    //
    //    //Console.WriteLine("structuremodel marker" + component);
    //    return sortMarker;
    //}

}