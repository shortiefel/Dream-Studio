using System.Collections.Generic;

public class TrafficLightManager : MonoBehaviour
{

    private Dictionary<Vector2, uint> trafficLights;

    public override void Start()
    {
        trafficLights = new Dictionary<Vector2, uint>();
    }

    public void RegisterTrafficLight(Vector2 pos, uint id)
    {
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

    public Queue<Vector2Int> GetTrafficLightPosition(List<Vector2Int> toCheck)
    {
        Queue<Vector2Int> tlPos = new Queue<Vector2Int>();

        foreach (Vector2Int pos in toCheck)
        {
            if (trafficLights.ContainsKey(pos)) tlPos.Enqueue(pos);
        }

        return tlPos;
    }
}


