using System;

public class PauseMusicClick: MonoBehaviour
{

    Transform pauseMenuBackIcon;

    Transform howToPlayTransform;
    Transform resumeTransform;
    Transform menuTransform;
    Transform quitTransform;

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
    Transform optionSetting;
    Transform settingBtn;
    Transform settingBack;
    Transform soundBg;
    Transform soundBg2;
    Transform soundBg3;

    UI settingBackBtn;
    static bool optionMusic;
    static bool settingBool;

    public override void Start()
    {
        optionMusic = false;
        settingBackBtn = GetComponent<UI>();
        settingBackBtn.color = new Color(1f, 1f, 1f);
        pauseMenuBackIcon = GameObject.Find("PauseIcon").GetComponent<Transform>();

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
        optionSetting = GameObject.Find("OptionSetting").GetComponent<Transform>();
        settingBtn = GameObject.Find("settingBtn").GetComponent<Transform>();
        settingBack = GameObject.Find("settingBack").GetComponent<Transform>();
        soundBg = GameObject.Find("SoundBg").GetComponent<Transform>();
        soundBg2 = GameObject.Find("SoundBg2").GetComponent<Transform>();
        soundBg3 = GameObject.Find("SoundBg3").GetComponent<Transform>();

        settingBool = false;

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
        Disable<Transform>(optionSetting);
        Disable<Transform>(settingBack);
        Disable<Transform>(settingBtn);

        Disable<Transform>(soundBg);
        Disable<Transform>(soundBg2);
        Disable<Transform>(soundBg3);

    }

    public override void OnMouseEnter()
    {
        settingBackBtn.color = new Color(1f, 0.5f, 0f);
    }
    public override void OnMouseExit()
    {
        settingBackBtn.color = new Color(1f, 1f, 1f);
    }
    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            if (optionMusic)
            {
                Debug.Log("Closing setting");
                settingBool = false;
                Enable<Transform>(howToPlayTransform);
                Enable<Transform>(resumeTransform);
                Enable<Transform>(menuTransform);
                Enable<Transform>(quitTransform);

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
                Disable<Transform>(optionSetting);
                Disable<Transform>(soundBg);
                Disable<Transform>(soundBg2);
                Disable<Transform>(soundBg3);
                Enable<Transform>(settingBtn);


                optionMusic = false;
            }
            else
            {
                Debug.Log("Opening setting");
                settingBool = true;
                Disable<Transform>(howToPlayTransform);
                Disable<Transform>(resumeTransform);
                Disable<Transform>(menuTransform);
                Disable<Transform>(quitTransform);

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
                Enable<Transform>(optionSetting);

                Enable<Transform>(soundBg);
                Enable<Transform>(soundBg2);
                Enable<Transform>(soundBg3);
                Disable<Transform>(settingBtn);

                optionMusic = true;

            }
        }
    }

    public bool getSettingBool()
    {
        return settingBool;
    }

}

