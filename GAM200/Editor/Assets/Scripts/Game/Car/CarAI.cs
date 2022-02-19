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

    private float targetAngle;

    //private float torque = 0.5f;
    private float dotValue;
    private float turningFactor; //Slow down when turning

    private float maxSpeed;

    private Vector2 movementVector;

    private StructureModel endPoint;

    private TrafficManager tm;
    private CollisionManager collisionManager;

    private float raycastLength;

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
        raycastLength = transform.scale.y * 2f;
        //Debug.Log(raycastLength + " lengirhteuth");

        endPoint = null;
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

        dotValue = 0.06f;

        maxSpeed = 3;
        power = 6;
        turningFactor = 1f;
        movementVector = new Vector2(0, 1);
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
    }

    public void SetPath(List<Vector2> newPath, ref StructureModel endStructure)
    {
        stop = false;
        endPoint = endStructure;

        Console.WriteLine("Set 2nd  CarAi path");
        if (newPath.Count == 0)
        {
            Destroy(gameObject);
            return;
        }
        Console.WriteLine("p1 " + newPath.Count);
        this.path = newPath;
        //foreach (var item in path)
        //{
        //    Debug.Log(item.ToString());
        //}
        Console.WriteLine("p2 " + path.Count + " " + this.path.Count);
        index = 0;
        currentTargetPosition = this.path[index];

        foreach(var i in path)
        {
            Console.WriteLine(i);
        }

        Console.WriteLine("ending in c# \n\n");
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
        turningFactor = 1f;
        //Console.WriteLine((int)value);
        if (Math.Round(value) == 1)
        {
            //Debug.Log("right");
            transform.angle = -90f;

        }
        else if (Math.Round(value) == -1)
        {
            //Debug.Log("left");
            transform.angle = 90f;
        }
        else
        {
            value = Vector2.Dot(transform.up, relativeDirection);
            //Console.WriteLine((int)value);
            if (Math.Round(value) == 1)
            {
                //Debug.Log("up");
                transform.angle = 0f;

            }
            else if (Math.Round(value) == -1)
            {
                //Debug.Log("Down");
                transform.angle = -180f;
            }
        }
        targetAngle = transform.angle;
        if (tm != null)
            tlIndex = tm.GetTrafficLightIndex(path);
    }

    public override void Update()
    {
        RaycastHit2D hit = Physics2D.RayCast(new Vector3(transform.position, 0f), transform.up, 0.6f, (int)transform.entityId);
        if (Input.GetKeyDown(KeyCode.Y))
            Debug.Log("up: " + transform.up);
        if (hit.collider != null)
        {
            Vector2Int targetPos = Vector2Int.RoundToInt(hit.transform.position);
            //if (tm.IsTrafficLight(targetPos))
            //{
            //    if (tlIndex.Contains(hit.transform.entityId))
            //    {
            //        stop = !tm.GetTrafficLightState(currentTargetPosition, transform.angle);
            //        //stop = true;
            //        //Debug.Log("Hiting trigger");
            //    }
            //}

            //else
            //{
            //    //Stop car because might be other cars
            //    stop = true;
            //}

            if (collisionManager != null)
            {
                switch (collisionManager.CollisionTypeCheck(targetPos))
                {
                    case CollisionType.Traffic:
                        if (tlIndex.Contains(hit.transform.entityId))
                        {
                            stop = !tm.GetTrafficLightState(new Vector2Int(currentTargetPosition), transform.angle);
                            //stop = true;
                            //Debug.Log("Hiting trigger");
                        }
                        break;
                    case CollisionType.ERP:
                        //Do nothing if its ERP as the logic is already in ERP
                        break;
                    case CollisionType.Unknown:
                        //Stop car because might be other cars
                        //stop = true;
                        break;
                    default:
                        break;
                }
            }

            //Debug.Log("Hiting trigger");
        }

        else
        {
            //Start car because no hit target
            stop = false;
        }
        //if (path == null || path.Count == 0)
        //{
        //    Destroy(gameObject);
        //}
        CheckIfArrived();
        Drive();
        //CheckForCollisions();

    }
    public override void FixedUpdate()
    {
        if (rb.velocity.magnitude < maxSpeed)
        {
            rb.AddForce(movementVector.y * transform.up * power * turningFactor);
        }
        //Debug.Log(rb.inertia);
        rb.AddTorque(movementVector.x * power * 70);
        //transform.angle = Mathf.Lerp(transform.angle, targetAngle, power * Time.deltaTime);
    }

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
            movementVector = Vector2.zero;

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
            Vector2 relativeDirection = transform.InverseTransformPoint(currentTargetPosition);
            float value = Vector2.Dot(transform.right, relativeDirection);
            var rotateCar = 0;
            turningFactor = 1f;
            if (value > dotValue)
            {
                //Debug.Log("Turn right");
                rotateCar = -1;
                targetAngle = transform.angle - 90f;
                turningFactor = 0.5f;
            }
            if (value < -dotValue)
            {
                //Debug.Log("Turn left");
                rotateCar = 1;
                targetAngle = transform.angle + 90f;
                turningFactor = 0.5f;
            }
            //OnDrive?.Invoke(new Vector2(rotateCar, 1));
            movementVector = new Vector2(rotateCar, 1);
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
            if (Vector2.Distance(currentTargetPosition, transform.position) < distanceToCheck)
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
        index++;
        if (index >= path.Count)
        {
            stop = true;
            //ScoreSystem.Instance.AddScore();

            ReachToEndPoint();
        }
        else
        {
            currentTargetPosition = path[index];

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
        Console.WriteLine("Before Notify ");
        Destroy(gameObject);
        Console.WriteLine("After delete ");
        endPoint.Notify();
        Console.WriteLine("After Notify ");

        if (tm != null)
            tm.RemoveCar(transform.entityId);
    }

    /*public void Move(Vector2 movementInput)
    {
        this.movementVector = movementInput;
    }*/

    public override void OnTriggerEnter(uint id)
    {
        if (tlIndex != null)
            if (tlIndex.Contains(id)) tlIndex.Remove(id);
    }
}
