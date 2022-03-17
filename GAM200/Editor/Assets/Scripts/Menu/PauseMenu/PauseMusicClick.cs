using System;

public class PauseMusicClick: MonoBehaviour
{
    Texture settingBtn;

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

    bool optionMusic;

    public override void Start()
    {
        optionMusic = false;

        GameObject go3 = GameObject.Find("MoneyText");
        if (go3 != null)
            moneyText = go3.GetComponent<Transform>();

        pauseMenuBackIcon = GameObject.Find("PauseIcon").GetComponent<Transform>();
        howToPlayBGTransform = GameObject.Find("HowToBG").GetComponent<Transform>();
        newBackTransform = GameObject.Find("HowToPlayBack").GetComponent<Transform>();

        howToPlayTransform = GameObject.Find("HowToText").GetComponent<Transform>();
        resumeTransform = GameObject.Find("ResumeText").GetComponent<Transform>();
        quitTransform = GameObject.Find("QuitText").GetComponent<Transform>();

        areYouSureTransform = GameObject.Find("AreYouSureText").GetComponent<Transform>();
        quitYesTransform = GameObject.Find("YesText").GetComponent<Transform>();
        quitNoTransform = GameObject.Find("NoText").GetComponent<Transform>();

        settingBtn = GameObject.Find("settingBack").GetComponent<Texture>();
    }

    public override void OnMouseEnter()
    {
        if (optionMusic)
        {
            settingBtn.color = new Color(1f, 1f, 1f);
        }
       
    }

    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            if (optionMusic)
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
            }
        }
    }



}

