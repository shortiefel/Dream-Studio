//using DreamEngine;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

/*public enum TEST
{
    tem = 0,
    tem1,
    tem2
}*/

public class Test : MonoBehaviour
{
    //Transform transform;
    public int health;
    /* public Vector2 vec2Test;
        public TEST testEnum;
        public char testChar;
        public Vector2 newvec2Test;*/
    Transform go2;
    Camera cam;
    Test2 tssl;
    Test2 ts2;
    //Collider col1;

    public override void Start()
    {
        go2 = GetComponent<Transform>();
        cam = GetComponent<Camera>();
        tssl = GetComponent<Test2>();
        //col1 = GetComponent<Collider>();
        //Console.WriteLine(GetComponent<Collider>().entityId);
        //Transform tem = GetTransform();
        //Vector2 pos = go2.GetPosition();
        //Console.WriteLine(pos);
        //go2.position = new Vector2(0, 0);
        Debug.Log("init");

        //Console.WriteLine(go2);
        ts2 = new Test2();
        //go2.scale = new Vector2(30, 100);
        /*Console.WriteLine(go2.position + new Vector2(10,10));

        go2.position += new Vector2(500, 500);
        Console.WriteLine(go2.position);*/
        //Console.WriteLine(col1.entityId);
        Debug.Log("Has Component Collider? ");
        Debug.Log(HasComponent<Collider>(entityId));
    }

    public override void Update()
    {
        //Console.WriteLine("new Update");
        //Console.WriteLine(Input::GetMouse);
        if (Input.GetKey(KeyCode.A))
        {
            go2.position += -go2.right * Time.dt * 250;
        }

        if (Input.GetKey(KeyCode.D))
        {
            go2.position += go2.right * Time.dt * 250;
        }

        if (Input.GetKey(KeyCode.W))
        {
            go2.position += go2.forward * Time.dt * 250;
        }

        if (Input.GetKey(KeyCode.S))
        {
            go2.position += -go2.forward * Time.dt * 250;
        }

        if (Input.GetKey(KeyCode.Q))
        {
            go2.angle += 250 * Time.dt;
        }

        if (Input.GetKey(KeyCode.E))
        {
            go2.angle -= 250 * Time.dt;
        }

        /*if (Input.GetMouseButtonDown(0))
        {
            //Instantiate("Box",go2);
            *//*RaycastHit2D hit = Physics2D.RayCast(new Vector3(go2.position.x, go2.position.y, 1), Vector2.zero);

            if (hit.collider != null)
            {
                Debug.Log(hit.distance);
                Debug.Log(hit.point);
                Debug.Log("First " + hit.transform.position);
            }*//*

            GameObject gameObject = new GameObject();
            Debug.Log("Creating Entity");
        }

        if (Input.GetMouseButtonDown(1))
        {
            GameObject gameObject = new GameObject("Game Object");
            Debug.Log("Creating Entity with name");
        }*/
        if (Input.GetMouseButtonDown(1))
        {
            Debug.Log("In Click");
            if (tssl != null) {
                Debug.Log("not null");
                tssl.TestFunction();
                ts2.TestFunction();
            }
        }

        /*if (Input.GetMouseButtonDown(0))
         {
            //Instantiate("Box",go2);
            float hitDis = 0f;
            Debug.Log(Physics2D.RayCast(go2.position, go2.forward, out hitDis, go2.entityId, 200f));
        }*/
        //if (Input.GetMouseButtonDown(1))
        //{
        //Instantiate Prefab
        /*for (int i = 0; i < 100; i++)
        {
            Instantiate_Entity("Box");
        }*/
        //Instantiate("Box");
        //Physics Ray cast and Debug.log
        //{
        //float hitDis = 0f;
        //Debug.Log(Physics2D.RayCast(go2.position, go2.forward, out hitDis, go2.entityId, 200f));
        //Debug.Log(hitDis);
        //}

        //Disable
        //Disable(go2);
        //go2.SetActive(false);
        /*if (cam != null)
        {
            Vector3 tem = cam.ScreenToWorldPoint(Input.GetMousePosition());
            Debug.Log(tem);
        }*/
        //}


    }

    public override void OnMouseEnter()
    {
        Debug.Log("Mouse Enter");
    }

    public override void OnMouseClick()
    {
        Debug.Log("Mouse Enter click");
    }

    public override void OnMouseExit()
    {
        Debug.Log("Mouse Exit");
    }

    public override void OnCollisionEnter()
    {
        //Instantiate_Entity("Box");
        //SceneManager.LoadScene("Test3");
        Debug.Log("Test Collision Enter");
    }

    public override void OnCollisionExit()
    {
        Debug.Log("Test Collision Exit");
    }

    public override void OnTriggerEnter()
    {
        Debug.Log("Test Trigger Enter");
    }

    public override void OnTriggerExit()
    {
        Debug.Log("Test Trigger Exit");
    }

}



