using System.Collections;
using System.Collections.Generic;
using System;

public class CarMenuAI : MonoBehaviour
{

    //[SerializeField]
    private  Vector2 startPosition, endPosition;

    private Rigidbody2D rb;

    private float power;
    private float maxSpeed;
    private float turningFactor; //Slow down when turning

    public void StartCarMenu()
    {
        startPosition.x = -89.4f;
        startPosition.y = 13.4f;
        endPosition.x = -40.3f;
        endPosition.y = 55.8f;
    }

    public void UpdateCarMenu()
    {
        if (rb.velocity.magnitude < maxSpeed)
        {
            rb.AddForce(transform.up * power * turningFactor);
        }
    }

    private void EndCarMenu()
    {
        Console.WriteLine("Before Notify ");
        Destroy(gameObject);
        Console.WriteLine("After delete ");
    }

}


