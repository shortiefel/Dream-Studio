using System;

public class Test2 : MonoBehaviour
{
    //Test test;
    Transform trans;
    public override void Start()
    {
        //test = GameObject.Find("Object1").GetComponent<Test>();
        // test.num = 109;
        /*Rigidbody2D rb = GetComponent<Rigidbody2D>();
        Console.WriteLine("CarAi id: " + entityId);*/
        trans = GameObject.Find("Entity1").GetComponent<Transform>();
    }

    public override void Update()
    {
        //Debug.Log("From Test2 " + test.num);
        /* if (Input.GetKey(KeyCode.W))
         {
             transform.position += transform.up * 10f * Time.deltaTime;
         }

         if (Input.GetKey(KeyCode.D))
         {
             transform.position += transform.right * 10f * Time.deltaTime;
         }*/
        Vector2 relativeDirection = transform.InverseTransformPoint(trans.position);
        float value = Vector2.Dot(transform.right, relativeDirection);
        //if (value > 0) Console.WriteLine("Turn right");
        //if (value < 0) Console.WriteLine("Turn left");
    }

}