using System.Collections.Generic;

public class TrafficLightManager : MonoBehaviour
{

    private Dictionary<Vector2Int, uint> trafficLights;
    private ERPManager erpManager;
    MoneySystem moneySystem;
    GameObject trafficLightGO;
    //Camera mainCamera; //TO Remove

    //bool toDraw; //To Remove

    public int tlCount;

    Transform TLInfoText;
    Transform TLInfo;

    public override void Start()
    {
        trafficLights = new Dictionary<Vector2Int, uint>();

        trafficLightGO = new GameObject(new Prefab("TrafficLight"));
        //mainCamera = GameObject.Find("Camera").GetComponent<Camera>(); //To Remove
        moneySystem = GameObject.Find("MoneyText").GetComponent<MoneySystem>();
        erpManager = GameObject.Find("ERPManager").GetComponent<ERPManager>();

        //toDraw = false; //To Remove

        tlCount = 1;

        TLInfoText = GameObject.Find("TLPopInfoText").GetComponent<Transform>();
        TLInfo = GameObject.Find("TLPopInfo").GetComponent<Transform>();

        Disable<Transform>(TLInfoText);
        Disable<Transform>(TLInfo);
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
            trafficLights.Add(pos, id);
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
        bool lrState = false;
        if ((45f < _carAngle && _carAngle < 135f) || (-315f < _carAngle && _carAngle < -225f) ||
            (225f < _carAngle && _carAngle < 315f) || (-135f < _carAngle && _carAngle < -45f)) lrState = true;

        //Vector2Int carPos = new Vector2Int(_carPos);

        if (!trafficLights.ContainsKey(tlPos)) return true;


        bool cState = GetComponent<TrafficLight>(trafficLights[tlPos]).state;
        //cState == true means allows horizontal movement
        //cState == false means allow vertical movement
        //if lrState == true means moving left right (horizontally) and false means moving up down (vertically)
        //It means that when they are the same then they are allowed to move
        if (lrState == cState) return true;
        return false;
    }

    public List<uint> GetTrafficLightIndex(List<Vector2> toCheck)
    {
        List<uint> tlPos = new List<uint>();

        foreach (Vector2 pos in toCheck)
        {
            if (trafficLights.ContainsKey(new Vector2Int(pos)))
            {
                if (!tlPos.Exists(x => x == trafficLights[new Vector2Int(pos)]))
                    tlPos.Add(trafficLights[new Vector2Int(pos)]);
            }
            
        }

        return tlPos;
    }

    public bool IsTrafficLight(Vector2Int posToCheck)
    {
        if (trafficLights.ContainsKey(posToCheck)) return true;
        return false;
    }

    public bool RequestPlacingTrafficLight(Vector2Int position)
    {
        Disable<Transform>(TLInfoText);
        Disable<Transform>(TLInfo);

        if (tlCount <= 0)
        {
            Enable<Transform>(TLInfoText);
            Enable<Transform>(TLInfo);
            return false;
        }

        if (trafficLights.ContainsKey(position))
            return false;
        if (erpManager.IsERP(position))
            return false;

        --tlCount;
        Instantiate(trafficLightGO, new Vector3(position.x, position.y, 0f));
        return true;
    }

    public bool RequestRemovingTrafficLight(Vector2Int position)
    {
        Disable<Transform>(TLInfoText);
        Disable<Transform>(TLInfo);

        if (!trafficLights.ContainsKey(position))
            return false;

        ++tlCount;
        moneySystem.SellTL();
        Destroy(trafficLights[position]);
        trafficLights.Remove(position);
        return true;

    }
}


