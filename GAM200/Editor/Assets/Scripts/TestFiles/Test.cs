using System;
public class Test : MonoBehaviour
{
    GameObject temTL; //TO Remove
    Camera mainCamera; //TO Remove

    public override void Start()
    {
        temTL = new GameObject(new Prefab("Box")); //To Remove
        mainCamera = GameObject.Find("Camera").GetComponent<Camera>(); //To Remove = GetComponent<Text>();
    }

    public override void Update()
    {
        
        if (Input.GetKeyDown(KeyCode.A))
        {
            Debug.Log("Instantiating ");
            Vector3 mousePos = mainCamera.ScreenToWorldPoint(Input.GetMousePosition());

            Instantiate(temTL, new Vector3(mousePos.x, mousePos.y, 0f));

        }
        if (Input.GetKeyDown(KeyCode.S))
        {
            Vector3 mousePos = mainCamera.ScreenToWorldPoint(Input.GetMousePosition());
            Transform temT = new Transform();
            Debug.Log("Entid " + temT.entityId);

            Instantiate(temTL, new Vector3(mousePos.x, mousePos.y, 0), 2, 90);
        }

        if (Input.GetKeyDown(KeyCode.Z))
        {
            Debug.Log("Instantiating ");

            Instantiate(temTL, new Vector3(0, 0, 0));

        }

        if (Input.GetKeyDown(KeyCode.X))
        {

            Instantiate(temTL, new Vector3(0, 0, 0), 2, 90);
        }

        if (Input.GetMouseButtonDown(MouseCode.Right))
        {
            Debug.Log("asdasdad");
            Console.WriteLine("asdasdad");
        }

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