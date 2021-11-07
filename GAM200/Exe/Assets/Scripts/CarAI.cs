using System.Collections;
using System.Collections.Generic;

public class CarAI : MonoBehaviour
{
    //[SerializeField]
    private List<Vector2> path = null;
    //[SerializeField]
    private float arriveDistance = 0.3f, lastPointArriveDistance = 0.1f;
    //[SerializeField]
    private float turningAngleOffset = 5;
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

    private int index = 0;

    private bool stop;
    private bool collisionStop = false;

    public bool Stop
    {
        get { return stop || collisionStop; }
        set { stop = value; }
    }

    //[field: SerializeField]
    //public UnityEvent<Vector2> OnDrive { get; set; }

    public override void Start()
    {
        if (path == null || path.Count == 0)
        {
            Stop = true;
        }
        else
        {
            currentTargetPosition = path[index];
        }
    }

    public void SetPath(List<Vector2> path)
    {
        if (path.Count == 0)
        {
            Destroy(gameObject);
            return;
        }
        this.path = path;
        //foreach (var item in path)
        //{
        //    Debug.Log(item.ToString());
        //}
        index = 0;
        currentTargetPosition = this.path[index];
        //Debug.Log(currentTargetPosition);

        Vector2 relativepoint = transform.InverseTransformPoint(this.path[index + 1]);
        //Debug.Log(relativepoint);
        float angle = Mathf.Atan2(relativepoint.x, relativepoint.y) * Mathf.Rad2Deg;
        //Debug.Log(angle);

        //transform.rotation = Quaternion.Euler(0, 0, -angle);
        transform.angle = -angle;
        Stop = false;
    }

    public override void Update()
    {
        CheckIfArrived();
        Drive();
        //CheckForCollisions();
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
        if (Stop)
        {
            //OnDrive?.Invoke(Vector2.zero);
        }
        else
        {
            Vector2 relativepoint = transform.InverseTransformPoint(currentTargetPosition);
            //Debug.Log(relativepoint);
            float angle = Mathf.Atan2(relativepoint.x, relativepoint.y) * Mathf.Rad2Deg;
            //Debug.Log(angle);
            var rotateCar = 0;
            if (angle > turningAngleOffset)
            {
                rotateCar = -1;
            }
            else if (angle < -turningAngleOffset)
            {
                rotateCar = 1;
            }
            //OnDrive?.Invoke(new Vector2(rotateCar, 1));
        }
    }

    private void CheckIfArrived()
    {
        if (Stop == false)
        {
            var distanceToCheck = arriveDistance;
            if (index == path.Count - 1)
            {
                distanceToCheck = lastPointArriveDistance;
            }
            if (Vector2.Distance(currentTargetPosition, transform.position) < distanceToCheck)
            {
                // Add the mass manager here
                //scoreSystem.AddScore();
                SetNextTargetIndex();
                //Debug.Log(transform.position);
            }
        }

    }

    private void SetNextTargetIndex()
    {
        index++;
        if (index >= path.Count)
        {
            Stop = true;
            //ScoreSystem.Instance.AddScore();
            Destroy(gameObject);
        }
        else
        {
            currentTargetPosition = path[index];
        }
    }
}
