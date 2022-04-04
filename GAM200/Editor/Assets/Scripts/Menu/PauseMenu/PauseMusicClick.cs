using System;

public class PauseMusicClick: MonoBehaviour
{

    Transform pauseMenuBackIcon;
    Transform howToPlayBGTransform;
    Transform newBackTransform;

    Transform howToPlayTransform;
    Transform resumeTransform;
    Transform menuTransform;
    Transform quitTransform;

    Transform moneyText;

    Transform MasterText;
    Transform BGMText;
    Transform SFXText;
    Transform VolumeAdjustSFX;
    Transform VolumeAdjustBGM;
    Transform VolumeAdjust;

    Transform upVolMaster;
    Transform downVolMaster;
    Transform upVolBGM;
    Transform downVolBGM;
    Transform upVolSFX;
    Transform downVolSFX;

    Transform settingBG;
    Transform settingBtn;
    Transform settingBack;

    //Texture settingBackTexture;

    static bool optionMusic;

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
        menuTransform = GameObject.Find("MenuText").GetComponent<Transform>();




        MasterText = GameObject.Find("MasterText").GetComponent<Transform>();
        BGMText = GameObject.Find("BGMText").GetComponent<Transform>();
        SFXText = GameObject.Find("SFXText").GetComponent<Transform>();
        VolumeAdjustSFX = GameObject.Find("VolumeAdjustSFX").GetComponent<Transform>();
        VolumeAdjustBGM = GameObject.Find("VolumeAdjustBGM").GetComponent<Transform>();
        VolumeAdjust = GameObject.Find("VolumeAdjust").GetComponent<Transform>();


        upVolMaster = GameObject.Find("UpVol").GetComponent<Transform>();
        downVolMaster = GameObject.Find("DownVol").GetComponent<Transform>();
        upVolBGM = GameObject.Find("UpBGMVol").GetComponent<Transform>();
        downVolBGM = GameObject.Find("DownBGMVol").GetComponent<Transform>();
        upVolSFX = GameObject.Find("UpSFXVol").GetComponent<Transform>();
        downVolSFX = GameObject.Find("DownSFXVol").GetComponent<Transform>();

        settingBG = GameObject.Find("settingBG").GetComponent<Transform>();
        settingBtn = GameObject.Find("settingBtn").GetComponent<Transform>();
        settingBack = GameObject.Find("settingBack").GetComponent<Transform>();

        //settingBackTexture = GameObject.Find("settingBack").GetComponent<Texture>();
    }

    //public override void OnMouseEnter()
    //{
    //    if (!optionMusic)
    //    {
    //        settingBackTexture.color = new Color(1f, 1f, 1f);
    //    }
    //}
    //
    //public override void OnMouseExit()
    //{
    //    if (!optionMusic)
    //    {
    //        settingBackTexture.color = new Color(0f, 0f, 0f);
    //    }
    //
    //}

    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            if (optionMusic)
            {
                //Enable<Transform>(howToPlayBGTransform);
                //Enable<Transform>(newBackTransform);

                Enable<Transform>(howToPlayTransform);
                Enable<Transform>(resumeTransform);
                Enable<Transform>(menuTransform);
                Enable<Transform>(quitTransform);
                Enable<Transform>(moneyText);

                Enable<Transform>(pauseMenuBackIcon);


                Disable<Transform>(MasterText);
                Disable<Transform>(BGMText);
                Disable<Transform>(SFXText);
                Disable<Transform>(VolumeAdjustSFX);
                Disable<Transform>(VolumeAdjustBGM);
                Disable<Transform>(VolumeAdjust);

                Disable<Transform>(upVolMaster);
                Disable<Transform>(downVolMaster);
                Disable<Transform>(upVolBGM);
                Disable<Transform>(downVolBGM);
                Disable<Transform>(upVolSFX);
                Disable<Transform>(downVolSFX);


                Disable<Transform>(settingBG);
                Disable<Transform>(settingBack);

                Enable<Transform>(settingBtn);

                optionMusic = false;
            }
            else
            {
                Disable<Transform>(howToPlayTransform);
                Disable<Transform>(resumeTransform);
                Disable<Transform>(menuTransform);
                Disable<Transform>(quitTransform);
                Disable<Transform>(moneyText);

                Disable<Transform>(pauseMenuBackIcon);

                Enable<Transform>(MasterText);
                Enable<Transform>(BGMText);
                Enable<Transform>(SFXText);
                Enable<Transform>(VolumeAdjustSFX);
                Enable<Transform>(VolumeAdjustBGM);
                Enable<Transform>(VolumeAdjust);

                Enable<Transform>(upVolMaster);
                Enable<Transform>(downVolMaster);
                Enable<Transform>(upVolBGM);
                Enable<Transform>(downVolBGM);
                Enable<Transform>(upVolSFX);
                Enable<Transform>(downVolSFX);


                Enable<Transform>(settingBG);
                Enable<Transform>(settingBack);

                Disable<Transform>(settingBtn);

                optionMusic = true;

            }
        }
    }



}

