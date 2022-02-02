
public class Generate1500Object : MonoBehaviour
{
    Test2 test2;

    public override void Start()
    {
        test2 = GameObject.Find("sdr").GetComponent<Test2>();

    }
    public override void Update()
    {
        if (Input.GetKeyDown(KeyCode.W)) {
            Debug.Log(test2.num);
        }

        if (Input.GetKeyDown(KeyCode.S))
        {
            test2.num++;
        }



        if (Input.GetKey(KeyCode.Z))
        {
            gameObject.transform.position += new Vector2(2, 0);
        }

        if (Input.GetKey(KeyCode.X))
        {
            transform.position -= new Vector2(2, 0);
        }
    }
}

