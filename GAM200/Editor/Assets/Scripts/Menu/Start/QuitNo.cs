
public class QuitNo : MonoBehaviour
{

    Text text;

    Transform areYouSure;
    Transform quitYes;
    Transform quitNo;
    Transform quitOverlay;

    public override void Start()
    {
        text = GetComponent<Text>();

        areYouSure = GameObject.Find("AreYouSureText").GetComponent<Transform>();
        quitYes = GameObject.Find("YesText").GetComponent<Transform>();
        quitNo = GameObject.Find("NoText").GetComponent<Transform>();
        quitOverlay = GameObject.Find("QuitOverlay").GetComponent<Transform>();
    }

    public override void OnMouseEnter()
    {
        text.color = new Color(0f, 0f, 0f);
    }

    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            Disable<Transform>(areYouSure);
            Disable<Transform>(quitYes);
            Disable<Transform>(quitNo);
            Disable<Transform>(quitNo);
            Disable<Transform>(quitOverlay);
        }
    }

    public override void OnMouseExit()
    {
        text.color = new Color(1f, 1f, 1f);
    }
}
