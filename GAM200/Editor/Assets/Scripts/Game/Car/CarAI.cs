using System.Collections;
using System.Collections.Generic;
using System;

public class CarAI : MonoBehaviour
{
    private List<Vector2> path;
    private List<uint> tlIndex;
    private List<Vector2Int> leftTurns;
    private List<Vector2Int> rightTurns;

    private float arriveDistance, lastPointArriveDistance;

    private Vector2 currentTargetPosition;

    private uint hitTarget = 0;

    private int index;

    private bool stop;
    private bool couterStop = false;

    //private Rigidbody2D rb;

    private float defaultPower;
    private float power;
    private float maxPower;
    private float halfPower;


    private CarSpawner endPoint;
    private CarSpawner startPoint;

    private TrafficManager tm;
    private CollisionManager collisionManager;

    //private float raycastLength;
    private float carLength;
    private float fullLength;

    //private float targetAngle;

    private bool changeTarget;
    private Vector2 prevPos;
    //private float prevAngle;
    private float tValue;

    private Vector2 p0;
    private Vector2 p1;
    private Vector2 p2;
    private float angle;
    private bool turning;

    private List<uint> pastTrafficLight;

    Vector2Int nextDestination;

    Vector2Int targetPos;

    Vector2 newHouseLocation;

    Vector2 headOfCar;

    float dt;

    public override void Start()
    {
        carLength = transform.scale.x;
        fullLength = carLength * 2f;
        //raycastLength = carLength * 0.7f;

        path = null;
        index = 0;
        stop = true;

        //rb = GetComponent<Rigidbody2D>();
        

        arriveDistance = 0.3f;
        lastPointArriveDistance = 0.1f;

        defaultPower = 1.5f;
        power = defaultPower;
        maxPower = 4.5f;
        halfPower = maxPower/2f;
        

        //tlPath = null;
        GameObject go1 = GameObject.Find("CollisionManager");
        if (go1 != null)
            collisionManager = go1.GetComponent<CollisionManager>();
        GameObject go2 = GameObject.Find("TrafficManager");
        if (go2 != null)
        {
            tm = go2.GetComponent<TrafficManager>();
            //tm.RegisterCar(transform.entityId);
        }

        changeTarget = false;
        tValue = 0f;
        prevPos = transform.position;

        pastTrafficLight = new List<uint>();

        //The next destination (the house spawn / where the car spawn) will be the returning position
        nextDestination = new Vector2Int(transform.position);
    }

    public void SetPath(List<Vector2> newPath, List<Vector2Int> _leftTurns, List<Vector2Int> _rightTurns, uint destinationID, uint houseId)
    {
        stop = false;
       
        //Currently both will be 0 at the same time
        if (destinationID == 0)
        {
            endPoint = null;
            startPoint = null;
        }
        else
        {
            endPoint = GameObject.FindWithId(destinationID).GetComponent<CarSpawner>();
            startPoint = GameObject.FindWithId(houseId).GetComponent<CarSpawner>();
        }

        //Console.WriteLine("Set 2nd  CarAi path");
        if (newPath.Count == 0)
        {
            Destroy(gameObject);
            return;
        }
        //Debug.Log(newPath[newPath.Count - 1] + " fdsfsfsdfsdfds");
        transform.position = newPath[newPath.Count - 1]; //Realignment
        newPath.RemoveAt(newPath.Count - 1);
        newHouseLocation = newPath[newPath.Count - 1]; 
        newPath.RemoveAt(newPath.Count - 1);

        //leftList = _leftList;
        //Console.WriteLine("p1 " + newPath.Count);
        this.path = newPath;
        leftTurns = _leftTurns;
        rightTurns = _rightTurns;

        index = 0;
        currentTargetPosition = this.path[index];
        

        Vector2 relativeDirection = transform.InverseTransformPoint(currentTargetPosition);
        float value = Vector2.Dot(transform.right, relativeDirection);
        //turningFactor = 1f;
        //Console.WriteLine((int)value);
        if (Math.Round(value) == 1)
        {
            //Debug.Log("right");
            transform.angle = 0f;

        }
        else if (Math.Round(value) == -1)
        {
            //Debug.Log("left");
            transform.angle = 180f;
        }
        else
        {
            value = Vector2.Dot(transform.up, relativeDirection);
            //Console.WriteLine((int)value);
            if (Math.Round(value) == 1)
            {
                //Debug.Log("up");
                transform.angle = 90f;

            }
            else if (Math.Round(value) == -1)
            {
                //Debug.Log("Down");
                transform.angle = -90f;
            }
        }
        //prevAngle = targetAngle = transform.angle;
        if (tm != null)
            tlIndex = tm.GetTrafficLightIndex(path);

        
        SetNextTargetIndex();

        //foreach (var it in leftList)
        //{
        //    Debug.Log(it);
        //}
        //Debug.Log("End -----");

        CarManager.carLists.Add(entityId);
    }

    public override void Update()
    {
        dt = Time.deltaTime;

        headOfCar = transform.position + transform.right * carLength;

        //RaycastHit2DGroup hit = Physics2D.RayCastGroup(new Vector3(headOfCar, 0f), transform.right, (turning ? carLength : fullLength) * power, (int)transform.entityId);
        RaycastHit2DGroup hit = Physics2D.RayCastGroup(new Vector3(headOfCar, 0f), transform.right, carLength * (power / 2f), (int)transform.entityId);

        stop = false;
        couterStop = false;

        if (hit.count != 0 && collisionManager != null)
        {

            for (int i = 0; i < hit.count; i++)
            {

                targetPos = Vector2Int.RoundToInt(hit.transform[i].position);
                uint entId = hit.transform[i].entityId;
                switch (collisionManager.RayTypeCheck(targetPos, entId))
                {
                    case CollisionType.Traffic:
                        
                        
                        if (!stop && pastTrafficLight.Contains(entId))
                        {
                            break;
                        }


                        DirectionToTL dtl = DirectionToTL.Down;
                        TurnDirection td = leftTurns.Contains(targetPos) ? TurnDirection.Left : (rightTurns.Contains(targetPos) ? TurnDirection.Right : TurnDirection.None);

                        if (targetPos.x + 0.5f < headOfCar.x)
                        {
                            //Debug.Log((leftTurns.Contains(targetPos) ? "Turning left " : (rightTurns.Contains(targetPos) ? "Turning Right " : "Going straight ")) + " from " + DirectionToTL.Right);
                            dtl = DirectionToTL.Right;
                        }

                        else if (targetPos.x - 0.5f > headOfCar.x)
                        {
                            //Debug.Log((leftTurns.Contains(targetPos) ? "Turning left " : (rightTurns.Contains(targetPos) ? "Turning Right " : "Going straight ")) + " from " + DirectionToTL.Left);
                            dtl = DirectionToTL.Left;
                        }

                        else if (targetPos.y + 0.5f < headOfCar.y)
                        {
                            //Debug.Log((leftTurns.Contains(targetPos) ? "Turning left " : (rightTurns.Contains(targetPos) ? "Turning Right " : "Going straight ")) + " from " + DirectionToTL.Up);
                            dtl = DirectionToTL.Up;
                        }

                        //else if (targetPos.y - 0.5f > headOfCar.y)
                        //{
                        //    Debug.Log((leftTurns.Contains(targetPos) ? "Turning left " : (rightTurns.Contains(targetPos) ? "Turning Right " : "Going straight ")) + " from " + DirectionToTL.Down);
                        //}
                        
                        bool state = !tm.GetTrafficLightState(targetPos, transform.angle, dtl, td);
                        stop |= state;
                        if (stop) power = halfPower;
                        if (state == false)
                            pastTrafficLight.Add(entId);
                        
                        break;
                    case CollisionType.ERP:
                        //Do nothing much if its ERP as the logic is already in ERP
                        break;
                    case CollisionType.Car:
                        //Stop car because might be other cars
                        //Debug.Log("Hit Car " + power + " " + (carLength * power));
                        collisionManager.AddRaycastCollision(entityId, hit.transform[i].entityId);
                        //Console.WriteLine("Ray " + entityId + " to " + hit.transform[i].entityId);
                        if (collisionManager.CheckStopRaycastCollision(entityId, hit.transform[i].entityId))
                        {
                            stop |= true;
                            //power = power > 2f ? power / 2f : 1f;
                            power = defaultPower;
                        }

                        if (entId == hitTarget)
                        {
                            couterStop = true;
                            //power = power > 2f ? power / 2f : 1f;
                            //Debug.Log("hit stop");
                        }
                        //
                        break;
                    case CollisionType.Building:
                        break;
                    default:
                        break;
                }
            }
            //Debug.Log("------------------------------");
        }

        //stop = true;
        if (Input.GetKey(KeyCode.T)) stop = true;
        //stop = true;


        //if (!testBool)
        //stop = true;
        if (stop) return;
        if (couterStop) return;

        CheckIfArrived();
        //Drive();
        //if (stop) {
        //    if (tm != null)
        //        stop = !tm.GetTrafficLightState(new Vector2Int(currentTargetPosition), transform.angle);
        //}

        if (power < maxPower)
        {
            power += dt;
        
            if (power >= maxPower) power = maxPower;
        }

        if (turning)
        {
            tValue += 0.8f * power * dt;
            transform.position = Vector2.QuadraticBezier(p0, p1, p2, tValue, out angle);
            //Debug.Log(angle);
            transform.angle = angle;

           
        }
        else
        {
            tValue += power * dt;
            transform.position = new Vector2(Mathf.Lerp(prevPos.x, currentTargetPosition.x, tValue), Mathf.Lerp(prevPos.y, currentTargetPosition.y, tValue));
            //transform.angle = Mathf.Lerp(prevAngle, targetAngle, tValue);
        }

        if (tValue > 1f)
        {
            tValue = 0f;
            changeTarget = true;
        }

    }
    
    

    private void CheckIfArrived()
    {

        if (!stop)
        {
           
            var distanceToCheck = arriveDistance;
            //if (path == null) Debug.Log("path is null");
            if (index == path.Count - 1)
            {
                distanceToCheck = lastPointArriveDistance;
            }
            
            if (changeTarget)
            {

                SetNextTargetIndex();
                
            }
        }

    }

    private void SetNextTargetIndex()
    {
        changeTarget = false;
        prevPos = transform.position;
        

        
        //index++;
        if (index >= path.Count)
        {
            stop = true;
            //ScoreSystem.Instance.AddScore();

            ReachToEndPoint();
        }
        else
        {
            currentTargetPosition = path[index];

            if (index + 1 >= path.Count)
            {
                turning = false;
                
                index++;
            }

            else
            {
                p0 = transform.position;
                p1 = path[index];
                index++;
                p2 = path[index];

                float angle = Vector2.AngleBetween(p2 - p0, p1 - p0);
                //Debug.Log(angle);
                //Vector2Int checkPos = new Vector2Int((int)Math.Round(p2.x), (int)Math.Round(p2.y));
                //if (angle < 10f) turning = false;
                //else
                //{
                //    turning = true;
                //    index++;
                //
                //    //Debug.Log("Turning now");
                //}


                //if (leftTurns.Contains(checkPos) || rightTurns.Contains(checkPos)) {
                if (angle > 10f) {
                    turning = true;
                    index++;
                    //Debug.Log("Turning now");
                }
                else
                {
                    turning = false;
                }
            }
        }
    }



    private void ReachToEndPoint()
    {
        CarManager.carLists.Remove(entityId);
        Destroy(gameObject);

        if (endPoint != null)
            endPoint.Notify(new Vector2(newHouseLocation), nextDestination);
        if (startPoint != null)
            startPoint.DisplayPopup();



        //Console.WriteLine("After Notify ");

        //if (tm != null)
        //    tm.RemoveCar(transform.entityId);
    }


    public override void OnTriggerEnter(uint entId)
    {
        if (tlIndex != null)
            if (tlIndex.Contains(entId)) tlIndex.Remove(entId);

        if (collisionManager.ShouldRemoveCar(entId))
        {
            CarManager.carLists.Remove(entityId);
            Destroy(gameObject);
        }

        if (CarManager.carLists.Contains(entId))
        {
            hitTarget = entId;
            //Debug.Log("Override fix");
            //Vector2 headOfCar = transform.position + transform.right * carLength;
            //RaycastHit2DGroup hit = Physics2D.RayCastGroup(new Vector3(headOfCar, 0f), transform.right, fullLength * power, (int)transform.entityId);
            //
            //if (hit.count != 0 && collisionManager != null)
            //{
            //
            //    for (int i = 0; i < hit.count; i++)
            //    {
            //        uint hitId = hit.transform[i].entityId;
            //
            //        if (entId == hitTarget)
            //        {
            //            Debug.Log("Stopping");
            //            couterStop = true;
            //            //power = power > 2f ? power / 2f : 1f;
            //        }
            //    }
            //}
        }
    }

    //For car overlapping each other
    //public override void OnTriggerStay(uint entId)
    //{
    //    //couterStop = false;
    //
    //    if (CarManager.carLists.Contains(entId))
    //    {
    //
    //        Debug.Log("Override fix");
    //        Vector2 headOfCar = transform.position + transform.right * carLength;
    //        RaycastHit2DGroup hit = Physics2D.RayCastGroup(new Vector3(headOfCar, 0f), transform.right, fullLength * power, (int)transform.entityId);
    //
    //        if (hit.count != 0 && collisionManager != null)
    //        {
    //
    //            for (int i = 0; i < hit.count; i++)
    //            {
    //                uint hitId = hit.transform[i].entityId;
    //
    //                if (entId == hitId)
    //                {
    //                    Debug.Log("Stopping");
    //                    couterStop = true;
    //                    //power = power > 2f ? power / 2f : 1f;
    //                }
    //            }
    //        }
    //    }
    //}

    public override void OnTriggerExit(uint entId)
    {
        couterStop = false;
    }

}
