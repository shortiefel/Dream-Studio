using System;
using System.Collections.Generic;

public class Test : MonoBehaviour
{
    bool left = false;

    public override void Start()
    {
    }

    public override void Update()
    {
        
       if (left)
        {
            transform.position += new Vector2(-0.1f, 0f);

            if (transform.position.x < -11f) left = false;
        }
       else
        {
            transform.position += new Vector2(0.1f, 0f);

            if (transform.position.x > 11f) left = true;
        }
    }

    

}