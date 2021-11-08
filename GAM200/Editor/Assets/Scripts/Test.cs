using System;
public class Test : MonoBehaviour
{
    //public int num;
    //RoadFixer roadFixer;
    Rigidbody2D rb;
    Transform trans;
    bool on = true;
    bool forcesA = true;
    int dir = 1;
    int forceDir = 1;
    public override void Start()
    {
        //Debug.Log("Test start");
        //roadFixer = GameObject.Find("RoadManager").GetComponent<RoadFixer>();
        //Grid.GridTest();
        rb = GetComponent<Rigidbody2D>();
        trans = GetComponent<Transform>();
    }

    public override void Update()
    {
        
        if (Input.GetKeyDown(KeyCode.G))
        {
            on = false;
            Debug.Log("stop " + on);
        }

        else if (Input.GetKeyDown(KeyCode.H))
        {
            Debug.Log("Start");
            dir = 1;
            on = true;
        }

        else if (Input.GetKeyDown(KeyCode.J))
        {
            on = true;
            dir = -1;
            Debug.Log("start " + on);
        }

        if (Input.GetKeyDown(KeyCode.T))
        {
            forcesA = false;
            forceDir = -1;
            Debug.Log("stop " + forceDir);
        }

        if (Input.GetKeyDown(KeyCode.Y))
        {
            forcesA = true;
            forceDir = 1;
            Debug.Log("start " + forceDir);
        }

        if (Input.GetKeyDown(KeyCode.U))
        {
            forcesA = true;
            forceDir = -1;
            Debug.Log("start " + forceDir);
        }
    }

    public override void FixedUpdate()
    {
        if (on)
            rb.AddTorque(dir * 90);

        if (forcesA)
            rb.AddForce(new Vector2(10f, 2f) * forceDir);

       
    }

    public override void OnMouseEnter()
    {
        //Debug.Log("From ENter ");
    }
    public override void OnMouseExit()
    {
        //Debug.Log("From exit ");
    }

}