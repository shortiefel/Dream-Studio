using System.Collections;
using System.Collections.Generic;
using System;

public class CarAI : MonoBehaviour
{
    //[SerializeField]
    private List<Vector2> path;
    //private Queue<Vector2Int> tlPath;
    private List<uint> tlIndex;

    //[SerializeField]
    private float arriveDistance, lastPointArriveDistance;
    //[SerializeField]
    //private float turningAngleOffset;
    //[SerializeField]
    private Vector2 currentTargetPosition;

    //[SerializeField]
    //private GameObject raycastStartingPoint = null;
    //[SerializeField]
    //private float collisionRaycastLength = 0.1f;

    //internal bool IsThisLastPathIndex()
    //{
    //    return index >= path.Count - 1;
    //}

    private int index;

    private bool stop;
    //private bool collisionStop;

    private Rigidbody2D rb;

    private float power;
    private float maxPower;


    //private float torque = 0.5f;
    //private float dotValue;
    //private float turningFactor; //Slow down when turning

    //private float maxSpeed;

    //private Vector2 movementVector;

    private StructureModel endPoint;
    //private GameObject endPointGO;

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

    //private bool testBool = true;
    /*public bool Stop
    {
        get { return stop || collisionStop; }
        set { stop = value; }
    }*/

    //[field: SerializeField]
    //public UnityEvent<Vector2> OnDrive { get; set; }
    //public Action<Vector2> OnDrive;

    public override void Start()
    {
        carLength = transform.scale.x;
        raycastLength = carLength * 0.5f;
        
        //Debug.Log(raycastLength + " lengirhteuth");

        //endPoint = null;
        path = null;
        index = 0;
        stop = true;
        //collisionStop = false;

        rb = GetComponent<Rigidbody2D>();
        //GetComponent<AudioSource>().Play();

        //if (path == null || path.Count == 0)
        //if (path == null || path.Count == 0)
        //{
        //    stop = true;
        //}
        //else
        //{
        //    currentTargetPosition = path[index];
        //}

        arriveDistance = 0.3f;
        lastPointArriveDistance = 0.1f;
        //turningAngleOffset = 0.02;

        //dotValue = 0.06f;
        //
        //maxSpeed = 3;
        power = 1;
        maxPower = 6;
        //maxPower = 1;
        //turningFactor = 1f;
        //movementVector = new Vector2(0, 1);
        //Console.WriteLine("Testing " + rb.velocity);

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
        //foreach (var item in path)
        //{
        //    Debug.Log(item.ToString());
        //}
        //Console.WriteLine("p2 " + path.Count + " " + this.path.Count);
        index = 0;
        currentTargetPosition = this.path[index];

        //foreach(var i in path)
        //{
        //    Console.WriteLine(i);
        //}

        //Console.WriteLine("ending in c# \n\n");
        //Vector2 directionToFace = new Vector2(0f, 0f);
        //if (this.path.Count != 1)
        //{
        //    directionToFace = currentTargetPosition = this.path[index];
        //}
        //
        //
        //else
        //{
        //    currentTargetPosition = this.path[0];
        //    directionToFace = endStructure.transform.position;
        //    Debug.Log("end ");
        //}
        //Console.WriteLine("p3 " + index);
        //Debug.Log(currentTargetPosition);

        /*Vector2 relativepoint = transform.InverseTransformPoint(this.path[index + 1]);
        //Debug.Log(relativepoint);
        float angle = Mathf.Atan2(relativepoint.x, relativepoint.y) * Mathf.Rad2Deg;
        Debug.Log(angle);

        //transform.rotation = Quaternion.Euler(0, 0, -angle);
        transform.angle = -angle;
        Console.WriteLine(angle);*/

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

        //p0 = transform.position;
        //p1 = path[index];
        //if (index + 1 == path.Count)
        //    p2 = p1;
        //else
        //    p2 = path[index + 1];
        //
        //turning = false;
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
                        //Vector2Int hitPos = new Vector2Int(hit.transform[i].position);
                        //Debug.Log("Enter count");
                        
                        if (!stop && pastTrafficLight.Contains(entId))
                        {
                            break;
                        }

                        bool state = !tm.GetTrafficLightState(targetPos, transform.angle);
                        stop |= state;
                        if (state == false)
                            pastTrafficLight.Add(entId);
                        //Debug.Log(stop + " TL");
                        //if (tlIndex.Contains(hit.transform.entityId))
                        //{
                        //    stop = !tm.GetTrafficLightState(new Vector2Int(currentTargetPosition), transform.angle);
                        //    //stop = true;
                        //    Debug.Log("Hiting trigger " + stop);
                        //}
                        //if (stop)
                        //power = 2f;
                        break;
                    case CollisionType.ERP:
                        //Do nothing much if its ERP as the logic is already in ERP
                        break;
                    case CollisionType.Unknown:
                        //Stop car because might be other cars
                        //Debug.Log(stop);
                        stop |= true;
                        //Debug.Log(stop);
                        //collisionManager.AddRaycastCollision(entityId, hit.transform.entityId);
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

        //if (!testBool) stop = true;
        if (stop) return;

        CheckIfArrived();
        Drive();
        //CheckForCollisions();
        

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

            //if (tValue > 0.9f)
            //{
            //    tValue = 0f;
            //    changeTarget = true;
            //}
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

    //private void CheckForCollisions()
    //{
    //    if (Physics.Raycast(raycastStartingPoint.transform.position, transform.forward, collisionRaycastLength, 1 << gameObject.layer))
    //    {
    //        collisionStop = true;
    //    }
    //    else
    //    {
    //        collisionStop = false;
    //    }
    //}

    private void Drive()
    {
        if (stop)
        {
            //Console.WriteLine("stopping ");
            //if (path == null) Console.WriteLine("stopping2222222 ");
            //OnDrive?.Invoke(Vector2.zero);
            //movementVector = Vector2.zero;

            if (tm != null)
                stop = !tm.GetTrafficLightState(new Vector2Int(currentTargetPosition), transform.angle);
        }
        else
        {
            /*Vector2 relativepoint = transform.InverseTransformPoint(currentTargetPosition);
            Debug.Log(currentTargetPosition + " ---target");
            Debug.Log(relativepoint);
            float angle = Mathf.Atan2(relativepoint.x, relativepoint.y) * Mathf.Rad2Deg;
            Debug.Log(angle + " new");
            var rotateCar = 0;
            if (angle > turningAngleOffset)
            {
                rotateCar = -1;
                Debug.Log("Turn right");
            }
            else if (angle < -turningAngleOffset)
            {
                Debug.Log("Turn left");
                rotateCar = 1;
            }*/
            //Console.WriteLine("Before Drive ");

            //------------------------Temporary remove---------------------
            //Vector2 relativeDirection = transform.InverseTransformPoint(currentTargetPosition);
            //float value = Vector2.Dot(transform.right, relativeDirection);
            //var rotateCar = 0;
            //turningFactor = 1f;
            //if (value > dotValue)
            //{
            //    //Debug.Log("Turn right");
            //    rotateCar = -1;
            //    //targetAngle = transform.angle - 90f;
            //    turningFactor = 0.5f;
            //}
            //if (value < -dotValue)
            //{
            //    //Debug.Log("Turn left");
            //    rotateCar = 1;
            //    //targetAngle = transform.angle + 90f;
            //    turningFactor = 0.5f;
            //}
            ////OnDrive?.Invoke(new Vector2(rotateCar, 1));
            //movementVector = new Vector2(rotateCar, 1);
            //------------------------Temporary remove---------------------
            //Console.WriteLine("End drive ");
        }
    }

    private void CheckIfArrived()
    {
        //if (stop == false)
        //Console.WriteLine("Before CheckIfArrived ");
        if (!stop)
        {
            //Console.WriteLine("After stop ");
            var distanceToCheck = arriveDistance;
            if (index == path.Count - 1)
            {
                distanceToCheck = lastPointArriveDistance;
            }
            //Console.WriteLine("After index ");
            //if (Vector2.Distance(currentTargetPosition, transform.position) < distanceToCheck)
            if (changeTarget)
            {
                //Console.WriteLine("Insde Distance ");
                // Add the mass manager here
                //scoreSystem.AddScore();
                SetNextTargetIndex();
                //Console.WriteLine("After SetNextTargetIndex ");
                //Debug.Log(transform.position);
            }
        }

        //Console.WriteLine("After CheckIfArrived ");

    }

    private void SetNextTargetIndex()
    {
        changeTarget = false;
        prevPos = transform.position;
        //prevAngle = transform.angle;
        //if (prevAngle > 360f)
        //{
        //    prevAngle -= 360f;
        //    transform.angle = prevAngle;
        //}
        //else if (prevAngle < -360f)
        //{
        //    prevAngle += 360f;
        //    transform.angle = prevAngle;
        //}

        
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
            



            
            //Debug.Log("currentTargetPosition " + currentTargetPosition + " - prevPos " + prevPos);
            //Debug.Log(currentTargetPosition - prevPos);
            //Vector2 diff = currentTargetPosition - prevPos;
            //targetAngle = Vector2.AngleBetween(currentTargetPosition - prevPos, new Vector2(0, 1));
            //if (diff.x > 0) targetAngle *= -1;
            //Debug.Log("From " + prevAngle + " " + transform.angle + " to " + targetAngle + " old----------");
            //targetAngle = Mathf.ShortestAngle(targetAngle, transform.angle);
            //Debug.Log("From " + prevAngle + " " + transform.angle + " to " + targetAngle);
            /*if (tlPath == null || tlPath.Count == 0) return;
            if (currentTargetPosition == tlPath[0])
            {
                tlPath.RemoveAt(0);
                //True = move so stop would false
                stop = !tm.GetTrafficLightState(currentTargetPosition, transform.position);
            }*/
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

    public override void OnTriggerEnter(Transform trans)
    {
        if (tlIndex != null)
            if (tlIndex.Contains(trans.entityId)) tlIndex.Remove(trans.entityId);
    }
}
