using System;
using System.Collections.Generic;

public class Test : MonoBehaviour
{


    Texture texture;
    Light light;
    public override void Start()
    {

        texture = GetComponent<Texture>();
        light = GetComponent<Light>();
    }

    public override void Update()
    {
        if (Input.GetKey(KeyCode.F))
        {
            texture.alpha -= 0.01f;
        }
        if (Input.GetKey(KeyCode.R))
        {
            texture.alpha += 0.01f;
        }

        if (Input.GetKey(KeyCode.T))
        {
            Disable<Light>(light);
        }
        if (Input.GetKey(KeyCode.G))
        {
            Enable<Light>(light);
        }
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