using System;
using System.Collections.Generic;

public class Test : MonoBehaviour
{
    //GameObject temTL; //TO Remove
    //Camera mainCamera; //TO Remove

    public override void Start()
    {
        //temTL = new GameObject(new Prefab("Box")); //To Remove
        //mainCamera = GameObject.Find("Camera").GetComponent<Camera>(); //To Remove = GetComponent<Text>();

        Waypoint wp = GetComponent<Waypoint>();

        //The list hold list of vector2 (each List<Vector2> is a possible path/route the car can take
        //The points added should be with reference to the center 0, 0
        //Order is how the list of points (shown in the inspector) will be cut 
        //The first value currently is 1 so only 1 position is considered as one route
        //The Console.WriteLine below will display how the route are spilt up in the console
        //The numbers in the order should add up to the number of points your have

        //You can view the TestScene.scene to see how to directly add the points and order in or another way is to add it using the inspector

        //TLDR
        //points = all possible waypoint the car can go to
        //order = how to group the points (the number of element = number of route) (the total value of all order should be = number of waypoints)


        List<List<Vector2>> listOfWaypoints = wp.GetWaypoints();

        foreach (var i in listOfWaypoints)
        {
            Console.WriteLine("Current set");
            foreach (var t in i)
            {
                Console.WriteLine(t);
            }

            Console.WriteLine("\nNext Set \n");
        }
    }

    public override void Update()
    {
        
        //if (Input.GetKeyDown(KeyCode.A))
        //{
        //    Debug.Log("Instantiating ");
        //    Vector3 mousePos = mainCamera.ScreenToWorldPoint(Input.GetMousePosition());
        //
        //    Instantiate(temTL, new Vector3(mousePos.x, mousePos.y, 0f));
        //
        //}
        //if (Input.GetKeyDown(KeyCode.S))
        //{
        //    Vector3 mousePos = mainCamera.ScreenToWorldPoint(Input.GetMousePosition());
        //    Transform temT = new Transform();
        //    //Debug.Log("Entid " + temT.entityId);
        //
        //    Instantiate(temTL, new Vector3(mousePos.x, mousePos.y, 0), 2, 90);
        //}
        //
        //if (Input.GetKeyDown(KeyCode.Z))
        //{
        //    Debug.Log("Instantiating ");
        //
        //    Instantiate(temTL, new Vector3(0, 0, 0));
        //
        //}
        //
        //if (Input.GetKeyDown(KeyCode.X))
        //{
        //
        //    Instantiate(temTL, new Vector3(0, 0, 0), 2, 90);
        //}
        //
        //if (Input.GetKeyDown(KeyCode.D))
        //{
        //    Debug.Log("Instantiating ");
        //
        //    Instantiate(temTL, new Vector3(5, 3, 0));
        //
        //}
        //
        //if (Input.GetKeyDown(KeyCode.F))
        //{
        //
        //    Instantiate(temTL, new Vector3(2, 6, 0), 2, 64);
        //}
        //
        //if (Input.GetMouseButtonDown(MouseCode.Right))
        //{
        //    Debug.Log("asdasdad");
        //    Console.WriteLine("asdasdad");
        //}

        //
        //else if (Input.GetKeyDown(KeyCode.H))
        //{
        //    Debug.Log("Start");
        //    dir = 1;
        //    on = true;
        //}
        //
        //else if (Input.GetKeyDown(KeyCode.J))
        //{
        //    on = true;
        //    dir = -1;
        //    Debug.Log("start " + on);
        //}
        //
        //if (Input.GetKeyDown(KeyCode.T))
        //{
        //    forcesA = false;
        //    forceDir = -1;
        //    Debug.Log("stop " + forceDir);
        //}
        //
        //if (Input.GetKeyDown(KeyCode.Y))
        //{
        //    forcesA = true;
        //    forceDir = 1;
        //    Debug.Log("start " + forceDir);
        //}
        //
        //if (Input.GetKeyDown(KeyCode.U))
        //{
        //    forcesA = true;
        //    forceDir = -1;
        //    Debug.Log("start " + forceDir);
        //}
    }

    public override void FixedUpdate()
    {
        //if (on)
        //    rb.AddTorque(dir * 90);
        //
        //if (forcesA)
        //    rb.AddForce(new Vector2(10f, 2f) * forceDir);

       
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