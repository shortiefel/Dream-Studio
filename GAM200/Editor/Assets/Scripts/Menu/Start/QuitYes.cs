
public class QuitYes : MonoBehaviour
{
    Text text;

    Transform quitYes;

    Texture texture;
    public override void Start()
    {
        text = GetComponent<Text>();
        quitYes = GameObject.Find("QuitYesBtn").GetComponent<Transform>();
        texture = GameObject.Find("QuitYesBtn").GetComponent<Texture>();
    }

    public override void OnMouseEnter()
    {
        //text.color = new Color(0f, 0f, 0f);
        texture.color = new Color(1f, 1f, 1f);
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
        //text.color = new Color(1f, 1f, 1f);
        texture.color = new Color(1f, 1f, 1f);
    }
}