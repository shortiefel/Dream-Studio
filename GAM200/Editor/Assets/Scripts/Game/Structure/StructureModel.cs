using System.Collections;
using System.Collections.Generic;
using System;

public class StructureModel : MonoBehaviour, INeedingRoad
{
    //float yHeight = 0;
    //private Transform transform;
    Texture texure;
    Notification notification;
    //CarSpawner carSpawner;
    public Vector2Int RoadPosition { get; set; }

    GameState gameState;
    //AIDirector aiDirector;

    Animation animation;
    StructureModel structureModel;

    //private Prefab notifiPrefab;
    private GameObject notifiSymbol;
    private AudioSource notificationSound;
    private AudioSource destroySound;

    AIDirector aiDirector;
    //bool spawnBool;

    public BuildingType buildingType;

    public override void Start()
    {
        gameState = GameObject.Find("GameManager").GetComponent<GameState>();
        //aiDirector = GameObject.Find("AIDirector").GetComponent<AIDirector>();
        structureModel = GetComponent<StructureModel>();

        transform = GetComponent<Transform>();
        texure = GetComponent<Texture>();
        notification = GetComponent<Notification>();
        //carSpawner = GetComponent<CarSpawner>();
        //animation = GetComponent<Animation>();
        //spawnBool = false;

        if (notification != null)
        {
            //notifiPrefab = ;
            Vector2 center = transform.localPosition;
            
            //Debug.Log("come in here --------------------------------------------------------------------------------");
            notifiSymbol = Instantiate(new Prefab("Notification"), new Vector3(center.x, center.y + 0.7f, 0f), 4);
            //notification.SetAnimation(ref notifiSymbol.GetComponent<Animation>());
            animation = notifiSymbol.GetComponent<Animation>();
            //animation.Play("Appear");
            //notification.SetAnimation("Appear");
            //spawnBool = true;
            SetToSpawn();
            notificationSound = GetComponent<AudioSource>();
            destroySound = notifiSymbol.GetComponent<AudioSource>();
            //aiDirector.SpawnACar();

            //Have to be texture names without the extension
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

        else
        {
            buildingType = BuildingType.House;
        }

        //Debug.Log("This is " + buildingType + " -------------------------");

        aiDirector = GameObject.Find("AIDirector").GetComponent<AIDirector>();
    }

    public override void Update()
    {
        
        if (notification != null)
        {
            if (!notification.NotificationUpdate())
            {
                gameState.shouldEnd = true;
                gameState.SetLoseHouse(transform.position);
            }

            if (notification.AppearCheck())
            {
                animation.Play("Stay");
            }

            if (notification.DestroyCheck())
            {
                Disable<Transform>(notifiSymbol.transform);
                destroySound.Play();
                notification.alreadyShowing = false;
                animation.Play("Stay");
            }
            if(notification.TickerAppearCheck())
            {
                animation.Play("TickingAppear");
            }
            if(notification.TickerDestroyCheck())
            {
                Disable<Transform>(notifiSymbol.transform);
                notification.alreadyShowing = false;
                animation.Play("TickingClose");
            }
            if (notification.shouldShow == true)
            {
                //animation.Play("Appear");
                //notification.SetAnimation("Appear");
                //spawnBool = true;
                if(notification.timerShow == true)
                {
                    SetToSpawn2();
                }
                else
                {
                    SetToSpawn();
                }
                notificationSound.Play();
                notification.shouldShow = false;
                notification.ResetTimer();
                Enable<Transform>(notifiSymbol.transform);
                
            }

            //if (spawnBool && aiDirector != null)
            //    spawnBool = !(aiDirector.SpawnToDestination(structureModel));
            if (Input.GetKeyDown(KeyCode.C))
                aiDirector.SpawnToDestination(structureModel);
        }
    }

    /*public void CreateModel(Prefab model)
    {
        //var structure = Instantiate(model, transform);
        //yHeight = structure.transform.position.y;
    }*/

    public StructureModel SwapModel(GameObject model, float rotation)
    {
        /*foreach (Transform child in transform)
        {
            Destroy(child.gameObject);
        }*/

        //texure.ChangeTexture(model.name);
        //transform.angle = rotation;
        Debug.Log("SwapModel not in use");
        //var structure = Instantiate(model, new Vector3(transform.position, 0f), 1);
        ////structure.transform.position = new Vector2(0, 0);
        //structure.transform.angle = rotation;
        //
        //aiDirector.placementManager.placementGrid.SetCellType(new Vector2Int(transform.position), CellType.Road, structure.entityId);
        //
        //Destroy(gameObject);

        //texure.color = new Color(0, 1, 0, 0.5f);
        //texure.ChangeTexture(model.name);
        //transform.angle = rotation;
        //Disable<Transform>(transform);

        return GetComponent<StructureModel>();
    }

    /*
     * Notify house that a car has reached it
    */
    public void Notify()
    {
        if (notification != null)
        {
            //Disable<Transform>(notifiSymbol.transform);
            //if (notification != null)
            if (notification.alreadyShowing)
            {
                animation.Play("Destroy");
                notification.SetAnimation("Destroy");
            }
            //notification.transform.
            gameState.IncrementScore();
            notification.ResetTimer();
        }
    }

    internal void DeleteModel()
    {
        Destroy(entityId);
    }

    void SetToSpawn()
    {
        animation.Play("Appear");
        notification.SetAnimation("Appear");
        //spawnBool = true;
    }

    void SetToSpawn2()
    {
        animation.Play("Ticking");
        notification.SetAnimation("Ticking");
        //spawnBool = true;
    }

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