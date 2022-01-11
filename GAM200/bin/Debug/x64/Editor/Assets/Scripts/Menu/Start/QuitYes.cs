
public class QuitYes : MonoBehaviour
{
    Text text;
    public override void Start()
    {
        text = GetComponent<Text>();
    }

    public override void OnMouseEnter()
    {
        text.color = new Color(0f, 0f, 0f);
    }

    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            Application.Quit();
        }
    }

    public override void OnMouseExit()
    {
        text.color = new Color(1f, 1f, 1f);
    }
}