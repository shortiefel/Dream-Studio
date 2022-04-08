using System.Collections.Generic;

public class TrafficLightManager : MonoBehaviour
{

    private Dictionary<Vector2Int, TrafficLight> trafficLights;
    private ERPManager erpManager;
    MoneySystem moneySystem;
    GameObject trafficLightGO;
    //Camera mainCamera; //TO Remove

    //bool toDraw; //To Remove


    Transform TLInfoText;
    Transform TLInfo;

    public override void Start()
    {
        trafficLights = new Dictionary<Vector2Int, TrafficLight>();

        trafficLightGO = new GameObject(new Prefab("TrafficLight"));
        //mainCamera = GameObject.Find("Camera").GetComponent<Camera>(); //To Remove
        moneySystem = GameObject.Find("MoneyText").GetComponent<MoneySystem>();
        erpManager = GameObject.Find("ERPManager").GetComponent<ERPManager>();

        //toDraw = false; //To Remove


        TLInfoText = GameObject.Find("TLPopInfoText").GetComponent<Transform>();
        TLInfo = GameObject.Find("TLPopInfo").GetComponent<Transform>();

        Disable<Transform>(TLInfoText);
        Disable<Transform>(TLInfo);
    }

    public int trafficlightTaxCount()
    {
        return trafficLights.Count;
    }


    //public override void Update()
    //{
    //    //To Remove ------------------------------------------------------
    //    if (toDraw && Input.GetMouseButtonDown(MouseCode.Left))
    //    {
    //        Vector3Int mousePos = Vector3Int.RoundToInt(mainCamera.ScreenToWorldPoint(Input.GetMousePosition()));
    //        
    //        Instantiate(trafficLightGO, new Vector3(mousePos.x, mousePos.y, 0f));
    //        Debug.Log("Traffic light placement");
    //    
    //        //foreach (var i in trafficLights) Debug.Log(" Traffic: " + i);
    //    }
    //    if (Input.GetKeyDown(KeyCode.D))
    //    {
    //        toDraw = !toDraw;
    //    }
    //    
    //    if (Input.GetKeyDown(KeyCode.A))
    //    {
    //        Time.timeScale = 1f;
    //    }
    //    if (Input.GetKeyDown(KeyCode.S))
    //    {
    //        Time.timeScale = 3f;
    //    }
    //    //To Remove ------------------------------------------------------
    //}

    public void RegisterTrafficLight(Vector2Int pos, uint id)
    {
        if (!trafficLights.ContainsKey(pos))
        {
            //TrafficLight tl = new TrafficLight();
            //tl.entityId = id;
            //trafficLights.Add(pos, tl);
            trafficLights.Add(pos, GetComponent<TrafficLight>(id));
        }
    }

    //public void RemoveTrafficLight(Vector2Int pos)
    //{
    //    trafficLights.Remove(pos);
    //}

    public bool GetTrafficLightState(Vector2Int tlPos, float _carAngle)
    {
        _carAngle = _carAngle % 360;
        //angle 0/360/-360 - up, 90/-270 - right, -90/270 - left, 180/-180 - down
        //+-45 degree for range
        //if left or right
        DirectionState ds = DirectionState.Horizontal;
        //if (state) ds = DirectionState.HorizontalLeft;

        if ((45f < _carAngle && _carAngle < 135f) || (-315f < _carAngle && _carAngle < -225f) ||
            (225f < _carAngle && _carAngle < 315f) || (-135f < _carAngle && _carAngle < -45f))
        {
            ds = DirectionState.Vertical;
            //if (state) ds = DirectionState.VerticalLeft;
        }
        //Debug.Log(ds + " " + state);
        if (!trafficLights.ContainsKey(tlPos)) return true;

        trafficLights[tlPos].RequestChange(ds);
        DirectionState tem = trafficLights[tlPos].directionState;
        
        return ds == tem;
    }

    public List<uint> GetTrafficLightIndex(List<Vector2> toCheck)
    {
        List<uint> tlPos = new List<uint>();

        foreach (Vector2 pos in toCheck)
        {
            if (trafficLights.ContainsKey(new Vector2Int(pos)))
            {
                if (!tlPos.Exists(x => x == trafficLights[new Vector2Int(pos)].entityId))
                    tlPos.Add(trafficLights[new Vector2Int(pos)].entityId);
            }
            
        }

        return tlPos;
    }
    public bool IsTrafficLight(Vector2Int targetPos, uint entId = 0)
    {
        if (entId == 0) return trafficLights.ContainsKey(targetPos);
        if (!trafficLights.ContainsKey(targetPos)) return false;
        return trafficLights[targetPos].entityId == entId;
    }

    public bool RequestPlacingTrafficLight(Vector2Int position)
    {

        if (trafficLights.ContainsKey(position))
            return false;
        if (erpManager.IsERP(position))
            return false;
        if (moneySystem.BuyTrafficLight())
            Instantiate(trafficLightGO, new Vector3(position.x, position.y, 0f), 3);
        return true;
    }

    public bool RequestRemovingTrafficLight(Vector2Int position)
    {
        if (!trafficLights.ContainsKey(position))
            return false;

        moneySystem.SellTL();
        Destroy(trafficLights[position].entityId);
        trafficLights.Remove(position);
        return true;

    }
}


