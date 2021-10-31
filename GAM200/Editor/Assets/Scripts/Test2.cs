
public class Test2 : MonoBehaviour
{
    public Transform trans;
    public override void Start()
    {
        trans = GetComponent<Transform>();
    } 
    public void Test2Function()
    {
        Debug.Log("Get Component of another script (test2) is successful");
    }

    public override void Update()
    {


        if (Input.GetKey(KeyCode.G))
        {
            trans.position += trans.forward * Time.dt * 1250;
        }
        if (Input.GetKey(KeyCode.H))
        {
            trans.localPosition += trans.forward * Time.dt * 1250;
        }

        if (Input.GetMouseButtonDown(1))
        {
            Debug.Log(trans.position);
        }
        if (Input.GetMouseButtonDown(2))
        {
            Debug.Log(trans.localPosition);
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
}

