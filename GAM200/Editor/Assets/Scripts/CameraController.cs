﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


    class CameraController : MonoBehaviour
    {
        Transform go2;
    Camera cam;
        public override void OnInit()
        {
            go2 = GetComponent<Transform>();
        cam = GetComponent<Camera>();
            
        }
        public override void OnUpdate()
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

        if (Input.GetMouseButtonDown(1))
        {
            //Instantiate("Box",go2);
            RaycastHit2D hit = Physics2D.RayCast(cam.ScreenToWorldPoint(Input.GetMousePosition()), Vector2.zero);
            Debug.Log(hit.distance);
            Debug.Log(hit.point);

            if (hit.collider != null)
            {
                Debug.Log("First " + hit.transform.position);
                Vector2Int invec = Vector2Int.RoundToInt(hit.transform.position);
                Debug.Log("First " + invec);
            }
        }

    }
    }

