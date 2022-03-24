using System;
public class HowToPlayButton : MonoBehaviour
{
    Text text;
    UI texture;
    Transform pauseMenuBackIcon;
    Transform howToPlayBGTransform;
    Transform newBackTransform;

    Transform howToPlayTransform;
    Transform resumeTransform;
    Transform quitTransform;

    Transform areYouSureTransform;
    Transform quitYesTransform;
    Transform quitNoTransform;

    Transform moneyText;

    UI backButtonUI;

    bool htw;


    public override void Start()
    {
        htw = false;

        GameObject go3 = GameObject.Find("MoneyText");
        if (go3 != null)
            moneyText = go3.GetComponent<Transform>();

        pauseMenuBackIcon = GameObject.Find("PauseIcon").GetComponent<Transform>();
        howToPlayBGTransform = GameObject.Find("HowToBG").GetComponent<Transform>();
        newBackTransform = GameObject.Find("HowToPlayBack").GetComponent<Transform>();
        howToPlayTransform = GameObject.Find("HowToText").GetComponent<Transform>();
        resumeTransform = GameObject.Find("ResumeText").GetComponent<Transform>();
        quitTransform = GameObject.Find("QuitText").GetComponent<Transform>();
        texture = GameObject.Find("howToPlayBtn").GetComponent<UI>();

        areYouSureTransform = GameObject.Find("AreYouSureText").GetComponent<Transform>();
        quitYesTransform = GameObject.Find("YesText").GetComponent<Transform>();
        quitNoTransform = GameObject.Find("NoText").GetComponent<Transform>();

        backButtonUI = GetComponent<UI>();


        text = GetComponent<Text>();

        //Is actually How to play button
        if (text != null)
        {

            texture.color = new Color(1f, 1f, 1f);
            htw = true;
        }
        else
        {
            backButtonUI.color = new Color(1f, 1f, 1f);
        }


    }

    public override void OnMouseEnter()
    {
        if (htw)
        {
            text.color = new Color(1f, 1f, 1f);
            texture.color = new Color(1f, 0.5f, 0f);
        }

        else
        {
            backButtonUI.color = new Color(1f, 1f, 1f);
        }
    }

    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            if (htw)
            {
                Enable<Transform>(howToPlayBGTransform);
                Enable<Transform>(newBackTransform);


                Disable<Transform>(howToPlayTransform);
                Disable<Transform>(resumeTransform);
                Disable<Transform>(quitTransform);
                Disable<Transform>(moneyText);

                Disable<Transform>(pauseMenuBackIcon);

                Disable<Transform>(areYouSureTransform);
                Disable<Transform>(quitYesTransform);
                Disable<Transform>(quitNoTransform);
            }

            else
            {
                Disable<Transform>(howToPlayBGTransform);
                Disable<Transform>(newBackTransform);

                Enable<Transform>(moneyText);
                Enable<Transform>(howToPlayTransform);
                Enable<Transform>(resumeTransform);
                Enable<Transform>(quitTransform);

                Enable<Transform>(pauseMenuBackIcon);
            }
        }
    }

    public override void OnMouseExit()
    {
        if (htw)
        {
            text.color = new Color(0f, 0f, 0f);
            texture.color = new Color(1f, 1f, 1f);
        }
        else
        {
            backButtonUI.color = new Color(0f, 0f, 0f); 
        }
    }
}