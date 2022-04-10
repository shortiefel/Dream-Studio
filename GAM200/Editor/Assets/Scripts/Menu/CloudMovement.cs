
public class CloudMovement : MonoBehaviour
{
    float speed;
    float yPos;

    public override void Start()
    {
        speed = Random.Range(1, 5) + (float)Random.Range(1, 5)/10f;
        yPos = transform.position.y;

    }

    public override void Update()
    {
        transform.position += new Vector2(speed * Time.deltaTime, 0);

        if (transform.position.x > 17)
        {
            speed = Random.Range(1, 5) + (float)Random.Range(1, 5) / 10f;
            transform.position = new Vector2(-17, yPos);
        }
    }
}
