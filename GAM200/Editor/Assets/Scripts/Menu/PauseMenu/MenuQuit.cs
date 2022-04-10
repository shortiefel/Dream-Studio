using System;

public class Menu : MonoBehaviour
{
    Text text;
    Texture texture;

    Transform areYouSure;
    Transform MquitYes;
    Transform MquitNo;
    Transform quitOverlay;
    Transform quitBG;
    private AudioSource btnClick;
    public override void Start()
    {
        //Console.WriteLine("going in start play");

        text = GetComponent<Text>();
        text.color = new Color(0f, 0f, 0f);
        texture = GameObject.Find("BackToMenuBtn").GetComponent<Texture>();
        texture.color = new Color(1f, 1f, 1f);
        btnClick = GetComponent<AudioSource>();

        areYouSure = GameObject.Find("AreYouSureText").GetComponent<Transform>();
        MquitYes = GameObject.Find("MenuYesbtn").GetComponent<Transform>();
        MquitNo = GameObject.Find("MenuNoBtn").GetComponent<Transform>();
        quitOverlay = GameObject.Find("QuitOverlay").GetComponent<Transform>();
        quitBG = GameObject.Find("QuitBG").GetComponent<Transform>();

        Disable<Transform>(areYouSure);
        Disable<Transform>(MquitYes);
        Disable<Transform>(MquitNo);
        Disable<Transform>(quitBG);
        Disable<Transform>(quitOverlay);

    }

    public override void OnMouseEnter()
    {
        btnClick.Play();
        text.color = new Color(1f, 1f, 1f);
        texture.color = new Color(1f, 0.5f, 0f);
    }

    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            Enable<Transform>(areYouSure);
            Enable<Transform>(MquitYes);
            Enable<Transform>(MquitNo);
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