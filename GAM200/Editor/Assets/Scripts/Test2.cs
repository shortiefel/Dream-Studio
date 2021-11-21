
public class Test2 : MonoBehaviour
{
    public override void Update()
    {
        if (Input.GetKey(KeyCode.W))
        {
            transform.position += 10f * transform.up * Time.deltaTime;
        }

        if (Input.GetKey(KeyCode.A))
        {
            transform.position += 10f * transform.right * Time.deltaTime;
        }

        if (Input.GetKey(KeyCode.S))
        {
            transform.position += 10f * -transform.up * Time.deltaTime;
        }

        if (Input.GetKey(KeyCode.D))
        {
            transform.position += 10f * -transform.right * Time.deltaTime;
        }
    }
}
