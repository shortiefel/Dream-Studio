
public class QuitNo : MonoBehaviour
{

    Text text;

    Texture texture;

    Transform areYouSure;
    Transform quitYes;
    Transform quitNo;
    Transform quitOverlay;

    public override void Start()
    {
        //text = GetComponent<Text>();

        areYouSure = GameObject.Find("AreYouSureText").GetComponent<Transform>();
        quitYes = GameObject.Find("QuitYesBtn").GetComponent<Transform>();
        quitNo = GameObject.Find("QuitNoBtn").GetComponent<Transform>();
        quitOverlay = GameObject.Find("QuitOverlay").GetComponent<Transform>();

        texture = GameObject.Find("QuitNoBtn").GetComponent<Texture>();
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
            Disable<Transform>(areYouSure);
            Disable<Transform>(quitYes);
            Disable<Transform>(quitNo);
            Disable<Transform>(quitOverlay);
        }
    }

    public override void OnMouseExit()
    {
        //text.color = new Color(1f, 1f, 1f);
        texture.color = new Color(1f, 1f, 1f);
    }
}
