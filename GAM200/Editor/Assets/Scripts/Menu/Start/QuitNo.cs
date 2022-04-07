
public class QuitNo : MonoBehaviour
{


    Transform areYouSure;
    Transform quitYes;
    Transform quitNo;
    Transform quitOverlay;
    Transform quitBG;

    public override void Start()
    {

        areYouSure = GameObject.Find("AreYouSureText").GetComponent<Transform>();
        quitYes = GameObject.Find("QuitYesBtn").GetComponent<Transform>();
        quitNo = GameObject.Find("QuitNoBtn").GetComponent<Transform>();
        quitOverlay = GameObject.Find("QuitOverlay").GetComponent<Transform>();
        quitBG = GameObject.Find("QuitBG").GetComponent<Transform>();
    }

    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            Disable<Transform>(areYouSure);
            Disable<Transform>(quitYes);
            Disable<Transform>(quitNo);
            Disable<Transform>(quitBG);
            Disable<Transform>(quitOverlay);
        }
    }

    public override void OnMouseExit()
    {
    }
}
