using System;

public class QuitButton : MonoBehaviour
{
    Text text;
    Texture texture;

    Transform areYouSure;
    Transform quitYes;
    Transform quitNo;
    Transform quitOverlay;
    Transform quitBG;

    public override void Start()
    {
        Console.WriteLine("going in start play");

        text = GetComponent<Text>();
        text.color = new Color(0f, 0f, 0f);
        texture = GameObject.Find("Quitbtn").GetComponent<Texture>();
        texture.color = new Color(1f, 1f, 1f);

        areYouSure = GameObject.Find("AreYouSureText").GetComponent<Transform>();
        quitYes = GameObject.Find("QuitYesBtn").GetComponent<Transform>();
        quitNo = GameObject.Find("QuitNoBtn").GetComponent<Transform>();
        quitOverlay = GameObject.Find("QuitOverlay").GetComponent<Transform>();
        quitBG = GameObject.Find("QuitBG").GetComponent<Transform>();

        Disable<Transform>(areYouSure);
        Disable<Transform>(quitYes);
        Disable<Transform>(quitNo);
        Disable<Transform>(quitBG);
        Disable<Transform>(quitOverlay);

    }

    public override void OnMouseEnter()
    {
        text.color = new Color(1f, 1f, 1f);
        texture.color = new Color(1f, 0.5f, 0f);
    }

    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            Enable<Transform>(areYouSure);
            Enable<Transform>(quitYes);
            Enable<Transform>(quitNo);
            Enable<Transform>(quitBG);
            Enable<Transform>(quitOverlay);
        }                     
    }                         

    public override void OnMouseExit()
    {
        text.color = new Color(0f, 0f, 0f);
        texture.color = new Color(1f, 1f, 1f);
    }
}