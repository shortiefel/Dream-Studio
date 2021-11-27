
public class Generate1500Object : MonoBehaviour
{
    int x, y;
    Prefab prefab;

    public override void Start()
    {
        x = 0;
        y = 0;
        prefab = new Prefab("Box");

    }
    public override void Update()
    {
        if (Input.GetKey(KeyCode.C)) {
            Instantiate(prefab, new Vector3(x * 2f, y * 2f, 0));
            x++;
            if (x > 99)
            {
                x = 0;
                y++;
            }
        }
    }
}

