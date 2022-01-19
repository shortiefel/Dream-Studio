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

    public void RegisterTrafficLight(Vector2 pos, uint id)
    {
        if (!trafficLights.ContainsKey(pos))
            trafficLights.Add(pos, id);
    }

    public void RemoveTrafficLight(Vector2 pos)
    {
        trafficLights.Remove(pos);
    }

    public bool GetTrafficLightState(Vector2Int tlPos, Vector2 _carPos)
    {
        Vector2Int carPos = new Vector2Int(_carPos);

        if (!trafficLights.ContainsKey(tlPos)) return true;

        bool cState = GetComponentWithID<TrafficLight>(trafficLights[tlPos]).state;
        //if different y values means that its moving up and down
        //Up and down for traffic light is represented with state = false
        //So its flipped here since car only recognize true for move
        if (carPos.y != tlPos.y) cState = !cState;
        return cState;
    }

    public List<Vector2Int> GetTrafficLightPosition(List<Vector2Int> toCheck)
    {
        List<Vector2Int> tlPos = new List<Vector2Int>();

        foreach (Vector2Int pos in toCheck)
        {
            if (trafficLights.ContainsKey(pos)) tlPos.Add(pos);
        }

        return tlPos;
    }
}


