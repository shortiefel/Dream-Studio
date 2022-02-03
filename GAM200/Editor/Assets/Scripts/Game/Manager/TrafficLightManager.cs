using System.Collections.Generic;

public class TrafficLightManager : MonoBehaviour
{

    private Dictionary<Vector2, uint> trafficLights;

    GameObject temTL; //TO Remove
    Camera mainCamera; //TO Remove

    bool toDraw; //To Remove


    public override void Start()
    {
        trafficLights = new Dictionary<Vector2, uint>();

        temTL = new GameObject(new Prefab("TrafficLight")); //To Remove
        mainCamera = GameObject.Find("Camera").GetComponent<Camera>(); //To Remove

        toDraw = false; //To Remove
    }

    public override void Update()
    {
        //To Remove ------------------------------------------------------
        if (toDraw && Input.GetMouseButtonDown(MouseCode.Left))
        {
            Vector3Int mousePos = Vector3Int.RoundToInt(mainCamera.ScreenToWorldPoint(Input.GetMousePosition()));
            
            Instantiate(temTL, new Vector3(mousePos.x, mousePos.y, 0f));
            Debug.Log("Traffic light placement");

            foreach (var i in trafficLights) Debug.Log(" Traffic: " + i);
        }
        if (Input.GetKeyDown(KeyCode.D))
        {
            toDraw = !toDraw;
        }

        if (Input.GetKeyDown(KeyCode.A))
        {
            Time.timeScale = 1f;
        }
        if (Input.GetKeyDown(KeyCode.S))
        {
            Time.timeScale = 3f;
        }
        //To Remove ------------------------------------------------------
    }

    public void RegisterTrafficLight(Vector2Int pos, uint id)
    {
        if (!trafficLights.ContainsKey(pos))
            trafficLights.Add(pos, id);
    }

    public void RemoveTrafficLight(Vector2Int pos)
    {
        trafficLights.Remove(pos);
    }

    public bool GetTrafficLightState(Vector2 tlPos, float _carAngle)
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


        bool cState = GetComponentWithID<TrafficLight>(trafficLights[tlPos]).state;
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
            if (trafficLights.ContainsKey(pos)) tlPos.Add(trafficLights[pos]);
        }

        return tlPos;
    }

    public bool IsTrafficLight(Vector2 posToCheck)
    {
        if (trafficLights.ContainsKey(posToCheck)) return true;
        return false;
    }
}


