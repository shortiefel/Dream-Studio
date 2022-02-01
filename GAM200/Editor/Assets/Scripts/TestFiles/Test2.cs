
public class Test2 : MonoBehaviour
{
    public override void Update()
    {
        if (Input.GetKeyDown(KeyCode.Q))
        {
            gameObject.AddComponent<Transform>();
        }

        if (Input.GetKeyDown(KeyCode.W))
        {
            AddComponentInternalTem<AudioTest>(entityId);
        }

        if (Input.GetKey(KeyCode.E))
        {
            transform.position += 10f * -transform.up * Time.deltaTime;
        }

        if (Input.GetKey(KeyCode.R))
        {
            transform.position += 10f * -transform.right * Time.deltaTime;
        }
    }
}
