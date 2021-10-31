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
    public Transform trans;
    public GameObject go1;

 
    //Collider col1;

    public override void Start()
    {
        trans = GetComponent<Transform>();

        
        //col1 = GetComponent<Collider>();
        //Console.WriteLine(GetComponent<Collider>().entityId);
        //Transform tem = GetTransform();
        //Vector2 pos = go2.GetPosition();
        //Console.WriteLine(pos);
        //go2.position = new Vector2(0, 0);
        //Debug.Log(go1.transform.entityId);
    }

    public override void Update()
    {
        //Console.WriteLine("new Update");
        //Console.WriteLine(Input::GetMouse);
        if (Input.GetKey(KeyCode.A))
        {
            trans.position += -trans.right * Time.dt * 250;
        }

        if (Input.GetKey(KeyCode.D))
        {
            trans.position += trans.right * Time.dt * 250;
        }

        if (Input.GetKey(KeyCode.W))
        {
            trans.position += trans.forward * Time.dt * 250;
        }

        if (Input.GetKey(KeyCode.S))
        {
            trans.position += -trans.forward * Time.dt * 250;
        }

        if (Input.GetKey(KeyCode.Q))
        {
            trans.angle += 250 * Time.dt;
        }

        if (Input.GetKey(KeyCode.E))
        {
            trans.angle -= 250 * Time.dt;
        }


        if (Input.GetKeyDown(KeyCode.G))
        {
            //go1 = Instantiate("Box", trans);
        }
        if (Input.GetMouseButtonDown(2))
        {
            
        }
        if (Input.GetMouseButtonDown(3))
        {
            //if (test2 != null)
     
            //else Debug.Log("Is null now");
        }
        if (Input.GetMouseButtonDown(4))
        {
  
        }

        /*if (Input.GetMouseButtonDown(2))
        {
            var tem = go1.AddComponent<Test2>();
            //tem.TestFunction();
        }*/


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



