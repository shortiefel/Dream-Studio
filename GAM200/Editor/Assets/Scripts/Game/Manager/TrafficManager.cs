using System.Collections.Generic;

public class TrafficManager : MonoBehaviour
{
    private TrafficLightManager tlm;
    //private CarManager cm;

    public override void Start()
    {
        tlm = GetComponent<TrafficLightManager>();
        //cm = GetComponent<CarManager>();
    }


    //TrafficLightManager-------------------------------------------------------------------
    //if state = true, car will be turning left
    //state = false, car will be going straight or right
    public bool GetTrafficLightState(Vector2Int tlPos, float _carAngle, bool state)
    {
        return tlm.GetTrafficLightState(tlPos, _carAngle, state);
    }

    public List<uint> GetTrafficLightIndex(List<Vector2> toCheck)
    {
        return tlm.GetTrafficLightIndex(toCheck);
    }

    public bool IsTrafficLight(Vector2Int posToCheck, uint entityId)
    {
        return tlm.IsTrafficLight(posToCheck, entityId);
    }



    //CarManager-------------------------------------------------------------------
    //public void RegisterCar(uint id)
    //{
    //    cm.RegisterCar(id);
    //}
    //
    //public void RemoveCar(uint id)
    //{
    //    cm.RemoveCar(id);
    //}
    //
    //public bool IsCar(uint id)
    //{
    //    return IsCar(id);
    //}
}
