using System.Collections;
using System.Collections.Generic;
using System;

public class CarMenuAI : MonoBehaviour
{
    private Vector2 startPosition;
    private Vector2 endPosition;

    private bool type;

    //private Rigidbody2D rb;

    public override void Start()
    {
        //rb = GetComponent<Rigidbody2D>();
        if (transform.position.x < -90)
            type = true;
        else
            type = false;

        if (type)
            startPosition = new Vector2(-100f, 4.2f);
        else
            startPosition = new Vector2(12f, 65f);

    }

    public override void Update()
    {
        transform.position += transform.up * 20f * Time.deltaTime;

        if (type && transform.position.y > 70f ||
            !type && transform.position.x > 100f)
        {
            transform.position = startPosition;
        }



    }

}


