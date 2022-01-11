
public class InstructionsClick : MonoBehaviour
{
    public bool state;
    public Animation animation;

    public override void Start()
    {
        state = false;
        animation = GetComponent<Animation>();
    }

    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            state = true;
        }
    }
}

