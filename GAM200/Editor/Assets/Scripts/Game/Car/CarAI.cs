using System.Collections;
using System.Collections.Generic;
using System;

public class CarAI : MonoBehaviour
{
    private List<Vector2> path;
    private List<uint> tlIndex;

    
    private float arriveDistance, lastPointArriveDistance;

    private Vector2 currentTargetPosition;



    private int index;

    private bool stop;

    private Rigidbody2D rb;

    private float power;
    private float maxPower;


    private StructureModel endPoint;

    private TrafficManager tm;
    private CollisionManager collisionManager;

    private float raycastLength;
    private float carLength;

    private float targetAngle;

    private bool changeTarget;
    private Vector2 prevPos;
    private float prevAngle;
    private float tValue;

    private Vector2 p0;
    private Vector2 p1;
    private Vector2 p2;
    private float angle;
    private bool turning;

    private List<uint> pastTrafficLight;

    

    public override void Start()
    {
        carLength = transform.scale.x;
        raycastLength = carLength * 0.5f;
        
        path = null;
        index = 0;
        stop = true;

        rb = GetComponent<Rigidbody2D>();
        

        arriveDistance = 0.3f;
        lastPointArriveDistance = 0.1f;

       
        power = 1;
        maxPower = 6;
        

        //tlPath = null;
        GameObject go1 = GameObject.Find("CollisionManager");
        if (go1 != null)
            collisionManager = go1.GetComponent<CollisionManager>();
        GameObject go2 = GameObject.Find("TrafficManager");
        if (go2 != null)
        {
            tm = go2.GetComponent<TrafficManager>();
            tm.RegisterCar(transform.entityId);
        }

        changeTarget = false;
        tValue = 0f;
        prevPos = transform.position;

        pastTrafficLight = new List<uint>();
    }

    public void SetPath(List<Vector2> newPath, uint id)
    {
        stop = false;
        //endPoint = endStructure;
        endPoint = GameObject.FindWithId(id).GetComponent<StructureModel>();

        //Console.WriteLine("Set 2nd  CarAi path");
        if (newPath.Count == 0)
        {
            Destroy(gameObject);
            return;
        }
        //Console.WriteLine("p1 " + newPath.Count);
        this.path = newPath;
       
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
        prevAngle = targetAngle = transform.angle;
        if (tm != null)
            tlIndex = tm.GetTrafficLightIndex(path);

        
        SetNextTargetIndex();
    }

    public override void Update()
    {
        //RaycastHit2D hit = Physics2D.RayCast(new Vector3(transform.position, 0f), transform.right, raycastLength, (int)transform.entityId);
        //
        //stop = false;
        //
        //if (hit.collider != null)
        //{
        //    Vector2Int targetPos = Vector2Int.RoundToInt(hit.transform.position);
        //
        //    if (collisionManager != null)
        //    {
        //        switch (collisionManager.CollisionTypeCheck(targetPos))
        //        {
        //            case CollisionType.Traffic:
        //                Vector2Int hitPos = new Vector2Int(hit.transform.position);
        //                uint entId = hit.transform.entityId;
        //                //if (!stop && pastTrafficLight.Contains(entId))
        //                //{
        //                //    //Debug.Log("Already past");
        //                //    break;
        //                //}
        //                stop |= !tm.GetTrafficLightState(hitPos, transform.angle);
        //                pastTrafficLight.Add(entId);
        //                //Debug.Log("Hiting trigger " + stop);
        //                //if (tlIndex.Contains(hit.transform.entityId))
        //                //{
        //                //    stop = !tm.GetTrafficLightState(new Vector2Int(currentTargetPosition), transform.angle);
        //                //    //stop = true;
        //                //    Debug.Log("Hiting trigger " + stop);
        //                //}
        //                //if (stop)
        //                //power = 2f;
        //                break;
        //            case CollisionType.ERP:
        //                //Do nothing much if its ERP as the logic is already in ERP
        //                break;
        //            case CollisionType.Unknown:
        //                //Stop car because might be other cars
        //                stop |= true;
        //                //Debug.Log("Hit");
        //                //collisionManager.AddRaycastCollision(entityId, hit.transform.entityId);
        //                break;
        //            case CollisionType.Building:
        //                break;
        //            default:
        //                break;
        //        }
        //    }
        //}

        //else
        //{
        //    //Start car because no hit target
        //    stop = false;
        //}

        Vector2 headOfCar = transform.position + transform.right * carLength;
        //Vector2 headOfCar = transform.position;

        RaycastHit2DGroup hit = Physics2D.RayCastGroup(new Vector3(headOfCar, 0f), transform.right, raycastLength, (int)transform.entityId);

        stop = false;

        if (hit.count != 0 && collisionManager != null)
        {
            //if (hit.count > 1)
                //Debug.Log(entityId + " Hit target " + hit.count);
            for (int i = 0; i < hit.count; i++)
            {
                //if (hit.transform[i].entityId != 126)
                    //Debug.Log(entityId + " Hit target " + hit.count + " at " + hit.transform[i].entityId);
                Vector2Int targetPos = Vector2Int.RoundToInt(hit.transform[i].position);
                uint entId = hit.transform[i].entityId;
                switch (collisionManager.CollisionTypeCheck(targetPos, entId))
                {
                    case CollisionType.Traffic:
                        
                        
                        if (!stop && pastTrafficLight.Contains(entId))
                        {
                            break;
                        }

                        bool state = !tm.GetTrafficLightState(targetPos, transform.angle);
                        stop |= state;
                        if (stop) power = 1;
                        if (state == false)
                            pastTrafficLight.Add(entId);
                        
                        break;
                    case CollisionType.ERP:
                        //Do nothing much if its ERP as the logic is already in ERP
                        break;
                    case CollisionType.Unknown:
                        //Stop car because might be other cars
                        //Debug.Log(stop);
                        collisionManager.AddRaycastCollision(entityId, hit.transform[i].entityId);
                        if (collisionManager.CheckStopRaycastCollision(entityId, hit.transform[i].entityId))
                        {
                            stop |= true;
                            power = power > 2f ? power / 2f : 1f;
                        }
                        //Debug.Log("hit");
                        break;
                    case CollisionType.Building:
                        break;
                    default:
                        break;
                }
            }
            //Debug.Log("------------------------------");
        }

        //Debug.Log(entityId + " " + stop + " status");


        //if (path == null || path.Count == 0)
        //{
        //    Destroy(gameObject);
        //}
        //Console.WriteLine("CarAI: " + stop);
        //stop = true;
        //if (Input.GetKey(KeyCode.T)) stop = true;
        //stop = true;
        //Debug.Log(power);
        //if (testBool) 

        //if (!testBool)
        //stop = true;
        if (stop) return;

        CheckIfArrived();
        //Drive();
        if (stop) {
            if (tm != null)
                stop = !tm.GetTrafficLightState(new Vector2Int(currentTargetPosition), transform.angle);
        }

        if (power < maxPower)
        {
            power += Time.deltaTime;
        
            if (power >= maxPower) power = maxPower;
        }

        if (turning)
        {
            tValue += 0.5f * power * Time.deltaTime;
            transform.position = Vector2.QuadraticBezier(p0, p1, p2, tValue, out angle);
            transform.angle = angle;

           
        }
        else
        {
            tValue += power * Time.deltaTime;
            transform.position = new Vector2(Mathf.Lerp(prevPos.x, currentTargetPosition.x, tValue), Mathf.Lerp(prevPos.y, currentTargetPosition.y, tValue));
            //transform.angle = Mathf.Lerp(prevAngle, targetAngle, tValue);
        }

        if (tValue > 0.95f)
        {
            tValue = 0f;
            changeTarget = true;
        }

    }
    //public override void FixedUpdate()
    //{
    //    //if (rb.velocity.magnitude < maxSpeed)
    //    //{
    //    //    rb.AddForce(movementVector.y * transform.up * power * turningFactor);
    //    //}
    //    //Debug.Log(rb.inertia);
    //    //rb.AddTorque(movementVector.x * power * 70);
    //
    //    //transform.angle = targetAngle;
    //    //tValue += power * Time.deltaTime;
    //
    //
    //    //if (turning)
    //    //{
    //    //    tValue += 0.5f * power * Time.deltaTime;
    //    //    transform.position = Vector2.QuadraticBezier(p0, p1, p2, tValue, out angle);
    //    //    transform.angle = angle;
    //    //
    //    //    //if (tValue > 0.9f)
    //    //    //{
    //    //    //    tValue = 0f;
    //    //    //    changeTarget = true;
    //    //    //}
    //    //}
    //    //else
    //    //{
    //    //    tValue += power * Time.deltaTime;
    //    //    transform.position = new Vector2(Mathf.Lerp(prevPos.x, currentTargetPosition.x, tValue), Mathf.Lerp(prevPos.y, currentTargetPosition.y, tValue));
    //    //    //transform.angle = Mathf.Lerp(prevAngle, targetAngle, tValue);
    //    //}
    //    //
    //    //if (tValue > 0.95f)
    //    //{
    //    //    tValue = 0f;
    //    //    changeTarget = true;
    //    //}
    //}

    //private void Drive()
    //{
    //    if (stop)
    //    {
    //     
    //
    //        if (tm != null)
    //            stop = !tm.GetTrafficLightState(new Vector2Int(currentTargetPosition), transform.angle);
    //    }
    //}

    private void CheckIfArrived()
    {

        if (!stop)
        {
           
            var distanceToCheck = arriveDistance;
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
                if (angle < 20f) turning = false;
                else
                {
                    turning = true;
                    index++;

                    //Debug.Log("Turning now");
                }
            }
        }
    }



    private void ReachToEndPoint()
    {
        //Console.WriteLine("Before Notify ");
        Destroy(gameObject);
        //Console.WriteLine("After delete ");

        endPoint.Notify();

        //Console.WriteLine("After Notify ");

        if (tm != null)
            tm.RemoveCar(transform.entityId);
    }

    /*public void Move(Vector2 movementInput)
    {
        this.movementVector = movementInput;
    }*/

    public override void OnTriggerEnter(uint entId)
    {
        //Debug.Log(entId);
        if (tlIndex != null)
            if (tlIndex.Contains(entId)) tlIndex.Remove(entId);
    }
}
