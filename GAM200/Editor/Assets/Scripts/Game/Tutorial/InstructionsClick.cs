
public class InstructionsClick : MonoBehaviour
{
    public bool state;

    public override void Start()
    {
        state = false;
    }

    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            state = true;
        }
    }
}

