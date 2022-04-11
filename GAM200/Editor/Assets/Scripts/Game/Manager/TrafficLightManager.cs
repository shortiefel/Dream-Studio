using System.Collections.Generic;

public enum DirectionToTL
{
    Up = 0,
    Down,
    Left,
    Right
}

public enum TurnDirection
{
    Left = 0,
    Right,
    None
}

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

    public override void Update()
    {
        //if (carCounter == 0)
        //    Debug.Log(carCounter);
        float deltaTime = Time.deltaTime;

        TrafficLight.timer += deltaTime;
        if (TrafficLight.timer >= TrafficLight.switchTimer)
        {
            TrafficLight.timer = 0f;
            TrafficLight.SwapState();
        }

        if (TrafficLight.changeState)
        {
            TrafficLight.inBetweenTimer += deltaTime;
            if (TrafficLight.inBetweenTimer >= 1.5f)
            //if (inBetweenTimer >= 1.5f || carCounter == 0)
            //if (carCounter == 0)
            {
                //toState = state = !state;
                //state = !state;
                //if (state)
                //    transform.angle = 0;
                ////texture.color = new Color(1, 0, 0, 1);
                //else
                //    transform.angle = 90;

                TrafficLight.directionState = TrafficLight.nextState;
                //if (nextState == DirectionState.Horizontal || nextState == DirectionState.HorizontalLeft)

                TrafficLight.inBetweenTimer = 0f;
                TrafficLight.changeState = false;
            }

            //reqeusting = false;
        }
    }
        public int trafficlightTaxCount()
    {
        return trafficLights.Count;
    }


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

    public bool GetTrafficLightState(Vector2Int tlPos, float _carAngle, DirectionToTL _dtl, TurnDirection _td, uint toCheckId)
    {
        //_carAngle = _carAngle % 360;
        ////angle 0/360/-360 - up, 90/-270 - right, -90/270 - left, 180/-180 - down
        ////+-45 degree for range
        ////if left or right
        //DirectionState ds = DirectionState.Horizontal;
        ////if (state) ds = DirectionState.HorizontalLeft;
        //
        //if ((45f < _carAngle && _carAngle < 135f) || (-315f < _carAngle && _carAngle < -225f) ||
        //    (225f < _carAngle && _carAngle < 315f) || (-135f < _carAngle && _carAngle < -45f))
        //{
        //    ds = DirectionState.Vertical;
        //    //if (state) ds = DirectionState.VerticalLeft;
        //}


        if (!trafficLights.ContainsKey(tlPos)) return false;
        if (trafficLights[tlPos].CheckIfJustSpawn(toCheckId)) return true;

        DirectionState ds = DirectionState.Right;
        switch(_dtl)
        {
            case DirectionToTL.Up:
                {
                    if (_td == TurnDirection.None && trafficLights[tlPos].downCollider.carCount != 0) return false;
                    else if (_td == TurnDirection.Left && trafficLights[tlPos].rightCollider.carCount != 0) return false;
                    else if (_td == TurnDirection.Right && trafficLights[tlPos].leftCollider.carCount != 0) return false;
                    ds = DirectionState.Up;
                    
                    break;
                }
            case DirectionToTL.Down:
                {
                    if (_td == TurnDirection.None && trafficLights[tlPos].upCollider.carCount != 0) return false;
                    else if (_td == TurnDirection.Left && trafficLights[tlPos].leftCollider.carCount != 0) return false;
                    else if (_td == TurnDirection.Right && trafficLights[tlPos].rightCollider.carCount != 0) return false;
                    ds = DirectionState.Down;
                    break;
                }
            case DirectionToTL.Left:
                {
                    if (_td == TurnDirection.None && trafficLights[tlPos].rightCollider.carCount != 0) return false;
                    else if (_td == TurnDirection.Left && trafficLights[tlPos].upCollider.carCount != 0) return false;
                    else if (_td == TurnDirection.Right && trafficLights[tlPos].downCollider.carCount != 0) return false;
                    ds = DirectionState.Left;
                    break;
                }
            case DirectionToTL.Right:
                {
                    if (_td == TurnDirection.None && trafficLights[tlPos].leftCollider.carCount != 0) return false;
                    else if (_td == TurnDirection.Left && trafficLights[tlPos].downCollider.carCount != 0) return false;
                    else if (_td == TurnDirection.Right && trafficLights[tlPos].upCollider.carCount != 0) return false;
                    break;
                }
        }

        //if (_dtl == DirectionToTL.Up) ds = DirectionState.Up;
        //else if (_dtl == DirectionToTL.Down) ds = DirectionState.Down;
        //else if (_dtl == DirectionToTL.Left) ds = DirectionState.Left;
        //else if (_dtl == DirectionToTL.Left)

            //Debug.Log(ds + " " + state);
            

        //trafficLights[tlPos].RequestChange(ds);
        //DirectionState tem = trafficLights[tlPos].directionState;
        
        //return ds == tem;
        return ds == TrafficLight.directionState;
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
        if (trafficLights.ContainsKey(new Vector2Int(position.x + 1, position.y)))
            return false;
        if (trafficLights.ContainsKey(new Vector2Int(position.x - 1, position.y)))
            return false;
        if (trafficLights.ContainsKey(new Vector2Int(position.x, position.y + 1)))
            return false;
        if (trafficLights.ContainsKey(new Vector2Int(position.x, position.y - 1)))
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
        Destroy(trafficLights[position].leftCollider.entityId);
        Destroy(trafficLights[position].rightCollider.entityId);
        Destroy(trafficLights[position].upCollider.entityId);
        Destroy(trafficLights[position].downCollider.entityId);
        Destroy(trafficLights[position].entityId);
        trafficLights.Remove(position);
        return true;

    }
}


