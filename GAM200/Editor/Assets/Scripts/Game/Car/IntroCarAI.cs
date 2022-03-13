using System.Collections;
using System.Collections.Generic;
using System;

public class IntroCarAI : MonoBehaviour
{
   private Vector2 startPosition;

    private bool type;

    public override void Start()
    {
        ////rb = GetComponent<Rigidbody2D>();
      
        //if(transform.position.x < -270)
        //    type = true;
        //else
        //    type = false;

        //if (type)
        //    startPosition = new Vector2(-12, -5.2f);
        //else
        startPosition = new Vector2(-15, -1.2f);
    }


    public override void Update()
    {
        transform.position += transform.right * 20f * Time.deltaTime;

        //if (type && transform.position.x > 30f)
        //    transform.position = startPosition;
        if (transform.position.x > 30f)
            transform.position = startPosition;
    }



}


