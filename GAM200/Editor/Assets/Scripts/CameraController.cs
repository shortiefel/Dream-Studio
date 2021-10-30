using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


    class CameraController : MonoBehaviour
    {
        Transform go2;
    Camera cam;
    
        public override void Start()
        {
            go2 = GetComponent<Transform>();
        cam = GetComponent<Camera>();
        

        //tssl.TestFunction();

    }
        public override void Update()
        {
            
            //Console.WriteLine("new Update");
            //Console.WriteLine(Input::GetMouse);
        if (Input.GetKey(KeyCode.J))
            {
                go2.position += -go2.right * Time.dt * 250;
            }

            if (Input.GetKey(KeyCode.L))
            {
                go2.position += go2.right * Time.dt * 250;
            }

            if (Input.GetKey(KeyCode.I))
            {
                go2.position += go2.forward * Time.dt * 250;
            }

            if (Input.GetKey(KeyCode.K))
            {
                go2.position += -go2.forward * Time.dt * 250;
            }

            if (Input.GetKey(KeyCode.U))
            {
                go2.angle += 250 * Time.dt;
            }

            if (Input.GetKey(KeyCode.O))
            {
                go2.angle -= 250 * Time.dt;
            }

        /*if (Input.GetMouseButtonDown(1))
        {
            //Instantiate("Box",go2);
            RaycastHit2D hit = Physics2D.RayCast(cam.ScreenToWorldPoint(Input.GetMousePosition()), Vector2.zero);
            

            if (hit.collider != null)
            {
                Debug.Log(hit.distance);
                Debug.Log(hit.point);
                Vector2Int invec = Vector2Int.RoundToInt(hit.point);
                Debug.Log(invec);
                Debug.Log("First " + hit.transform.position);
            }
        }*/

        

    }
    }

