public class CollisionRubrics : MonoBehaviour 
{
    public override void Update()
    {
        if (Input.GetKey(KeyCode.W))
        {
            transform.position += transform.up * 10 * Time.deltaTime;
        }

        if (Input.GetKey(KeyCode.S))
        {
            transform.position -= transform.up * 10 * Time.deltaTime;
        }

        if (Input.GetKey(KeyCode.A))
        {
            transform.position -= transform.right * 10 * Time.deltaTime;
        }
        
        if (Input.GetKey(KeyCode.D))
        {
            transform.position += transform.right * 10 * Time.deltaTime;
        }

        if (Input.GetKey(KeyCode.Q))
        {
            transform.angle += 100 * Time.deltaTime;
        }
    }
}