
public class Test2 : MonoBehaviour
{
    public int num;

    public override void Start()
    {
        num = 0;
    }

    public override void Update()
    {
        if (Input.GetKeyDown(KeyCode.Q))
        {
            gameObject.AddComponent<Collider>();
        }
        if (Input.GetKeyDown(KeyCode.W))
        {
            //gameObject.AddComponent<Test2>();
            AddComponent<Test2>();
        }

        if (Input.GetKeyDown(KeyCode.E))
        {
            //gameObject.AddComponent<Generate1500Object>();
            AddComponent<Generate1500Object>();
        }

    }
}
